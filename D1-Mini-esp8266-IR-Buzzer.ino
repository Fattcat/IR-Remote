#include <IRremoteESP8266.h>
#include <IRrecv.h>

const uint16_t kRecvPin = D2;  // GPIO4 na D1 Mini
const uint8_t buzzerPin = D1; // GPIO5 na D1 Mini

IRrecv irrecv(kRecvPin);
decode_results results;

void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn();  // Inicializácia IR prijímača
  
  pinMode(buzzerPin, OUTPUT);  // Nastavenie pinu bzučiaka ako výstup
}

void loop() 
{
  if (irrecv.decode(&results)) 
  {
    Serial.print("Received IR code: ");
    Serial.println(results.value, HEX);
    
    // Reakcia na konkrétny IR kód
    if (results.value == 0xFFA25D) // CHANGE THIS WITH YOUR VALUE
    {
      // Reakcia na kód "FFA25D" - bzučiak zaznie raz
      tone(buzzerPin, 1000, 200);  // Tón s frekvenciou 1000 Hz a trvaním 200 ms
    }
    else if (results.value == 0x52A3D41F) // CHANGE THIS WITH YOUR VALUE
    {
      // Reakcia na kód "52A3D41F" - bzučiak zaznie 3x rýchlo
      for (int i = 0; i < 3; i++) 
      {
        tone(buzzerPin, 1000, 100);  // Tón s frekvenciou 1000 Hz a trvaním 100 ms
        delay(100);  // Pauza medzi tónmi
      }
    }
    
    irrecv.resume();  // Pokračovanie v prijímaní ďalších signálov
  }
}
