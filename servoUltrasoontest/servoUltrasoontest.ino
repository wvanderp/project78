#include <NewPing.h>
#include <Servo.h>
int testPin = 9;
NewPing sensor(5,6,110);

const int deg = 2;
const int staps = 180/deg;
int array [staps];
Servo testServo;
void setup() 
{
  testServo.attach(testPin);
  Serial.begin(9600);
}

void loop() 
{
 check(deg,100);
 //move(0);
 //Serial.println(sensor.ping_cm());
}
void move(int degrees)
{
  if ((degrees >= - 91) && (degrees <= 91))
  {
    testServo.write(degrees + 90);
  }
}
void check(int stepSize,int delayTime)
{
  move(-90);
  delay(delayTime);
  for (int i = -90; i < 91; i += stepSize)
  {
    move(i + stepSize);
    delay(delayTime);
    array [(180 / (i +90)) - 1] = sensor.ping_cm();
    //Serial.println(sensor.ping_cm());
    Serial.println("");
    for (int j = 0;j < 6;j++)
    {
      Serial.print(array[j]);
      Serial.print("|");
    }
  }
  for (int i = 90; i > -91; i -= stepSize)
  {
    move(i - stepSize);
    delay(delayTime);
    array [(180 / (i+ 90)) - 1] = sensor.ping_cm();
    //Serial.println(array [(180 / (i+ 90)) - 1]);
    Serial.println("");
    for (int j = 0;j < 6;j++)
    {
      Serial.print(array[j]);
      Serial.print("|");
    }
  }
  delay(delayTime);
}

