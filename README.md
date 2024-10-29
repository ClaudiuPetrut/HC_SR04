#include <Arduino.h>
#include <Servo.h>
#include <HC_SR04.h>

// Connect pin D6 from arduino to ultrasonic sensor trig pin
// Connect pin D7 from arduino to ultrasonic sensor echo pin

Servo ESC, DIR;
uint16_t hc_distance;

void setup()
{
  ESC.attach(9);
  DIR.attach(10);
  ESC.writeMicroseconds(1500);
  DIR.writeMicroseconds(1500);
  initUltrasoundSensor();
  Serial.begin(9600);
}

void loop()
{
  hc_distance = getUltrasonicDistance();
  Serial.print(hc_distance);
  Serial.println(" CM");
  delay(50);
}
