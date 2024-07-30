#include <NewPing.h>
#include <Servo.h>

const int LeftMotorForward = 8; 
const int LeftMotorBackward = 9;
 const int RightMotorForward = 10; 
const int RightMotorBackward = 11; 
Servo servo_motor;
#define MAX_DISTANCE 1000
#define trig_pin A1
#define echo_pin A2
#define maximum_distance 200
boolean goesForward = false;
 int distance = 100; 
NewPing sonar(trig_pin, echo_pin, maximum_distance);
#define motor_aPin1 8
#define motor_aPin2 9
#define motor_bPin1 10
#define motor_bPin2 11
#define motor_aEnable 5
#define motor_bEnable 6
#define OB_range 30

int i=0, pos = 0,current_distance=0;
int range0=0, range30=0, range60=0, range85=0,range90=0,range95=0, range120=0, range150=0, range180=0 ;
unsigned long previous_millis = 0;
char serialData;

void setup()
{
 Serial.begin(9600);
servo_motor.attach(7); 


pinMode(motor_aPin1,OUTPUT);
 pinMode(motor_aPin2,OUTPUT);
 pinMode(motor_bPin1,OUTPUT);
 pinMode(motor_bPin2,OUTPUT);
 pinMode(motor_aEnable,OUTPUT);
 pinMode(motor_bEnable,OUTPUT);
analogWrite(motor_aEnable,200);
analogWrite(motor_bEnable,200);

 pinMode(RightMotorForward, OUTPUT); pinMode(LeftMotorForward, OUTPUT); pinMode(LeftMotorBackward, OUTPUT); pinMode(RightMotorBackward, OUTPUT); 
 servo_motor.write(115); delay(2000); distance = readPing(); delay(100); distance = readPing(); delay(100); distance = readPing(); delay(100); distance = readPing(); delay(100);
 

}

void brake()
{
 digitalWrite(motor_aPin1,LOW);
 digitalWrite(motor_aPin2,LOW);
 digitalWrite(motor_bPin1,LOW);
 digitalWrite(motor_bPin2,LOW);
 
}

void forward()
{
 digitalWrite(motor_aPin1,LOW);
 digitalWrite(motor_aPin2,HIGH);
 digitalWrite(motor_bPin1,LOW);
 digitalWrite(motor_bPin2,HIGH);
 
}

void forward_left()
{
 digitalWrite(motor_aPin1,LOW);
 digitalWrite(motor_aPin2,HIGH);
 digitalWrite(motor_bPin1,LOW);
 digitalWrite(motor_bPin2,LOW);
 
}

void forward_right()
{
 digitalWrite(motor_aPin1,LOW);
 digitalWrite(motor_aPin2,LOW);
 digitalWrite(motor_bPin1,LOW);
 digitalWrite(motor_bPin2,HIGH);
 
}

void backward()
{
 digitalWrite(motor_aPin1,HIGH);
 digitalWrite(motor_aPin2,LOW);
 digitalWrite(motor_bPin1,HIGH);
 digitalWrite(motor_bPin2,LOW);
 
}

void backward_right()
{
 digitalWrite(motor_aPin1,LOW);
 digitalWrite(motor_aPin2,LOW);
 digitalWrite(motor_bPin1,HIGH);
 digitalWrite(motor_bPin2,LOW);
 
}
void backward_left()
{
 digitalWrite(motor_aPin1,HIGH);
 digitalWrite(motor_aPin2,LOW);
 digitalWrite(motor_bPin1,LOW);
 digitalWrite(motor_bPin2,LOW);

}

void left()
{
 digitalWrite(motor_aPin1,LOW);
 digitalWrite(motor_aPin2,HIGH);
 digitalWrite(motor_bPin1,HIGH);
 digitalWrite(motor_bPin2,LOW);
 
}

void right()
{
 digitalWrite(motor_aPin1,HIGH);
 digitalWrite(motor_aPin2,LOW);
 digitalWrite(motor_bPin1,LOW);
 digitalWrite(motor_bPin2,HIGH);
 
}


int lookRight(){ servo_motor.write(50); delay(500); int distance = readPing(); delay(100); servo_motor.write(115); return distance; } int lookLeft(){ servo_motor.write(170); delay(500); int distance = readPing(); delay(100); servo_motor.write(115); return distance; delay(100); } int readPing(){ delay(70); int cm = sonar.ping_cm(); if (cm==0){ cm=250; } return cm; } void moveStop(){ digitalWrite(RightMotorForward, LOW); digitalWrite(LeftMotorForward, LOW); digitalWrite(RightMotorBackward, LOW); digitalWrite(LeftMotorBackward, LOW); } void moveForward(){ if(!goesForward){ goesForward=true; digitalWrite(LeftMotorForward, HIGH); digitalWrite(RightMotorForward, HIGH); digitalWrite(LeftMotorBackward, LOW); digitalWrite(RightMotorBackward, LOW); } } void moveBackward(){ goesForward=false; digitalWrite(LeftMotorBackward, HIGH); digitalWrite(RightMotorBackward, HIGH); digitalWrite(LeftMotorForward, LOW); digitalWrite(RightMotorForward, LOW); } void turnRight(){ digitalWrite(LeftMotorForward, HIGH); digitalWrite(RightMotorBackward, HIGH); digitalWrite(LeftMotorBackward, LOW); digitalWrite(RightMotorForward, LOW); delay(500); digitalWrite(LeftMotorForward, HIGH); digitalWrite(RightMotorForward, HIGH); digitalWrite(LeftMotorBackward, LOW); digitalWrite(RightMotorBackward, LOW); } void turnLeft(){ digitalWrite(LeftMotorBackward, HIGH); digitalWrite(RightMotorForward, HIGH); digitalWrite(LeftMotorForward, LOW); digitalWrite(RightMotorBackward, LOW); delay(500); digitalWrite(LeftMotorForward, HIGH); digitalWrite(RightMotorForward, HIGH); digitalWrite(LeftMotorBackward, LOW); digitalWrite(RightMotorBackward, LOW); }

void loop()

{


Automatic: brake();
 delay(300);

 
 { int distanceRight = 0; int distanceLeft = 0; delay(50); if (distance <= 20){ moveStop(); delay(300); moveBackward(); delay(400); moveStop(); delay(300); distanceRight = lookRight(); delay(300); distanceLeft = lookLeft(); delay(300); if (distance >= distanceLeft){ turnRight(); moveStop(); } else{ turnLeft(); moveStop(); } } else{ moveForward(); } distance = readPing(); } 
 
 if(Serial.available()>0)
 serialData=Serial.read();
 if(serialData=='M')
 goto Manual;

 

 
 
 

 Manual: brake();
 delay(300);


 while(1){
 if(Serial.available()>0)
 serialData=Serial.read();
 if(serialData=='A')
 goto Automatic;
 
 if(serialData=='F')
 backward();
 if(serialData=='B')
 forward();
 if(serialData=='S')
 brake();
 if(serialData=='L')
 left();
 if(serialData=='R')
 right();
 }
}
