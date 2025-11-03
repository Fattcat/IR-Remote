#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <IRremote.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define IR_RECV_PIN 2
#define IR_SEND_PIN 3
#define BTN_UP 4
#define BTN_DOWN 5
#define BTN_ENTER 6

IRrecv irrecv(IR_RECV_PIN);
IRsend irsend;
decode_results results;

// Maximálny počet RAW pulzov, ktoré uložíme (obmedzené EEPROM a RAM)
#define MAX_RAW_LEN 80
byte storedLength = 0;
unsigned int rawBuffer[MAX_RAW_LEN];

// Menu
const char* menuItems[] = { "Learn IR", "Send IR" };
const byte menuSize = 2;
byte menuIndex = 0;

unsigned long lastDebounce = 0;
const unsigned long debounceDelay = 200;

// EEPROM adresa začiatku dát
#define EEPROM_ADDR_LEN 0
#define EEPROM_ADDR_DATA (EEPROM_ADDR_LEN + 1)

void setup() {
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_ENTER, INPUT_PULLUP);

  irrecv.enableIRIn();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1); // OLED chyba
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println(F("IR Remote"));
  display.println(F("Loading..."));
  display.display();

  loadFromEEPROM();
  delay(1000);
  showMenu();
}

void loop() {
  if (millis() - lastDebounce > debounceDelay) {
    if (!digitalRead(BTN_UP)) {
      menuIndex = (menuIndex + menuSize - 1) % menuSize;
      showMenu();
      lastDebounce = millis();
    }
    if (!digitalRead(BTN_DOWN)) {
      menuIndex = (menuIndex + 1) % menuSize;
      showMenu();
      lastDebounce = millis();
    }
    if (!digitalRead(BTN_ENTER)) {
      if (menuIndex == 0) learnIR();
      else sendIR();
      showMenu();
      lastDebounce = millis();
    }
  }
}

void showMenu() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("-- IR Remote --"));
  for (byte i = 0; i < menuSize; i++) {
    if (i == menuIndex) display.print(F("--> "));
    else display.print(F("    "));
    display.println(menuItems[i]);
  }
  display.display();
}

void learnIR() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("Point IR remote"));
  display.println(F("and press btn"));
  display.display();

  while (!irrecv.decode(&results)) {
    // čakáme
  }

  // Ulož do buffera (max MAX_RAW_LEN - 1, pretože začíname od indexu 1)
  storedLength = 0;
  for (byte i = 1; i < results.rawlen && storedLength < MAX_RAW_LEN; i++) {
    rawBuffer[storedLength] = results.rawbuf[i] * 50; // USECPERTICK = 50
    storedLength++;
  }

  irrecv.resume();
  saveToEEPROM();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("IR learned!"));
  display.println(F("Saved to EEPROM"));
  display.display();
  delay(2000);
}

void sendIR() {
  if (storedLength == 0) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("No IR code"));
    display.println(F("learned yet!"));
    display.display();
    delay(2000);
    return;
  }

  irsend.sendRaw(rawBuffer, storedLength, 38);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("IR sent!"));
  display.display();
  delay(2000);
}

void saveToEEPROM() {
  EEPROM.write(EEPROM_ADDR_LEN, storedLength);
  for (byte i = 0; i < storedLength && i < MAX_RAW_LEN; i++) {
    // EEPROM ukladá bajty (0-255), ale my máme unsigned int (0-65535)
    // Preto uložíme ako dva bajty: low a high
    EEPROM.write(EEPROM_ADDR_DATA + i * 2,     rawBuffer[i] & 0xFF);
    EEPROM.write(EEPROM_ADDR_DATA + i * 2 + 1, rawBuffer[i] >> 8);
  }
}

void loadFromEEPROM() {
  storedLength = EEPROM.read(EEPROM_ADDR_LEN);
  if (storedLength > MAX_RAW_LEN) storedLength = 0; // ochrana

  for (byte i = 0; i < storedLength; i++) {
    byte low  = EEPROM.read(EEPROM_ADDR_DATA + i * 2);
    byte high = EEPROM.read(EEPROM_ADDR_DATA + i * 2 + 1);
    rawBuffer[i] = ((unsigned int)high << 8) | low;
  }
}
