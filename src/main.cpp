#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>

void recvOneChar();
void showNewData();

SoftwareSerial ss(6, 7);

Servo myservo;
int servoPin = 9;
int val;

char receivedChar;

boolean newData = false;

void setup()
{
  Serial.begin(9600);

  myservo.attach(9);
}

void loop()
{

  recvOneChar();
  showNewData();
  /*
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

      val = 100;                       // reads the value of the potentiometer (value between 0 and 1023)
      val = map(val, 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180)
      myservo.write(val);              // sets the servo position according to the scaled value
    }
  }
  */
}

void recvOneChar()
{
  if (Serial.available() > 0)
  {
    receivedChar = Serial.read();
    newData = true;
  }
}

void showNewData()
{
  if (newData == true)
  {
    Serial.print("This just in ... ");
    Serial.println(receivedChar);
    newData = false;
  }
}
