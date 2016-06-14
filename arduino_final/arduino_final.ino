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

SoftwareSerial mySerial(6, 7); // RX, TX
byte size;
char input[INPUT_SIZE + 1];

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(4800);
  motorL.attach(motorLeft);
  motorR.attach(motorRight);
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



