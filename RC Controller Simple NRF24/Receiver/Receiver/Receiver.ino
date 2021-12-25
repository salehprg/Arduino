#include <Servo.h>
#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8);  //ce , csn

const byte pipe[6] = "101000";

int FB = 4;
int frontlight = 9;
int outpin10 = 10;
int in1 = 5;
int in2 = 3;
int highlight =2;
int RL = 6;
Servo leftright;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, pipe);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode(highlight , OUTPUT);
  pinMode(in1 , OUTPUT);
  pinMode(in2 , OUTPUT);
  pinMode(FB , OUTPUT);
  pinMode(frontlight , OUTPUT);
  pinMode(outpin10 , OUTPUT);
  leftright.attach(RL);
  delay(250);
  leftright.write(90);
  digitalWrite(frontlight , HIGH);
  leftright.write(90);
  radio.printDetails();
  //
}

int servoangle , power , condition , lightstate , breakline , secondbreakline , thirdbreakline , fourthbreakline , fifthbreakline , sixthbreakline , pin10state, highlightstate;

String message;

void loop() {
  if (radio.available()) {
//message = angle|power|frontlight|condition(F/B)|toplight
    char text[50] = {0};
    radio.read(&text, sizeof(text));

    message = String(text);

    breakline = message.indexOf("|");
    servoangle = message.substring(0 , breakline).toInt();
    delay(10);

    secondbreakline = message.indexOf("|" , breakline + 1);
    power = message.substring(breakline + 1 , secondbreakline).toInt();

    thirdbreakline = message.indexOf("|" , secondbreakline + 1);
    lightstate = message.substring(secondbreakline + 1 , thirdbreakline).toInt();

    fourthbreakline = message.indexOf("|" , thirdbreakline + 1);
    condition = message.substring(thirdbreakline + 1, fourthbreakline).toInt();

    fifthbreakline = message.indexOf("|" , fourthbreakline + 1);
    highlightstate = message.substring(fourthbreakline + 1, fifthbreakline).toInt();

    sixthbreakline = message.indexOf("|" , fifthbreakline + 1);
    pin10state = message.substring(fifthbreakline + 1, sixthbreakline).toInt();
    
 //--------------------------------------------------   
 
      if (lightstate == 1)
      {
        digitalWrite(frontlight , HIGH);
      }
      else if(lightstate == 0)
      {
        digitalWrite(frontlight , LOW);
      }

//-------------------------------------------------- 
 
      if (highlightstate == 1)
      {
        digitalWrite(highlight , HIGH);
      }
      else if(highlightstate == 0)
      {
        digitalWrite(highlight , LOW);
      }
      
 //-------------------------------------------------- 

      if (pin10state == 1)
      {
        digitalWrite(outpin10 , HIGH);
      }
      else if(pin10state == 0)
      {
        digitalWrite(outpin10 , LOW);
      }
      
 //-------------------------------------------------- 
      if(condition == 0)
      {
        digitalWrite(FB , HIGH);
        analogWrite(in1, power);
        digitalWrite(in2, LOW);
      }
      else if(condition == 1)
      {     
        digitalWrite(FB , HIGH);
        digitalWrite(in1, LOW);
        analogWrite(in2, power);
      }
      
 //--------------------------------------------------       
      
      leftright.write(servoangle);
    
    Serial.println(message); 
  }
  else
  {
    turnoff();
  }
}

void turnoff()
{
    leftright.write(90);
    digitalWrite(FB , HIGH);
    analogWrite(in1, 0);
    digitalWrite(in2, LOW);
    digitalWrite(frontlight , LOW);
    digitalWrite(outpin10 , LOW);
    digitalWrite(highlight , LOW);
}
