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

void forward(int travelTime)
{
    motorLF();
    motorRF();
    delay(travelTime);
    motorIdle();
}

void reverse(int travelTime)
{
  motorLR();
  motorRR();
  delay(travelTime);
  motorIdle();
}

void left(double degree)
{
  motorLR();
  motorRF();
  delay(degree * 7);
  motorIdle();
}

void right(double degree)
{
  motorLF();
  motorRR();
  delay(degree * 7);
  motorIdle();
}
void turn(double degree)
{
  if (degree < 0)
  {
    left(-1 * degree);
  }
  else if (degree > 0)
  {
    right(degree);
  }
}
