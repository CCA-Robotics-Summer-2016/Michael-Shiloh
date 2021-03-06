/*
 Controlling a servo position using a potentiometer 
 and print out the values being sent to the servo
 
 Useful for determining the limits of a given
 servo motor

 Based on Knob by Michal Rinott 
 <http://people.interaction-ivrea.it/m.rinott>

 Revisions 
 19 Jun 2016 - Michael Shiloh - added print()
  8 Nov 2013 - Scott Fitzgerald
 
 http://www.arduino.cc/en/Tutorial/Knob
*/

// Include the servo library
#include <Servo.h>

// Create the servo object
Servo myservo;  // create servo object to control a servo

// Declare some variables
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  Serial.println(val);
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}

