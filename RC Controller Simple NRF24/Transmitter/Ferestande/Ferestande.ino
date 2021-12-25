#include <RF24.h>
#include <SPI.h>

RF24 radio(9, 10);
const byte pipe[6] = "101000";

int fwdbkw = A0;
int leftright = A1;
int btnpin8 = 8;
int btnpin6 = 6;
int btnlight = 7;
int angle , condition ,  power ,btnstate , lightstate , btn6state, old_btnstate , old_lightstate , old_btn6state;
String message;
char result[50];
long mtime = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(btnpin8 , INPUT);
  pinMode(btnpin6 , INPUT);
  pinMode(btnlight , INPUT);
  old_btnstate = 0;
  old_lightstate = 0;
  old_btn6state = 0;
}


void loop() {
  message = "";
  
  int value = analogRead(leftright);
  angle = map(value, 0, 1023, 0, 180);

  if(value <= 537 && value >= 500)
  {
    angle = 90;
  }

  int valuep = analogRead(fwdbkw);
  power = map(valuep, 516, 1023, 0, 255);

//------- my petansiometer tolerance
  if(power > -35 && power < 35)
  {
    power = 0;
  }

  if(power < -220)
  {
    power = -255;
  }
//----------------------------  

  if(power < 0 )
  {
    condition = 0;
    power = power * (-1);
  }
  else
  {
    condition = 1;
  }
  
//------- my petansiometer tolerance
  if(power > 245)
  {
    power = 255;
  } 
//----------------------------------
  
  if (digitalRead(btnpin8) == HIGH && old_btnstate == 0 && millis() - mtime > 200)
  {
    btnstate = 1;
    old_btnstate = 1;
    mtime = millis();
  }
  else if (digitalRead(btnpin8) == HIGH && old_btnstate == 1 && millis() - mtime > 200)
  {
    btnstate = 0;
    old_btnstate = 0;
    mtime = millis();
  }

  //---------------------------------------

  if (digitalRead(btnlight) == HIGH && old_lightstate == 0 && millis() - mtime > 200)
  {
    lightstate = 1;
    old_lightstate = 1;
    mtime = millis();
  }
  else if (digitalRead(btnlight) == HIGH && old_lightstate == 1 && millis() - mtime > 200)
  {
    lightstate = 0;
    old_lightstate = 0;
    mtime = millis();
  }

   //---------------------------------------


   if (digitalRead(btnpin6) == HIGH && old_btn6state == 0 && millis() - mtime > 200)
  {
    btn6state = 1;
    old_btn6state = 1;
    mtime = millis();
  }
  else if (digitalRead(btnpin6) == HIGH && old_btn6state == 1 && millis() - mtime > 200)
  {
    btn6state = 0;
    old_btn6state = 0;
    mtime = millis();
  }

   //---------------------------------------
  message += angle;
  message += "|";
  message += power;
  message += "|";
  message += btnstate;
  message += "|";
  message += condition;
  message += "|";
  message += lightstate;
  message += "|";
  message += btn6state;
  message += "|";

  //message = angle|power|frontlight|condition(F/B)|toplight
  message.toCharArray(result , 50);

  if(radio.write(&result, sizeof(result)))
  {
      Serial.println(message);
  }

}
