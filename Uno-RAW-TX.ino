#include <IRremote.h>

// #define IR_SEND_PIN 3 // This is not used because it is already in IRremote library or somewhere else defined

IRsend irsend; // Vytvorenie objektu irsend

uint16_t rawData[100] = {
  // ADD your RAW LENGHT (MAX 100) Code here
  // Set for other number like 68 or else Depends on your IR Remote ...
};

void setup() {
  Serial.begin(9600);
  // irsend.begin(); // This is not also used because i dont know (it works without)
  Serial.println("Pripravený na odosielanie IR signálu...");
}

void loop() {
  // Odošli RAW kód po každom spustení loop
  Serial.println("Odosielam IR kód...");
  irsend.sendRaw(rawData, 100, 38); // 38 je frekvencia 38 kHz (štandard pre väčšinu diaľkových ovládačov)
  Serial.println("IR kód bol odoslaný.");
  
  delay(5000); // 5-sekundová pauza medzi odoslaním
}
