#include <SoftwareSerial.h>
SoftwareSerial ESPserial(5, 6); // RX | TX

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    ESPserial.begin(9600);  
    
 Serial.println("Remember to to set Both NL & CR in the serial monitor.");
    Serial.println("");
    ESPserial.println("AT+CIPMUX=1");
    delay(1000);
    ESPserial.println("AT+CIPSERVER=1,8888"); //open port 8888
    delay(1000);
    
    Serial.println("Ready");
    Serial.println("");    
}

void loop() {
    if ( ESPserial.available() )
    {  
      Serial.write( ESPserial.read() );
      ESPserial.flush();
    }
 
    // listen for user input and send it to the ESP8266
    if ( Serial.available() )
    {  
      ESPserial.write( Serial.read() );
    }
}
