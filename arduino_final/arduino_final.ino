#include <NewPing.h>

// Calculate based on max input size expected for one command
#define INPUT_SIZE 40
#include <SoftwareSerial.h>
#include <Servo.h>
double hoeken[99];
int timings[99];
int hoekInd;
int timingInd;

int motorLeft = 10;
int motorRight = 11;
Servo motorL;
Servo motorR;

int servoPin = 9;
Servo testServo;

int trigerPin = 5;
int echoPin = 4;
int maxDistance = 110;

NewPing sensor(trigerPin, echoPin, maxDistance);

enum avoidObjectState{
  Driving,
  NoClearPathInFront,
  DrivingToClearPath,
  DrivingParralel
};
enum avoidObjectState avoidState;

const int deg = 2;
const int staps = 180 / deg;
double distanceArray[90];
double degree;

SoftwareSerial mySerial(6, 7); // RX, TX
byte size;
char input[INPUT_SIZE + 1];

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(4800);
  motorL.attach(motorLeft);
  motorR.attach(motorRight);
  testServo.attach(servoPin);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  mySerial.println("Hello, world?");
}

void loop() { // run over and over
  /*if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }*/
 parseThis();
  
}


void parseThis(){
  // Get next command from Serial (add 1 for final 0)
  size = mySerial.readBytes(input, INPUT_SIZE);
  // Add the final 0 to end the C string
  input[size] = 0;
  // Read each command pair 
  char* command = strtok(input, ":");
  while (command != 0)
  {
      // Split the command in two values
      char* separator = strchr(command, '&');
      if (separator != 0)
      {
          
          // Actually split the string in 2: replace ':' with 0
          *separator = 0;
          double servoId = atof(command);
          
          ++separator;
          int position = atoi(separator);
          Serial.print(servoId);
          Serial.print(" & ");
          Serial.println(position);
          // Do something with servoId and position
          hoeken[hoekInd] = servoId;
          timings[timingInd] = position;
          Serial.print("hoeken[");
          Serial.print(hoekInd);
          Serial.print("]: ");
          Serial.println(hoeken[hoekInd]);
          Serial.print("timings[");
          Serial.print(timingInd);
          Serial.print("]: ");
          Serial.println(timings[timingInd]);
          hoekInd++;
          timingInd++;
          turn(servoId);
          forward(position);
          
      }
      // Find the next command in input string
      command = strtok(0, ":");
      check(deg,staps);
      switch(avoidState)
      {
        case Driving:
        if (checkIfClearFront() == false)
        {
          avoidState = Driving;
        }
        break;
        case NoClearPathInFront:
        degree = checkClearPath();
        turn(-1 * degree);
        avoidState = DrivingToClearPath;
        forward(2000);
        break;
        case DrivingToClearPath:
        if (checkIfObjectGone(degree) == true)
        {
          turn(degree);
          avoidState = DrivingParralel;
          forward(2000);
        }
        break;
        case DrivingParralel:
        if (checkIfObjectGone(degree) == true)
        {
          turn(degree);
          forward(2000);
          turn(-1 * degree);
          avoidState = Driving;
        }
        break;
      }
  }
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
void check(int stepSize, int delayTime)
{
  move(-90);
  for (int i = -90; i < 91; i += stepSize){
    move(i + stepSize);
    distanceArray[(i + 90)/2] = sensor.ping_cm();
    //Serial.println((180 / (i + 90)) - 1 + ":" + distanceArray[i+90]);
  }
  for (int i = 90; i > -91; i -= stepSize)
  {
    move(i - stepSize);
    distanceArray[(i + 90)/2] = sensor.ping_cm();
    //Serial.println((180 / (i + 90)) - 1 + ":" + distanceArray[i+90]);
  }
}

void move(int degrees)
{
  if ((degrees >= - 91) && (degrees <= 91))  
  {
    testServo.write(degrees + 90);
   }
}
boolean checkIfClearFront()
{
  if (((distanceArray[44] > 0) && (distanceArray[44] < 30)) || ((distanceArray[45] > 0) && (distanceArray[45] < 30)) || ((distanceArray[46] > 0) &&(distanceArray[47] < 30)))
  {
    return false;
  }
  else 
  {
    return true;
  }
}
double checkClearPath()
{
  for (int i = 0; i < 90; i++)
  {
    
  }
}
boolean checkIfObjectGone(int deg)
{
  
}


