/*
 HC-SR04 Ping distance sensor]
 VCC to arduino 5v GND to arduino GND
 Echo to Arduino pin 13 Trig to Arduino pin 12
 Red POS to Arduino pin 11
 Green POS to Arduino pin 10
 560 ohm resistor to both LED NEG and GRD power rail
 More info at: http://goo.gl/kJ8Gl
 Original code improvements to the Ping sketch sourced from Trollmaker.com
 Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
 */

#define pwmMotorL 10
#define pwmMotorR 9

#define MotorLB 8
#define MotorLF 7
#define MotorRB 6 //plus is forward back is minus
#define MotorRF 5 

#define trigPin 12 //George 
#define echoPin 11 //George
#define USGnd 4 //George
#define USVcc 3 //George

void setup() {
  Serial.begin (9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(MotorLF,OUTPUT);
  pinMode(MotorRF,OUTPUT);
  pinMode(MotorLB,OUTPUT);
  pinMode(MotorRF,OUTPUT);
  pinMode(pwmMotorL,OUTPUT);
  pinMode(pwmMotorR,OUTPUT);
  pinMode(USGnd,OUTPUT);
  pinMode(USVcc,OUTPUT);
  digitalWrite(USGnd,LOW);
  digitalWrite(USVcc,HIGH);
  digitalWrite(pwmMotorL,170);
  digitalWrite(pwmMotorR,170);
  
}

int cm = 1; // centimeters
int in = cm/2.54; // inches
int ft = in/12; // feet

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance <30*cm) {  // This is where the LED On/Off happens
     // When the Red condition is met, the Green LED should turn off
    digitalWrite(MotorLF,LOW);
    digitalWrite(MotorRF,HIGH);
    digitalWrite(MotorLB,HIGH);
    digitalWrite(MotorRB,LOW);
  
}
  else {
    
    digitalWrite(MotorLF,HIGH);
    digitalWrite(MotorRF,HIGH);
    digitalWrite(MotorRB,LOW);
    digitalWrite(MotorLB,LOW);
  }
  if (distance >= 200*cm || distance <= 0*cm){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println("cm");
  }
  delay(500);
}
