//Arduino IR Remote Control Car

//Before uploading the code you have to install the necessary library
//AFMotor Library https://github.com/Super44day/2WD-Arduino-Car
//IRremote Library https://github.com/Super44day/2WD-Arduino-Car

// To Install the libraries go to sketch >> Include Library >> Add .ZIP File >> Select the Downloaded ZIP files From the Above links //



#include <AFMotor.h>
#include <IRremote.h>
#include <Servo.h> 

Servo myservo;   //Create servo instance

int RECV_PIN = 2; //Define input pin of IR Receiver
IRrecv irrecv(RECV_PIN);
decode_results results;

AF_DCMotor motorL(3);//Left Wheel Connected with M3
AF_DCMotor motorR(4);//Right whell connnected with M4


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  
  myservo.attach(10);  
  myservo.write(115); //Adjust the servo to look forward
  
  motorR.setSpeed(150);
  motorL.setSpeed(150);// Set speed of 2 wheel,range from 0~255
  
  motorL.run(RELEASE);
  motorR.run(RELEASE);

}

void loop(){
  if (irrecv.decode(&results)) 
  {
    Serial.println(results.value);//Print the encoding number of different keys on Serial monitor
    switch(results.value){
      case 16718055: {move_ahead();delay(1500);stop();break; }// 16718055 corresponds to the forward key, move adead for 1.5s and stop
      case 16730805: {move_backwards();delay(1500);stop();break; }   // 16730805 corresponds to the backward key
      case 16716015: {turn_left();delay(800);stop();break; }   // 16716015 corresponds to the left key
      case 16734885: {turn_right();delay(800);stop();break; }   // 16734885 corresponds to the right key
      case 16726215: {stop(); break;}   //16726215 corresponds to the ok key
    }// you can add more branches for different instruction
    irrecv.resume(); //Accept the next encoding
  } 
}



void move_ahead(){
    myservo.write(115); //looking forward
    motorR.run(FORWARD); //Two Wheel Move forward
    motorL.run(FORWARD);
}


void move_backwards(){
    myservo.write(115); //looking forward

    motorR.run(BACKWARD);      
    motorL.run(BACKWARD);//Two Wheel Move backward
}

void turn_left(){
    myservo.write(180); //looking left

    motorR.run(FORWARD);//Only right wheel move forward
}


void turn_right(){
  myservo.write(50); //looking right
  
  motorL.run(FORWARD);//Only left wheel move forward
}

void stop(){
  myservo.write(110); //looking forward

  motorL.run(RELEASE); // Two wheel stop moving
  motorR.run(RELEASE);
}
