#include <TimerObject.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <NewPing.h>

void checkEverything();
void check(int stepSize, int delayTime);
void move(int degrees);
boolean checkIfClearFront();
double checkClearPath();
boolean checkIfObjectGone(int deg);
double lookLeftOrRight(int deg);

double turnAfterDrive;
TimerObject *driveTimer = new TimerObject(2000);
TimerObject *QRTimer = new TimerObject(2000);

// Calculate based on max input size expected for one command
#define INPUT_SIZE 40
double hoeken[99];
int timings[99];
int hoekInd;
int timingInd;

int motorLeft = 10,motorRight = 11;
Servo motorL, motorR, testServo;
int servoPin = 9;
int trigerPin = 5,echoPin = 4;
int maxDistance = 250;

NewPing sensor(trigerPin, echoPin, maxDistance);

enum avoidObjectState{Driving, NoClearPathInFront, DrivingToClearPath,DrivingParralel};
enum avoidObjectState avoidState;

const int deg = 2;
const int steps = 180 / deg;
double distanceArray[180/deg];
double degree;

SoftwareSerial mySerial(6, 7); // RX, TX
byte size;
char input[INPUT_SIZE + 1];
void setup() 
{
  // Open serial communications and wait for port to open:
  Serial.begin(4800);
  motorL.attach(motorLeft);
  motorR.attach(motorRight);
  testServo.attach(servoPin);
  driveTimer -> setOnTimer(&motorIdle);
  QRTimer -> setOnTimer(&motorIdle);
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
 driveTimer->Update();
 QRTimer -> Update();
 parseThis();
 //objectAvoidanceDemo();
}

void parseThis()
{
  // Get next command from Serial (add 1 for final 0)
  size = mySerial.readBytes(input, INPUT_SIZE);
  // Add the final 0 to end the C string
  input[size] = 0;
  // Read each command pair 
  char* command = strtok(input, ":");
  while (command != 0)
  {
      //driveTimer->Update();
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
          driveTimer->setOnTimer(*motorIdle);
          turn(servoId);
          forwardQR(position);
      }
      // Find the next command in input string
      command = strtok(0, ":");
      
  }
}
void objectAvoidanceDemo()
{
  if (checkIfClearFront() == false)
          {
            QRTimer->Pause();
            motorIdle();
          }
   else
   {
    QRTimer->Resume();
   }
          
}
void objectAvoidance()
{
  check(deg,steps);
  switch(avoidState)
  {
        case Driving:
          if (checkIfClearFront() == false)
          {
            avoidState = NoClearPathInFront;
          }
          break;
        case NoClearPathInFront:
          degree = checkClearPath();
          motorIdle();
          QRTimer->Pause();
          turn(-1 * degree);
          avoidState = DrivingToClearPath;
          forward(2000);
          break;
        case DrivingToClearPath:
          if (checkIfObjectGone(degree) == true)
          {
             motorIdle();
             delay(500);
             turn(degree*2 - 90);
             avoidState = DrivingParralel;
             driveTimer->setOnTimer(*motorIdle);
             forwardQR(3000);
          }
          break;
       case DrivingParralel:
          if (checkIfObjectGone(lookLeftOrRight(degree)) == true)
          {
             turn(degree*2 - 90);
             QRTimer->Pause();
             //driveTimer->setOnTimer(*makeTurnAfterDrive);
             motorLF();
             motorRF();
             delay(2000);
             motorIdle();
             motorLF();
             motorRR();
             delay(7* degree);
             motorIdle();
             avoidState = Driving;
             forwardQR(3000);
           }
           break;
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
  if (((distanceArray[44] > 0) && (distanceArray[44] < 30)) || ((distanceArray[45] > 0) && (distanceArray[45] < 30)) || ((distanceArray[46] > 0) &&(distanceArray[46] < 30)))
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
  if ((distanceArray[0] >= distanceArray[90]) && (distanceArray[0] != 0) && (distanceArray[90] != 0))
  {
    return 0;
  }
  else if ((distanceArray[0] < distanceArray[90]) && (distanceArray[0] != 0) && (distanceArray[90] != 0))
  {
    return 90;
  }
  else
  {
    return 0;
  }
  
}
boolean checkIfObjectGone(int deg)
{
  if ((distanceArray[deg -1] > 30) || (distanceArray[deg] > 30) || (distanceArray[deg+1] > 30))
  {
    return true;
  }
}
double lookLeftOrRight(int deg)
{
  if (deg < 45)
  {
    return 0;
  }
  else
  {
    return 90;
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
    driveTimer->setInterval(travelTime);
    driveTimer->Start();
}
void forwardQR(int travelTime)
{
    motorLF();
    motorRF();
    QRTimer->setInterval(travelTime);
    QRTimer->Resume();
}

void reverse(int travelTime)
{
  motorLR();
  motorRR();
  driveTimer->setInterval(travelTime);
  driveTimer->Start();
}

void left(double degree)
{
  motorLR();
  motorRF();
  driveTimer->setInterval(degree * 9);
  driveTimer->Start();
}

void right(double degree)
{
  motorLF();
  motorRR();
  driveTimer->setInterval(degree * 9);
  driveTimer->Start();
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
void makeTurnAfterDrive()
{
  if (turnAfterDrive < 0)
  {
    left(-1 * turnAfterDrive);
  }
  else if (turnAfterDrive > 0)
  {
    right(turnAfterDrive);
  }
}


