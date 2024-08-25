// Receive and show IR Signal Data in Serial Monitor

#include <IRremoteESP8266.h>
#include <IRrecv.h>

const uint16_t kRecvPin = D2;  // GPIO4 na D1 Mini

// ---------------------------------
// Connection
// IR Receiver --> esp8266 D1 Mini
// VCC --> 5V
// GND --> GND
// Pin --> D2
// ---------------------------------

IRrecv irrecv(kRecvPin);
decode_results results;

void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn();  // Inicializácia IR prijímača
}

void loop() 
{
  if (irrecv.decode(&results)) 
  {
    Serial.print("Received IR code: ");
    Serial.println(results.value, HEX);
    irrecv.resume();  // Pokračovanie v prijímaní ďalších signálov
  }
}
