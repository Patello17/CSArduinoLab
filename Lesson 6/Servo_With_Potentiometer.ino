#include <Servo.h>

Servo servo; // create servo object to control a servo

int POTENTIOMETER_PIN = 0;
int SERVO_PIN = 9;
int val;

void setup() {
  // put your setup code here, to run once:
  servo.attach(SERVO_PIN); // attach servo to correct pin
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(POTENTIOMETER_PIN); // get potentiometer value (0 - 1023)
  val = map(val, 0, 1023, 0, 180); // scale value (0 - 180)
  servo.write(val); // set servo position to value
  delay(15); // wait for servo to reach the position
}
