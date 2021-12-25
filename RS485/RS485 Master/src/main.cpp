
#include <Arduino.h>
#include <SoftwareSerial.h>


bool stringComplete = false;
String inputString = "";

SoftwareSerial mySerial(2, 3);

int enablePin = 8;  

void setup() {

  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(enablePin, OUTPUT);

  delay(10); 

  digitalWrite(enablePin, HIGH);  //  (always high as Master Writes data to Slave)
}

int result = 0;

void loop() {

    if (Serial.available())
    {
      mySerial.write(Serial.read());
    }
}