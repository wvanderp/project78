#include "lib/NewPing.h"
#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port

}

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}










int trigerPin = 5;
int echoPin = 6;
int maxDistance = 110;
NewPing sensor(trigerPin, echoPin, maxDistance);

const int deg = 2;
const int staps = 180 / deg;

int servoPin = 9;
Servo testServo;

void setup() {
  testServo.attach(servoPin);
// Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("hallo hard serial");
  
  mySerial.begin(4800);
  mySerial.println("hallo soft serial");
}

void loop(){
  int pingDelay = 50;
//  check(deg, 50);
  for(int i =0; i <=180;i++){
    mySerial.print(i);
    mySerial.print(":");
    mySerial.println(random(0,110));
    delay(1000);
  }
}

//void check(int stepSize, int delayTime){
//  move(-90);
//  for (int i = -90; i < 91; i += stepSize){
//    move(i + stepSize);
//    Serial.print((180 / (i + 90)) - 1]);
//    Serial.print(":");
//    Serial.println(sensor.ping_cm());
//  }
//  
//  for (int i = 90; i > -91; i -= stepSize){
//    move(i - stepSize);
//    Serial.print((180 / (i + 90)) - 1]);
//    Serial.print(":");
//    Serial.println(sensor.ping_cm());
//  }
//}
//
//void move(int degrees){
//  if ((degrees >= - 91) && (degrees <= 91))  {
//    testServo.write(degrees + 90);
//  }
//}

