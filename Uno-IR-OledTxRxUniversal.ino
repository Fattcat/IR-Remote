// Arduino uno code with Oled display, buttons and IR Tx and Rx Diodes to make portable Universal Remote Controler.
// --------------------------------
// Connection
// IR RX pin D2
// IR TX pin D3
// ---
// Button    UP pin 4
// Button  DOWN pin 5
// Button ENTER pin 6
// ---
// OLED Display 
// VCC 5V, GND to GND, SDA - A4, SCL - A5
// ---- 
// SD Card Module
// VCC 5V, GND to GND,CS 10, MISO 11, MOSI 12, SCK 13
// Code
#include <IRremote.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SD.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define IR_RECEIVE_PIN 2
#define IR_SEND_PIN 3
#define BUTTON_UP 4
#define BUTTON_DOWN 5
#define BUTTON_ENTER 6
#define SD_CS_PIN 10

#define USECPERTICK 50  // Definovanie hodnoty USECPERTICK, zodpovedá 38kHz modulovaniu

IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;
IRsend irsend;

int menuIndex = 0;
const char* menuItems[] = {"Receive", "Send", "Saved Codes"};
const int menuSize = 3;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_ENTER, INPUT_PULLUP);

  irrecv.enableIRIn();
  //irsend.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED displej sa nepodarilo inicializovať"));
    while (true);
  }
  display.clearDisplay();
  display.display();

  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD karta sa nepodarilo inicializovať");
  }
  showMenu();
}

void loop() {
  if (millis() - lastDebounceTime > debounceDelay) {
    if (!digitalRead(BUTTON_UP)) {
      menuIndex = (menuIndex - 1 + menuSize) % menuSize;
      showMenu();
      lastDebounceTime = millis();
    }
    if (!digitalRead(BUTTON_DOWN)) {
      menuIndex = (menuIndex + 1) % menuSize;
      showMenu();
      lastDebounceTime = millis();
    }
    if (!digitalRead(BUTTON_ENTER)) {
      handleSelection(menuIndex);
      lastDebounceTime = millis();
    }
  }
}

void showMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("-- IR Remote Control --");
  for (int i = 0; i < menuSize; i++) {
    if (i == menuIndex) display.print("--> ");
    else display.print("    ");
    display.println(menuItems[i]);
  }
  display.display();
}

void handleSelection(int index) {
  switch (index) {
    case 0:
      receiveIR();
      break;
    case 1:
      sendLastIR();
      break;
    case 2:
      listSavedCodes();
      break;
  }
  showMenu();
}

void receiveIR() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Press your IR button");
  display.println("to read ...");
  display.display();

  while (!irrecv.decode(&results)) {
    // čakaj na signál
  }

  // Uloženie dát
  String filename = getNextFileName();
  File file = SD.open(filename.c_str(), FILE_WRITE);
  if (file) {
    file.print("RAW: ");
    for (int i = 1; i < results.rawlen; i++) {
      file.print(results.rawbuf[i] * USECPERTICK);
      if (i < results.rawlen - 1) file.print(",");
    }
    file.close();
  }

  irrecv.resume();
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("IR uložené do:");
  display.println(filename);
  display.display();
  delay(2000);
}

void sendLastIR() {
  String filename = getLastFileName();
  File file = SD.open(filename.c_str());
  if (!file) return;

  String line = file.readStringUntil('\n');
  file.close();

  line.replace("RAW: ", "");
  int len = 0;
  unsigned int rawData[200];
  char *token = strtok((char*)line.c_str(), ",");
  while (token != NULL && len < 200) {
    rawData[len++] = atoi(token);
    token = strtok(NULL, ",");
  }

  irsend.sendRaw(rawData, len, 38);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("IR signál odoslaný");
  display.display();
  delay(2000);
}

void listSavedCodes() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Uložené IR kódy:");
  File root = SD.open("/");
  while (true) {
    File entry = root.openNextFile();
    if (!entry) break;
    String name = entry.name();
    if (name.startsWith("IR") && name.endsWith(".TXT")) {
      display.println(name);
      display.display();
      delay(500);
    }
    entry.close();
  }
  delay(3000);
}

// Funkcia pre získanie názvu súboru s nulami pred číslom
String getNextFileName() {
  for (int i = 1; i <= 999; i++) {
    char fname[10];
    snprintf(fname, sizeof(fname), "IR%03d.TXT", i);  // Použitie sprintf na formátovanie čísla
    if (!SD.exists(fname)) {
      return String(fname);
    }
  }
  return "IR999.TXT";
}

String getLastFileName() {
  String lastName = "IR001.TXT";
  for (int i = 1; i <= 999; i++) {
    char fname[10];
    snprintf(fname, sizeof(fname), "IR%03d.TXT", i);  // Použitie sprintf na formátovanie čísla
    if (SD.exists(fname)) lastName = fname;
  }
  return lastName;
}
