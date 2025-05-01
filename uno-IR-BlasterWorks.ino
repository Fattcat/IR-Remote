#include <IRremote.h>

// Definuj pin pre IR vysielač
const int irPin = 3; // IR Transmit Diode Pin D3 because it is PWM Pin !!!!
IRsend irsend; // Objekt pre IR vysielač

void setup() {
  //irsend.begin(); DONT USE IT BECAUSE IRremote Version 2.6.1 does NOT WORKS WITH irsend.begin(); !
}

void loop() {
  // Odoslanie IR kódov pre vypnutie rôznych zariadení

  // AB CryptoBox Power OFF
  irsend.sendNEC(0x20DF10EF, 32); // 32-bitový kód
  delay(500); // Čakaj 2 sekundy pred ďalším príkazom

  // Samsung TV Power OFF
  irsend.sendNEC(0xE0E040BF, 32); // 32-bitový kód
  delay(500); // Čakaj 2 sekundy pred ďalším príkazom

  // LG TV Power OFF
  irsend.sendNEC(0x20DF40BF, 32); // 32-bitový kód
  delay(500); // Čakaj 2 sekundy pred ďalším príkazom

  // Sony TV Power OFF
  irsend.sendSony(0xA90, 12); // 12-bitový kód pre Sony
  delay(500); // Čakaj 2 sekundy pred ďalším príkazom

  // Panasonic TV Power OFF
  irsend.sendPanasonic(0xB0E0, 16); // 16-bitový kód pre Panasonic
  delay(500); // Čakaj 2 sekundy pred ďalším príkazom

  // Sharp TV Power OFF
  irsend.sendSharp(0x2A5, 16); // 16-bitový kód pre Sharp
  delay(500); // Čakaj 2 sekundy pred ďalším príkazom

  // Hisense TV Power OFF
  irsend.sendNEC(0x32F1, 32); // 32-bitový kód pre Hisense
  delay(500); // Čakaj 2 sekundy pred ďalším príkazom

  // Vizio TV Power OFF
  irsend.sendNEC(0x20DF01FE, 32); // 32-bitový kód pre Vizio
  delay(500); // Čakaj 2 sekundy pred ďalším príkazom

  // Toshiba TV Power OFF (nie je priamo podporované v knižnici)
  // Môžeš zvoliť alternatívny kód, napríklad pomocou NEC
  irsend.sendNEC(0x70C0, 32); // 32-bitový kód pre Toshiba (príklad s NEC)
  delay(500); // Čakaj 2 sekundy pred ďalším príkazom
}
