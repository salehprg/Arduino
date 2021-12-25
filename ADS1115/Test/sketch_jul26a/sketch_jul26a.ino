#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */

void setup(void)
{
  Serial.begin(9600);

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
  ads.setDataRate(32);
  
  //Serial.println("Rate : ");
  //Serial.println(ads.getDataRate());
}

void loop(void)
{
  int16_t adc0, adc1, adc2, adc3;
  float volts0, volts1, volts2, volts3;

  adc0 = ads.readADC_SingleEnded(0);


  volts0 = ads.computeVolts(adc0);


  Serial.println(adc0);

  delay(100);
}
