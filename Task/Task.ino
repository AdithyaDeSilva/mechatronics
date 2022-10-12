#include <Stepper.h>
#include<Servo.h>

Servo servo1;
int pingPin=30;
int echo =12;  
double duration,distance;

int pos = 0;

int currentPlace[2] = {0, 1};
int nextPlace[2] = {0, 0};
  
int boxLength = -2100;
int boxheight = 2650;
// Include the Arduino Stepper Library


// Number of steps per output rotation
const int stepsPerRevolution = 100;

Stepper stepperXAxis(stepsPerRevolution, 4, 5, 6, 7);
Stepper stepperYAxis(stepsPerRevolution, 8, 9, 10, 11);

void relayOff(int pinNumber)
{
  digitalWrite(pinNumber, HIGH);
}

void relayOn(int pinNumber)
{
  digitalWrite(pinNumber, LOW);
}


void boxNumberToCoordinates(int boxNumber)
{
  switch (boxNumber)
  {
  case 0:
    nextPlace[0] = 0;
    nextPlace[1] = 1;
    break;
  case 1:
    nextPlace[0] = 1;
    nextPlace[1] = 1;
    break;
  case 2:
    nextPlace[0] = 2;
    nextPlace[1] = 1;
    break;
  case 3:
    nextPlace[0] = 3;
    nextPlace[1] = 1;
    break;
  case 4:
    nextPlace[0] = 1;
    nextPlace[1] = 2;
    break;
  case 5:
    nextPlace[0] = 2;
    nextPlace[1] = 2;
    break;
  case 6:
    nextPlace[0] = 3;
    nextPlace[1] = 2;
    break;
  case 7:
    nextPlace[0] = 1;
    nextPlace[1] = 3;
    break;
  case 8:
    nextPlace[0] = 2;
    nextPlace[1] = 3;
    break;
  case 9:
    nextPlace[0] = 3;
    nextPlace[1] = 3;
    break;
  default:
    break;
  }
}

void stepperMove()
{
  if (currentPlace[1] == nextPlace[1]) // check y axis
  {
    relayOn(2);
    stepperXAxis.step((nextPlace[0] - currentPlace[0]) * boxLength);
    relayOff(2);
    currentPlace[0] = nextPlace[0];
  }
  else
  {
    relayOn(2);
    stepperXAxis.step(-currentPlace[0] * boxLength);
    relayOff(2);
    relayOn(3);
    stepperYAxis.step((nextPlace[1] - currentPlace[1]) * boxheight);
    relayOff(3);
    relayOn(2);
    stepperXAxis.step(nextPlace[0] * boxLength);
    relayOff(2);
    currentPlace[0] = nextPlace[0];
    currentPlace[1] = nextPlace[1];
  }
  

      
      servo1.write(0);
      digitalWrite(pingPin,LOW);
      delayMicroseconds(2);
      digitalWrite(pingPin,HIGH);
      delayMicroseconds(5);
      digitalWrite(pingPin,LOW);
      duration= pulseIn(echo,HIGH);
    
      //OUTPUT
    
      //Serial.println(duration);
      Serial.print("Distance : ");
      distance=0.0342*duration/2;
      Serial.print(distance);
      Serial.println(" cm ");
      delay(100);
    if (distance<8)
     {
      servo1.write(-30);
      delay(200);
      servo1.write(30);
      delay(2000);
//        for (pos = 0; pos <= 10; pos += 1) { // goes from 0 degrees to 180 degrees
//          // in steps of 1 degree
//          servo1.write(pos);              // tell servo to go to position in variable 'pos'
//          delay(15);                       // waits 15ms for the servo to reach the position
//        }
//        for (pos = 10; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//          servo1.write(pos);              // tell servo to go to position in variable 'pos'
//          delay(15);                       // waits 15ms for the servo to reach the position
//        }
     }
}



void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  stepperXAxis.setSpeed(500);
  stepperYAxis.setSpeed(500);
  relayOff(2);
  relayOff(3);

  Serial.print("Enter 0 to complete the order.");

  pinMode(pingPin,OUTPUT);
  pinMode(echo,INPUT);
  servo1.attach(28);
}

void loop()
{
  if (Serial.available())
  {
    Serial.print("Input Box Number:");
    String reading = Serial.readStringUntil("\n");
    int s = reading.toInt();
    Serial.println(s);
    if(s<0 or s>9 ){
    Serial.print("Invalid input. Enter 0-9.");
      
    }else{
      
      boxNumberToCoordinates(s);
      relayOff(2);
      relayOff(3);
      stepperMove();
    }
  }
}
