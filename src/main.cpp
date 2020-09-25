#include <Arduino.h>
#include <Wire.h>

int ledPin = 13;
void blinkLED(int inputVal);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // listen for the data from raspberry pi
  if (Serial.available() > 0)
  {
    // read a numbers from serial port
    int inputVal = Serial.parseInt();
    if (inputVal > 0)
    {
      //Serial.print("Your input is: ");
      //Serial.println(String(inputVal));
      // Here blink the LED
      blinkLED(inputVal);
    }
  }
}

void blinkLED(int inputVal)
{
  for (int i = 0; i < inputVal; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
}
