#include <IRremote.h>

#define IR_LED_PIN 3  // Pin Arduino uno D3 | or Attiny85 (PB3)

IRsend irsend;

void setup() {
  // Nastavenie IR LED pinu ako výstup
  pinMode(IR_LED_PIN, OUTPUT);
  // irsend.begin();  // commented because it works in version good IRremote 2.6.1
  delay(1000);     // chvíľka na stabilizáciu
}

void loop() {
  // -- TIETO KODY SU FUNKCNE --
  // SAMSUNG: Power (NEC protocol)
  irsend.sendNEC(0xE0E040BF, 32);
  delay(500);

  // SONY: Power (Sony protocol)
  irsend.sendSony(0xA90, 12);  // 0xA90 = Power pre väčšinu Sony TV
  delay(500);

  // PANASONIC: Power (Panasonic protocol)
  irsend.sendPanasonic(0x4004, 0x100BCBD);  // Address, Command
  delay(500);

  // LG: Power (NEC-like)
  irsend.sendNEC(0x20DF10EF, 32);  // LG Power
  delay(500);

  // PHILIPS: Power (RC5 protocol)
  irsend.sendRC5(0x100C, 13); // 0x10 (TV), 0x0C (Power)
  delay(500);
}
