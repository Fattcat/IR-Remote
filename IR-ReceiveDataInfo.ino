#include <IRremote.h>

const int recv_pin = 10;  // Pin, na ktorom je pripojený IR prijímač
IRrecv irrecv(recv_pin);  // Inicializácia IR prijímača
decode_results results;   // Objekt na ukladanie výsledkov dekódovania

void setup() {
  Serial.begin(9600);  // Inicializácia sériovej komunikácie
  irrecv.enableIRIn(); // Začiatok príjmu IR signálov
  Serial.println("Cakam na IR signal...");
}

void loop() {
  if (irrecv.decode(&results)) {  // Ak bol prijatý IR signál
    Serial.println("IR signal prijaty:");
    
    // Zobrazenie dekódovaných údajov
    Serial.print("Hodnota (hex): ");
    Serial.println(results.value, HEX);  // Vypíše hodnotu signálu v hexadecimálnom formáte
    
    Serial.print("Hodnota (dec): ");
    Serial.println(results.value, DEC);  // Vypíše hodnotu signálu v desiatkovej sústave
    
    Serial.print("Počet bitov: ");
    Serial.println(results.bits);  // Počet bitov v prijatom signáli
    
    // Rôzne ďalšie údaje z výsledkov (napr. čas trvania impulzu)
    Serial.print("Dĺžka trvania impulzu: ");
    Serial.println(results.rawlen);  // Dĺžka trvania prijatého signálu

    irrecv.resume();  // Pripravenie na ďalší signál
  }
}
