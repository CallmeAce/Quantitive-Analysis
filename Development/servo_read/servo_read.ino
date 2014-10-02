// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo servo_top;  // create servo object to control a servo 
                  // a maximum of eight servo objects can be created 
Servo servo_base;


int pos = 0;    // variable to store the servo position 
long duration, distance;
void setup() 
{ 
  servo_top.attach(11);  // attaches the servo on pin 11 to the servo object 
  servo_base.attach(10); 
  Serial.begin(9600);

} 
 
 
void loop() 
{ 
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
} 
