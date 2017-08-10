
#define trigPin 12
#define echoPin 11
#define USGnd 4
#define USVcc 3

#define led1 5
#define led2 6
#define led3 7
#define led4 8
#define led5 9

byte cmd; // Stores the next byte of incoming data, which is a "command" to do something
byte param; // Stores the 2nd byte, which is the command parameter

int cm = 1; // centimeters
int in = cm/2.54; // inches
int ft = in/12; // feet

void setup() {
  // put your setup code here, to run once:

pinMode(13,OUTPUT);//LED built in
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);
pinMode(led5, OUTPUT);
pinMode(trigPin,OUTPUT);// 
pinMode(echoPin,INPUT);// 
pinMode(USVcc,OUTPUT); 
pinMode(USGnd,OUTPUT);
digitalWrite(USGnd, LOW);
digitalWrite(USVcc, HIGH);
Serial.begin(9600);// Serial (Bluetooth) Communication
}

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
  
if ( Serial.available() ) // if data is available to read
{
cmd = Serial.read(); // read it and store it in 'cmd'
// Data format is byte 1 = command, byte 2 = parameter, byte 3 = speedParam
};
switch (cmd) {
 case 1:
// First byte contains a generic "command" byte. We arbitrarily defined '1' as the command to then check the 2nd parameter byte
// User can additional commands by adding case 2, 3, 4, etc
{
// read the parameter byte
param = Serial.read();
switch (param)


 {
case 1:
// Android device requests the Arduino to send some data back to Android
if (Serial)
{
Serial.write(1);
Serial.write(2);
}

break;
case 2: 
if (distance < 20*cm) {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
}
else {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, HIGH);
}

break;
case 3:
if (distance < 10*cm) {
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
}
else {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
}

break;
case 4:
if (distance < 30*cm) {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
}
else {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
}

}
}
}
}
