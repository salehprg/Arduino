
#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
#include <SoftwareSerial.h>

SoftwareSerial rs485(4, 5); // RX, TX

#define Slave_ID  1
#define baudrate  9600
#define LED 3

void setup() {
  rs485.begin(baudrate);
  Serial.begin(baudrate);

  
  rs485.println("Modbus RTU Server LED");
  
  if (!ModbusRTUServer.begin(Slave_ID , baudrate))
  {
    rs485.println("Failed to start Modbus RTU Server!");
    while (1);
  }

  int conf = ModbusRTUServer.configureHoldingRegisters(0x00, 5);

  pinMode(LED , OUTPUT);
  digitalWrite(LED , LOW);

  rs485.print("conf : ");
  rs485.println(conf);
}

int result = 0;

void loop() {
  ModbusRTUServer.poll();

  int regValue = ModbusRTUServer.holdingRegisterRead(0x40001);

  int reg2Value = ModbusRTUServer.holdingRegisterWrite(0x40002 , regValue / 2);

  if(regValue % 2 == 0)
  {
    digitalWrite(LED , HIGH);
  }
  else
  {
    digitalWrite(LED , LOW);
  }

  delay(100);

}