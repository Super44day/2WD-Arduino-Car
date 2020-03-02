//ARDUINO OBSTACLE AVOIDING CAR

//Before uploading the code you have to install the necessary library
//AFMotor Library https://github.com/Super44day/2WD-Arduino-Car
//NewPing Library https://github.com/Super44day/2WD-Arduino-Car

// To Install the libraries go to sketch >> Include Library >> Add .ZIP File >> Select the Downloaded ZIP files From the Above links //


#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 


#define TRIG_PIN A1 
#define ECHO_PIN A0   //Echo and Trig pin connected with A0 A1 pin
#define MAX_DISTANCE 200
#define MAX_SPEED 190 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
AF_DCMotor motorL(3); //M3 connected with left wheel
AF_DCMotor motorR(4); //M4 connnected with right wheel

Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {
  myservo.attach(10);  
  myservo.write(115); //Adjust the servo to look forward
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);

}
void loop() {
 int distanceR = 0;
 int distanceL = 0;
 delay(40);
 
 if(distance<=15)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance = readPing();
}

//get distance of right
int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

//get distance of left
int lookLeft()
{
    myservo.write(180); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

//ultrasonic sensor get distance information
int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motorL.run(RELEASE); 
  motorR.run(RELEASE);

  } 
  
void moveForward() {
 if(!goesForward)
  {
    goesForward=true;
    motorL.run(FORWARD);      
    motorR.run(FORWARD);
 
   for (speedSet = 50; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motorL.setSpeed(speedSet);
    motorR.setSpeed(speedSet);

    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motorL.run(BACKWARD);      
    motorR.run(BACKWARD);

  for (speedSet = 50; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motorL.setSpeed(speedSet);
    motorR.setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
  motorL.run(FORWARD);
  delay(500);
  motorL.run(FORWARD);
  motorR.run(FORWARD);
 
} 
 
void turnLeft() {
  motorR.run(FORWARD);  
  delay(500);
  motorL.run(FORWARD);
  motorR.run(FORWARD);

}  
