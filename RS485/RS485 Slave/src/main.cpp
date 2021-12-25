
#include <Arduino.h>

bool stringComplete = false;
String inputString = "";

int enablePin = 8;  

void setup() {
  Serial.begin(9600);

  pinMode(enablePin, OUTPUT);
  
  delay(10); 

  digitalWrite(enablePin, LOW);  //  (always high as Master Writes data to Slave)
}

int result = 0;

void loop() {

  while (Serial.available()) 
  {
    char inChar = (char)Serial.read();

    if((inChar >= 32 && inChar <= 127) || inChar == '\n')
    {
      inputString += inChar;

      if (inChar == '\n') {
        stringComplete = true;
      }
    }
  }
  inputString.trim();

  if(stringComplete)
  {
    Serial.print("I receive : ");
    Serial.println(inputString);
    stringComplete = false;
    inputString = "";
  }

}