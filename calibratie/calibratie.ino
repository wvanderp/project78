#include <Servo.h>

int motorLeft = 10;
int motorRight = 11;

Servo motorL;
Servo motorR;

void setup() {
  motorL.attach(motorLeft);
  motorR.attach(motorRight);
}

void loop() {
  motorL.write(90);
  motorR.write(90);
  }
