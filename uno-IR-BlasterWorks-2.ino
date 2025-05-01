#include <IRremote.h>

const int irPin = 3;
IRsend irsend;

void setup() {
  // irsend.begin(); // Not need to use, we are working with IRremote v2.6.1
}

void loop() {
  // TV zariadenia
  irsend.sendNEC(0x20DF10EF, 32); delay(500); // AB CryptoBox Power OFF
  irsend.sendNEC(0xE0E040BF, 32); delay(500); // Samsung TV Power OFF
  irsend.sendNEC(0x20DF40BF, 32); delay(500); // LG TV Power OFF
  irsend.sendSony(0xA90, 12);     delay(500); // Sony TV Power OFF
  irsend.sendPanasonic(0xB0E0, 16); delay(500); // Panasonic TV Power OFF
  irsend.sendSharp(0x2A5, 15);    delay(500); // Sharp TV Power OFF
  irsend.sendNEC(0x32F1, 32);     delay(500); // Hisense TV Power OFF
  irsend.sendNEC(0x20DF01FE, 32); delay(500); // Vizio TV Power OFF
  irsend.sendNEC(0x70C0, 32);     delay(500); // Toshiba TV Power OFF (príklad)

  // LED pás – vypnutie
  irsend.sendNEC(0x00FF9867, 32); delay(500); // LED pás – červená
  irsend.sendNEC(0x00FF58A7, 32); delay(500); // LED pás – zelená
  irsend.sendNEC(0x00FF30CF, 32); delay(500); // LED pás – modrá
  irsend.sendNEC(0x00FF22DD, 32); delay(500); // LED pás OFF
  irsend.sendNEC(0x00FF02FD, 32); delay(500); // LED pás ON

  // Žalúzie / Roletový motor
  irsend.sendNEC(0x00FF18E7, 32); delay(500); // Žalúzie OPEN
  irsend.sendNEC(0x00FF4AB5, 32); delay(500); // Žalúzie CLOSE
  irsend.sendNEC(0x00FF38C7, 32); delay(500); // Žalúzie STOP

  // Ventilátor
  irsend.sendNEC(0x00FF629D, 32); delay(500); // Ventilátor rýchlosť +
  irsend.sendNEC(0x00FFE21D, 32); delay(500); // Ventilátor rýchlosť -
  irsend.sendNEC(0x00FFA25D, 32); delay(500); // Ventilátor ON/OFF

  // Stropný ventilátor (príklad)
  irsend.sendNEC(0x00FF906F, 32); delay(500); // Fan Power
  irsend.sendNEC(0x00FF10EF, 32); delay(500); // Fan Speed +
  irsend.sendNEC(0x00FF50AF, 32); delay(500); // Fan Speed -

  // Projektor – vypnutie
  irsend.sendNEC(0xA55A38C7, 32); delay(500); // Projektor OFF (častý NEC kód)

  // Add more IR codes ...
}
