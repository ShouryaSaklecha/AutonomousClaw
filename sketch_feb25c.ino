// --------------------------------------------------------------------------------------
// Code for Autonomous Claw: APSC 101
// Author: Shourya Saklecha
// Sources: Example codes in Arduino IDE; APSC 101
--------------------------------------------------------------------------------------
#include <Servo.h>
#define VCC_PIN 13
#define TRIGGER_PIN 12    // sonar trigger pin will be attached to Arduino pin 12
#define ECHO_PIN 11       // sonar echo pint will be attached to Arduino pin 11
#define GROUND_PIN 10     //
#define MAX_DISTANCE 200  // maximum distance set to 200 cm
#define Threshold_Distance 10 // Defines the required distance to be 10 cm

// defines variables
long duration;
int distance;

void setup() {
  Serial. begin(9600);            // set data transmission rate to communicate with computer
  pinMode(ECHO_PIN, INPUT) ;  
  pinMode(TRIGGER_PIN, OUTPUT) ;
  pinMode(GROUND_PIN, OUTPUT);    // tell pin 10 it is going to be an output
  pinMode(VCC_PIN, OUTPUT);       // tell pin 13 it is going to be an output
  digitalWrite(GROUND_PIN,LOW);   // tell pin 10 to output LOW (OV, or ground)
  digitalWrite(VCC_PIN, HIGH) ;   // tell pin 13 to output HIGH (+5V)

}

void loop() {
  digitalWrite(TRIGGER_PIN, LOW);   // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(20);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance= duration*0.034/2;       // Calculating the distance

  // if the distance measurement becomes extremely high, it is likely an error.  
  // Default to a maximum value of MAX_DISTANCE to identify this condition.
  
  if (distance > MAX_DISTANCE)   
    { 
      distance = MAX_DISTANCE;
      }
  if (distance<Threshold_Distance)
  {
    delay(1000);
    Servo myservo;   // create servo object to control a servo
 myservo.attach(9); 
int pos = 10;       // sets initial position to 10 to make a rotation

while(pos<=270)
{
  myservo.write(pos);
  delay(20);
  pos++;           // increase the position value to move the servo
}

delay(6000);      // Waits 6 seconds
while (pos>=0)
{ 
  myservo.write(pos);
  delay(20);
  pos--;        // Goes from 270 to 0, basically just brings back the servo to initial position
}
}

}
