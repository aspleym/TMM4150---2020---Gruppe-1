#include <Arduino.h>
#include <Servo.h>

Servo flag_servo;
int flag_pin = 13;
int flag_angle = 180;

void setup()
{
  flag_servo.attach(flag_pin);
  flag_servo.write(flag_angle);
  delay(3000);
}

void loop()
{
  delay(3000);
  // move from 0 to 180 degrees with a positive angle of 1
  for (flag_angle = 180; flag_angle > 0; flag_angle -= 4)
  {
    flag_servo.write(flag_angle);
    delay(50);
  }
  delay(3000);
  flag_angle = 180;
  flag_servo.write(flag_angle);
}