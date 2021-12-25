
int in1 = 2;
int in2 = 4;
int ena = 5;
int pwminput = A0;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(in1 , OUTPUT);
  pinMode(in2 , OUTPUT);
  pinMode(ena , OUTPUT);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

int pwm;

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(pwminput);
  pwm = map(value, 516, 1023, 0, 255);

  if(pwm < 0 )
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    pwm = pwm * (-1);
  }
  else
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  if(pwm > 255)
  {
    pwm = 255;
  }
  analogWrite(ena , pwm);
  Serial.println(pwm);
}
