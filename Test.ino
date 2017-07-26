// Changing that Tx and Rx
#include <SoftwareSerial.h> // to use pin 10 and 11 as RX and TX ports



#define sw_serial_rx_pin 11 //  Connect this pin to TX on the HC - 06
#define sw_serial_tx_pin 10 //  Connect this pin to RX on the HC - 06

#define whiteLED 2
#define greenLED 6
#define blueLED 10
#define redLED 11

#define READ_RATE 100 // How often the serial link is read, in milliseconds
#define FLASH_RATE 100 // The on/off period in milliseconds, for the LED Flash status feedback


byte cmd; // Stores the next byte of incoming data, which is a "command" to do something
byte param; // Stores the 2nd byte, which is the command parameter
byte speedParam; // Stores 3rd byte for speed

void setup() {
  // put your setup code here, to run once:

pinMode(13,OUTPUT);//LED built in
pinMode(12,OUTPUT);// Off
pinMode(11,OUTPUT);//RX
pinMode(10,OUTPUT);//Tx
pinMode(9,OUTPUT);//Turn L
pinMode(8,OUTPUT);//Motor L Forward
pinMode(7,OUTPUT);//Motor L Back
pinMode(6,OUTPUT);// PWN/speed controll
pinMode(5,OUTPUT);//Turn R
pinMode(4,OUTPUT);//Motor R Back
pinMode(3,OUTPUT);//Motor R Forward
Serial.begin(9600);// Serial (BLuetooth) Communication
}
void loop() {
int Speed = 125;  //Defines the speed of the robot  
  while(speedParam == 7){
    while(Speed <= 255){
      Speed += 1;
      Serial.write(Speed);
      delay(200);
    } //When the Arudino receives a third byte with the value 7, and while speed is less than or equal to 255, increase the speed of the robot every .2 seconds.
  }

  while(speedParam == 8){
    while(Speed > 0){
      Speed -= 1;
      Serial.write(Speed);
      delay(200);
    } //When the Arduino receives a third byte with the value 8, and while speed is greater than zero, decrease the speed of the robot every .2 seconds.
  }

  while(0 < Speed < 75){
    digitalWrite(whiteLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, LOW);
  }

  while(76 < Speed < 150){
    digitalWrite(whiteLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, LOW);
  }

  while(151 < Speed < 225){
    digitalWrite(whiteLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, HIGH);
    digitalWrite(redLED, LOW);
  }

  while(226 < Speed < 255){
    digitalWrite(whiteLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, HIGH);
  }
  
if ( Serial.available() ) // if data is available to read
{
cmd = Serial.read(); // read it and store it in 'cmd'
// Data format is byte 1 = command, byte 2 = parameter
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
// Send back 2 bytes with a value of 1, 2
Serial.write(1);
Serial.write(2);
};
break;
case 2: //Forwards
digitalWrite(8,HIGH);
digitalWrite(7,LOW);
digitalWrite(3,HIGH);
digitalWrite(4,LOW);
digitalWrite(12,LOW);
digitalWrite(9,LOW);
digitalWrite(5,LOW);
break;
case 3: //Backwards
digitalWrite(8,LOW);
digitalWrite(7,HIGH);
digitalWrite(4,HIGH);
digitalWrite(3,LOW);
digitalWrite(12,LOW);
digitalWrite(9,LOW);
digitalWrite(5,LOW);
break;
case 4: // Turn Left
digitalWrite(8,HIGH);
digitalWrite(7,LOW);
digitalWrite(4,HIGH);
digitalWrite(3,LOW);
digitalWrite(9,HIGH);
digitalWrite(12,LOW);
digitalWrite(5,LOW);
break;
case 5: // Turn Right? Its 1:10 AM and I just want to celebrate my realtive sucess and not fix
//all the problems so Tomorrow. I think right now the LEft will turn right and the Right will turn left.
//I'll confim this is a minute but not fix it. I'll fix it tomorrow
digitalWrite(8,LOW);
digitalWrite(7,HIGH);
digitalWrite(4,LOW);
digitalWrite(3,HIGH);
digitalWrite(5,HIGH);
digitalWrite(12,LOW);
digitalWrite(9,LOW);

break;
case 6: // Stop
digitalWrite(12,HIGH);
digitalWrite(9,LOW);
digitalWrite(8,LOW);
digitalWrite(7,LOW);
analogWrite(6,LOW);
digitalWrite(4,LOW);
digitalWrite(3,LOW);
digitalWrite(5,LOW);

break;
default: break; // do nothing
} // switch (param)
} // switch (cmd) case 1
default: break; // do nothing
} // switch (cmd)

delay(READ_RATE); // wait 100ms for next readin

}

