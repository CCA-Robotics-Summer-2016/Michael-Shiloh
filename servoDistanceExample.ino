/*
 * Using an ultrasonic distance measuring sensor mounted on a servo motor, 
 * survey the space around 
 * and figure out the best path forward
 * 
 * 6/17/16 - MS - fixed some bugs, added print()
 * 6/15/16 - MS - Initial coding
 * 
 */




#include <Servo.h>

// Global array of measurements
long measurements[180];
long averages[18];

// the ultrasonic distance measuring sensor sits on top of this servo
Servo myServo;
const int servoPin = 9;

// ultrasonic distance measuring sensor
const int trigPin = 12;
const int echoPin = 11;

// Control pins for the right half of the H-bridge
const int enable2 = 3; // PWM pin for speed control
const int in3 = 8;
const int in4 = 7;

//other half
const int enable1 = 6; // PWM pin for speed control
const int in1 = 4;
const int in2 = 2;

// sweep 180 degrees and populate the measurements array
void sweepAndMeasure() {
  Serial.println("Hello from sweepAndMeasure");

  // VERY IMPORTANT: Note that degree = degree++ is
  // worse than unnecessary as it causes problems
  for (int degree = 0; degree < 180; degree++) {

    myServo.write(degree);
    delay(15);

    measurements[degree] = measureDistance();
  }

}

// Take a measurement using the ultrasonic discance
// measuring sensor and return the distance in cm
// returns -1 if an error occurrs

long measureDistance() {
  long myDuration, distance;
  Serial.println("Hello from measureDistance");

  // measure how far anything is from us
  // send the pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); // low for 2 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // high for 10 microseconds
  digitalWrite(trigPin, LOW);
  myDuration = pulseIn(echoPin, HIGH); // measure the time to the echo
  distance = (myDuration / 2) / 29.1; // calculate the distance in cm

  // if reading is out of range, make it -1

  if (distance <= 0 || distance >= 200) {
    distance = -1;
  }
  return distance;
}

void setup() {

  Serial.begin (9600);
  Serial.println("hello from michaels program version 0.1");

  myServo.attach(servoPin);

  // pins for the ultrasonic distance measuring sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // motors
  pinMode( enable1, OUTPUT);
  pinMode( in1, OUTPUT);
  pinMode( in2, OUTPUT);

  pinMode( enable2, OUTPUT);
  pinMode( in3, OUTPUT);
  pinMode( in4, OUTPUT);

  // Set the speed to 100, which is pretty slow
  analogWrite (enable1, 100);
  analogWrite (enable2, 100);

  // later on, move these to loop()
  // look around and see what's nearby
  sweepAndMeasure();

  // look at measurements in 10 degree chunks
  averageInTenDegreeChunks();
}
void loop() {

  // finally decide where to go

}

void averageInTenDegreeChunks() {
  Serial.println("Hello from averageInTenDegreeChunks");

  for (int degree = 0; degree < 180; degree = degree + 10) {

    averages[degree / 10] = averageTheseTen(degree);

  }
}

int averageTheseTen ( int startHere ) {

  Serial.println("Hello from averageTheseTen");
  int sum = 0;
  int validMeasurements = 10;
  int average;

  for (int degree = startHere; degree < startHere + 10; degree ++) {
    Serial.print(measurements[degree]);
    Serial.print("\t");
    if (-1 == measurements[degree] ) {
      // skip this measurement
      validMeasurements--;
    } else {
      sum = sum + measurements[degree];
    }
  }

  average = sum / validMeasurements;
  Serial.print("average: ");
  Serial.print(average);
  Serial.print("\t");
  Serial.print("valid measurements: ");
  Serial.print(validMeasurements);
  Serial.println("");
  return average;
}









