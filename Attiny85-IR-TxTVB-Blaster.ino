#include <IRremote.h>
// USE Arduino IRremote version 2.0.1 !
// DONT USE  IRremote version 2.6.1 !
// Používaj digitálny pin 1 na ATtiny85 (PB1)
#define IR_LED_PIN 1 // OR pin 0

IRsend irsend;

void setup() {
  // Nastav výstupný pin pre IR LED
  //irsend.begin();
}

void loop() {
  irsend.sendNEC(0x20DF10EF, 32); // AB CryptoBox Power OFF
  delay(500);

  irsend.sendNEC(0xE0E040BF, 32); // Samsung TV Power OFF
  delay(500);

  irsend.sendNEC(0x20DF40BF, 32); // LG TV Power OFF
  delay(500);

  irsend.sendNEC(0x00FF22DD, 32); // LED pás OFF
  delay(1000);
}
