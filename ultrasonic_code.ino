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

#define trigPin 13
#define echoPin 12
#define led 11 //redLED
#define MotorLF 7
#define MotorLB 8
#define MotorRpwn 10
#define MotorLpwn 9
#define MotorRF 6
#define MotorRB 5

// #define led2 10 //greenLED


void setup() {
  Serial.begin (9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(led,OUTPUT);
//  pinMode(led2,OUTPUT);
  pinMode(MotorLF,OUTPUT);
  pinMode(MotorRF,OUTPUT);
  pinMode(MotorLB,OUTPUT);
  pinMode(MotorRF,OUTPUT);
  pinMode(MotorLpwn,OUTPUT);
  pinMode(MotorRpwn,OUTPUT);
  pinMode(2,OUTPUT);  
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(2,LOW);  
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  
  analogWrite(MotorRpwn,255);
  analogWrite(MotorLpwn,25);
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
  if (distance < 40*cm) {  // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
    digitalWrite( MotorLF,LOW);
    digitalWrite(MotorRF,LOW);
    digitalWrite(MotorLB,LOW);
    digitalWrite(MotorRB,LOW);
 //   digitalWrite(led2,LOW);
   
//    delay(500); // Added this line so that the YOunity bot backs up a distance before continuing regular motion.
   
}
  else {
    digitalWrite(led,LOW);
//    digitalWrite(led2,HIGH);
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
}/*
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

#define trigPin 13
#define echoPin 12
#define led 11 //redLED
#define MotorLF 7
#define MotorLB 8
#define MotorRpwn 10
#define MotorLpwn 9
#define MotorRF 6
#define MotorRB 5

// #define led2 10 //greenLED


void setup() {
  Serial.begin (9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(led,OUTPUT);
//  pinMode(led2,OUTPUT);
  pinMode(MotorLF,OUTPUT);
  pinMode(MotorRF,OUTPUT);
  pinMode(MotorLB,OUTPUT);
  pinMode(MotorRF,OUTPUT);
  pinMode(MotorLpwn,OUTPUT);
  pinMode(MotorRpwn,OUTPUT);
  pinMode(2,OUTPUT);  
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(2,LOW);  
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  
  analogWrite(MotorRpwn,255);
  analogWrite(MotorLpwn,25);
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
  if (distance < 40*cm) {  // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
    digitalWrite( MotorLF,LOW);
    digitalWrite(MotorRF,LOW);
    digitalWrite(MotorLB,LOW);
    digitalWrite(MotorRB,LOW);
 //   digitalWrite(led2,LOW);
   
//    delay(500); // Added this line so that the YOunity bot backs up a distance before continuing regular motion.
   
}
  else {
    digitalWrite(led,LOW);
//    digitalWrite(led2,HIGH);
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
