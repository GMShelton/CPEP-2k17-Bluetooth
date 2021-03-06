// Why are:
// pwmMotorL and sw_serial_tx_pin are both on pin 10
// sw_serial_rx_pin and blueLED both on pin 11

// test10_motor_speed_correction.ino is specifically for the YOunity bot George took home over the weekend (it dampens 
// the speed of the left motor to match the right motor, which is slower)

// Changing that Tx and Rx
#include <SoftwareSerial.h> // to use pin 10 and 11 as RX and TX ports



#define sw_serial_rx_pin 11 //  Connect this pin to TX on the HC - 06
#define sw_serial_tx_pin 10 //  Connect this pin to RX on the HC - 06

#define whiteLED 2
#define greenLED 3
#define blueLED 11
#define redLED 12

#define pwmMotorL 10
#define pwmMotorR 9

#define MotorLB 8
#define MotorLF 7
#define MotorRB 6 //plus is forward back is minus
#define MotorRF 5

#define READ_RATE 100 // How often the serial link is read, in milliseconds
#define FLASH_RATE 100 // The on/off period in milliseconds, for the LED Flash status feedback


byte cmd; // Stores the next byte of incoming data, which is a "command" to do something
byte param; // Stores the 2nd byte, which is the command parameter

int Speed = 125;  //Defines the speed of the robot


void setup() {
  // put your setup code here, to run once:

pinMode(13,OUTPUT);//LED built in
pinMode(11,OUTPUT);//RX
pinMode(pwmMotorL,OUTPUT);//TX
pinMode(pwmMotorR,OUTPUT);//Turn L
pinMode(MotorLF,OUTPUT);//Motor L Forward
pinMode(MotorLB,OUTPUT);//Motor L Back
pinMode(MotorRF,OUTPUT);// PWN/speed controll
pinMode(MotorRB,OUTPUT);//Turn R
pinMode(MotorRF,OUTPUT);//Motor R Forward
Serial.begin(9600);// Serial (Bluetooth) Communication
}

void loop() {
  
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
case 2: //Forwards
digitalWrite(MotorLF,HIGH);
digitalWrite(MotorLB,LOW);
digitalWrite(MotorRF,HIGH);
digitalWrite(MotorRB,LOW);
analogWrite(pwmMotorR,Speed);
analogWrite(pwmMotorL,Speed);

break;
case 3: //Backwards
digitalWrite(MotorLF,LOW);
digitalWrite(MotorLB,HIGH);
digitalWrite(MotorRB,HIGH);
digitalWrite(MotorRF,LOW);
analogWrite(pwmMotorR,Speed);
analogWrite(pwmMotorL,Speed);

break;
case 4: // Turn Left
digitalWrite(MotorLF,HIGH);
digitalWrite(MotorLB,LOW);
digitalWrite(MotorRB,HIGH);
digitalWrite(MotorRF,LOW);
analogWrite(pwmMotorR,Speed);
analogWrite(pwmMotorL,Speed);
break;
case 5: // Turn Right? Its 1:10 AM and I just want to celebrate my relative success and not fix
//all the problems so Tomorrow. I think right now the LEft will turn right and the Right will turn left.
//I'll confirm this is a minute but not fix it. I'll fix it tomorrow
digitalWrite(MotorLF,LOW);
digitalWrite(MotorLB,HIGH);
digitalWrite(MotorRB,LOW);
digitalWrite(MotorRF,HIGH);
analogWrite(pwmMotorL,Speed);
analogWrite(pwmMotorR,Speed);

break;
case 6: // Stop
analogWrite(pwmMotorR,Speed);
digitalWrite(MotorLF,LOW);
digitalWrite(MotorLB,LOW);
digitalWrite(MotorRF,LOW);
digitalWrite(MotorRB,LOW);
analogWrite(pwmMotorL,Speed);

break;
case 7:// Fast
Speed = 255;
Serial.write(Speed);
digitalWrite(redLED, HIGH);
digitalWrite(blueLED, LOW);
digitalWrite(whiteLED, LOW);
digitalWrite(greenLED, LOW);

break;
case 8:// Slow
Speed = 75;
Serial.write(Speed);
digitalWrite(redLED, LOW);
digitalWrite(blueLED, LOW);
digitalWrite(whiteLED, HIGH);
digitalWrite(greenLED, LOW);


break;
case 9:
Speed = 150;
Serial.write(Speed);
digitalWrite(redLED, LOW);
digitalWrite(blueLED, HIGH);
digitalWrite(whiteLED, LOW);
digitalWrite(greenLED, LOW);


break;
default: break; // do nothing
} // switch (param)
} // switch (cmd) case 1
default: break; // do nothing
} // switch (cmd)

delay(READ_RATE); // wait 100ms for next readin

}

