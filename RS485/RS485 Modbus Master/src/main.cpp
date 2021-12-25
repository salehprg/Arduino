
#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
#include <SoftwareSerial.h>

SoftwareSerial rs485(4, 5); // RX, TX

#define baudrate  9600
#define LED  3

void setup() 
{
  
  rs485.begin(baudrate);
  Serial.begin(baudrate);

  //RS485Class client(Serial , 1 , 2 , 3);

  pinMode(LED , OUTPUT);
  digitalWrite(LED , LOW);

  if (!ModbusRTUClient.begin(baudrate))
  {
    rs485.println("Failed to start Modbus RTU Server!");
    while (1);
  }


}

int result = 0;

void loop() {
  
  
  int write = ModbusRTUClient.holdingRegisterWrite(1 , 0x40001 , result);

  rs485.print("Error Write: ");
  rs485.println(ModbusRTUClient.lastError());

  int coilValue = ModbusRTUClient.holdingRegisterRead(1 , 0x40002);
  
  rs485.print("Error Read: ");
  rs485.println(ModbusRTUClient.lastError());

  rs485.print("Result : ");
  rs485.println(coilValue);

  if(coilValue % 2 == 0)
  {
    digitalWrite(LED , HIGH);
  }
  else
  {
    digitalWrite(LED , LOW);
  }

  result++;

  delay(100);
}