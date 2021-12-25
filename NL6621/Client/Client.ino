#include <SoftwareSerial.h>
#define SSID "ma az donia aghabim!"
#define PASS "Saleh-1379"
#define CONNECT_ATTEMPTS 2

SoftwareSerial esp8266(2,3);
 
void setup() {
 
  Serial.begin(9600);
  esp8266.begin(9600);
 
  delay(1000);
}
 
void loop() {

  while(Serial.available()) {
    int inByte = Serial.read();
    esp8266.write(inByte);
  }
  while(esp8266.available()) {
    int inByte = esp8266.read();
    Serial.write(inByte);
  }
}
 
