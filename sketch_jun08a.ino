#include <Servo.h>
int motorLeft = 10;
int motorRight = 11;
Servo motorL;
Servo motorR;
void setup() {
  // put your setup code here, to run once:
//pinMode(motorLeft,OUTPUT);
//pinMode(motorRight,OUTPUT);
motorL.attach(motorLeft);
motorR.attach(motorRight);
forward();
}

void loop() 
{
  // put your main code here, to run repeatedly:
  forward();
}
void motorLF()
{
  //analogWrite(motorLeft,11.5);
  motorL.write(180);
}
void motorLR()
{
  //analogWrite(motorLeft,21.7);
  motorL.write(0);
}
void motorRF()
{
  //analogWrite(motorRight,11.5);
  motorL.write(0);
}
void motorRR()
{
  //analogWrite(motorRight,21.7);
  motorL.write(180);
}
void motorIdle()
{
  //analogWrite(motorLeft,0);
  //analogWrite(motorRight,0);
  motorL.write(90);
  motorL.write(90);
  
}
void forward()
{
  motorLF();
  motorRF();
}
void reverse()
{
  motorLR();
  motorRR();
}
void left()
{
  motorLR();
  motorRF();
}
void right()
{
  motorLF();
  motorRR();
}

