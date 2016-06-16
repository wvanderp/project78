#include <Servo.h>
int motorLeft = 10;
int motorRight = 11;
Servo motorL;
Servo motorR;

void setup() 
{
  // put your setup code here, to run once:
  //pinMode(motorLeft,OUTPUT);
  //pinMode(motorRight,OUTPUT);
  motorL.attach(motorLeft);
  motorR.attach(motorRight);
}

void loop()
{
  left(90);
  delay(5000);
  right(90);
  delay(5000);
  forward(2000);
  delay(5000);
}

void motorLF()
{
  motorL.write(180);
}

void motorLR()
{
  motorL.write(0);
}

void motorRF()
{
  motorR.write(0);
}

void motorRR()
{
  motorR.write(180);
}

void motorIdle()
{
  motorL.write(90);
  motorR.write(90);
}
void reverse(int travelTime)
{
    motorLF();
    motorRF();
    delay(travelTime);
    motorIdle();
}

void forward(int travelTime)
{
  motorLR();
  motorRR();
  delay(travelTime);
  motorIdle();
}

void left(int degree)
{
  motorLR();
  motorRF();
  delay(degree * 7);
  motorIdle();
}

void right(int degree)
{
  motorLF();
  motorRR();
  delay(degree * 7);
  motorIdle();
}


