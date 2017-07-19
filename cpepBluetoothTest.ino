// Changing that Tx and Rx
#include <SoftwareSerial.h> // to use pin 3 and 4 as RX and TX ports

#define sw_serial_rx_pin 3 //  Connect this pin to TX on the HC - 06
#define sw_serial_tx_pin 4 //  Connect this pin to RX on the HC - 06

// Constant Definitions
#define LEDPIN 13 // Pin on Arduino board to which status LED is connected
#define READ_RATE 100 // How often the serial link is read, in milliseconds
#define FLASH_RATE 100 // The on/off period in milliseconds, for the LED Flash status feedback

// Declarations
byte cmd; // Stores the next byte of incoming data, which is a "command" to do something
byte param; // Stores the 2nd byte, which is the command parameter

// Initialization
void setup() {
pinMode(9,OUTPUT);
pinMode(8,OUTPUT);
pinMode(7,OUTPUT);
pinMode(LEDPIN, OUTPUT); // pin 48 (on-board LED) as OUTPUT
// Devider between Stuff (ask and I'll try to explain if I'm not to tired)
digitalWrite(LEDPIN, LOW);
digitalWrite(8, LOW);
digitalWrite(7,LOW);
analogWrite(9,0);
Serial.begin(9600); // start serial communication at 9600bps
}

// Arduino Execution Loop
void loop() {

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
flashLED(1);
if (Serial)
{
// Send back 2 bytes with a value of 1, 2
Serial.write(1);
Serial.write(2);
};
break;
case 2:
// Turn on status LED
flashLED(2);
digitalWrite(LEDPIN, HIGH );
break;
case 3:
// Turn off status LED
flashLED(3);
digitalWrite(LEDPIN, LOW);
digitalWrite(8, LOW);
digitalWrite(7,LOW);
analogWrite(9,0);
break;
case 4:
// Test for the Motor which I don't expect to move (because of eletrical Issues) to run forwards
digitalWrite(8, HIGH);
digitalWrite(7,LOW);
analogWrite(9,255);
break;
case 5:
// Test code for the Motor to run backwards. The goal is to see if it a least struggles.
digitalWrite(7, HIGH);
digitalWrite(8,LOW);
analogWrite(9,255);
break;
default: break; // do nothing
} // switch (param)
} // switch (cmd) case 1
default: break; // do nothing
} // switch (cmd)

delay(READ_RATE); // wait 100ms for next reading
}

// Support routine
void flashLED (int n) {
// Flash the LED n times, to provide an on board status indicator
for (int i=1; i<=n; i++) {
digitalWrite (LEDPIN, HIGH);
delay (FLASH_RATE);
digitalWrite (LEDPIN, LOW);
delay(FLASH_RATE);
};
return;
}
