#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(3);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(115200);
} 
 
 
void loop() 
{ 
  /*for(pos = 81; pos <= 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    //delay(15);                       // waits 15ms for the servo to reach the position 
    Serial.println(pos);
    delay(500);
  }*/
  for(pos = 81; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    //delay(500);                       // waits 15ms for the servo to reach the position 
    Serial.println(pos);
    delay(500);
  
  } 
} 
