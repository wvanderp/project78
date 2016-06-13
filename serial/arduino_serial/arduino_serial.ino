// Calculate based on max input size expected for one command
#define INPUT_SIZE 40
#include <SoftwareSerial.h>
double hoeken[99];
int timings[99];
int hoekInd;
int timingInd;

SoftwareSerial mySerial(6, 7); // RX, TX
byte size;
char input[INPUT_SIZE + 1];

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(4800);
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
      }
      // Find the next command in input string
      command = strtok(0, ":");

  }
}

