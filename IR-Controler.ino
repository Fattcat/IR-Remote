// Some IR Codes for LED Control
// Flash - FBD02F
// Strobe - FBF00F
// Fade - FBC837
// Smooth - FBE817
// Green - FBA05F
// Red - FB20DF
// Power OFF / ON - FB18E7
// Blue - FB609F
// White - FBE01F
// Adjust - FBD827
// Decrease - FB38C7

#include <IRremote.h>

// Definujte piny
const int SEND_PIN = 9;    // IR vysielač na pin 9 (namiesto pinu 3)
const int OnOff = 2;       // Tlačidlo pripojené na pin 2
const int Adjust = 3;      // Tlačidlo pripojené na pin 3
const int Decrease = 4;    // Tlačidlo pripojené na pin 4
const int Red = 5;         // Tlačidlo pripojené na pin 5
const int Green = 6;       // Tlačidlo pripojené na pin 6
const int Blue = 7;        // Tlačidlo pripojené na pin 7

void setup() {
  Serial.begin(9600);
  
  // Inicializácia IR vysielača
  IrSender.begin(SEND_PIN, ENABLE_LED_FEEDBACK);
  
  // Inicializácia tlačidiel
  pinMode(OnOff, INPUT_PULLUP);  
  pinMode(Adjust, INPUT_PULLUP);
  pinMode(Decrease, INPUT_PULLUP);
  pinMode(Red, INPUT_PULLUP);
  pinMode(Green, INPUT_PULLUP);
  pinMode(Blue, INPUT_PULLUP);
}

void loop() {
  // Skontroluj, či bolo tlačidlo stlačené a odoslať príslušný IR kód
  if (digitalRead(OnOff) == LOW) {
    Serial.println("Tlačidlo On/Off stlačené, odosielam IR kód...");
    IrSender.sendNEC(0xFB18E7, 32);  // Kód pre Power On/Off
    delay(700); // Pauza pre debouncing
  }

  else if (digitalRead(Adjust) == LOW) {
    Serial.println("Tlačidlo Adjust stlačené, odosielam IR kód...");
    IrSender.sendNEC(0xFBD827, 32);  // Kód pre Adjust
    delay(700); // Pauza pre debouncing
  }

  else if (digitalRead(Decrease) == LOW) {
    Serial.println("Tlačidlo Decrease stlačené, odosielam IR kód...");
    IrSender.sendNEC(0xFB38C7, 32);  // Kód pre Decrease
    delay(700); // Pauza pre debouncing
  }

  else if (digitalRead(Red) == LOW) {
    Serial.println("Tlačidlo Red stlačené, odosielam IR kód...");
    IrSender.sendNEC(0xFB20DF, 32);  // Kód pre Red
    delay(700); // Pauza pre debouncing
  }

  else if (digitalRead(Green) == LOW) {
    Serial.println("Tlačidlo Green stlačené, odosielam IR kód...");
    IrSender.sendNEC(0xFBA05F, 32);  // Kód pre Green
    delay(700); // Pauza pre debouncing
  }

  else if (digitalRead(Blue) == LOW) {
    Serial.println("Tlačidlo Blue stlačené, odosielam IR kód...");
    IrSender.sendNEC(0xFB609F, 32);  // Kód pre Blue
    delay(700); // Pauza pre debouncing
  }

  delay(100); // Krátka pauza na prevenciu viacerých stlačení naraz
}

