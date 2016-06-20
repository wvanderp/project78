#include <Servo.h>

int motorLeft = 10;
int motorRight = 11;
int servoPi = 9;
Servo motorL;
Servo motorR;
Servo testServo;

void setup() {
  motorL.attach(motorLeft);
  motorR.attach(motorRight);
  testServo.write(90);
}

void loop() {
  motorL.write(90);
  motorR.write(90);
  }
