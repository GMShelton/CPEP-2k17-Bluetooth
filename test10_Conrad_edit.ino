// 7/29 changes
// - turn 1: left turn while moving forward  turn 2: right turn while moving forward
//  to turn left while going backward, activate turn 2 and for turn right, turn 1
  
// - Switched order of digital writes in movement so it goes: LB, LF, RB, RF (8, 7, 6, 5) instead of LF, LB, RB, RF (7, 8, 6, 5)

// - I made an if statement in turn left to check whether both MotorLF and Motor RF are HIGH, and an if statement in turn right to
//  check whether both MotorLB and Motor RB are HIGH, but how do you check if the motors are HIGH?

// 8/2 changes
// made speedParam the third byte of data that will be received along with cmd and param and moved the cases controlling speed 
// into a new switch function for speedParam


// Changing that Tx and Rx
#include <SoftwareSerial.h> // to use pin 10 and 11 as RX and TX ports



#define sw_serial_rx_pin 11 //  Connect this pin to TX on the HC - 06
#define sw_serial_tx_pin 10 //  Connect this pin to RX on the HC - 06

// #define whiteLED 2
// #define greenLED 3
// #define blueLED 11
// #define redLED 12

#define pwmMotorL 10
#define pwmMotorR 9

#define MotorLB 8
#define MotorLF 7
#define MotorRB 6 //plus is forward back is minus
#define MotorRF 5

#define READ_RATE 0 // How often the serial link is read, in milliseconds
#define FLASH_RATE 100 // The on/off period in milliseconds, for the LED Flash status feedback


byte cmd; // Stores the next byte of incoming data, which is a "command" to do something
byte param; // Stores the 2nd byte, which is the command parameter
byte speedParam; // Stores the 3rd byte, which is the speed parameter

int Speed = 150;  //Defines the speed of the robot


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


void turn1() {
    digitalWrite(MotorLB,HIGH);
    digitalWrite(MotorLF,LOW);
    digitalWrite(MotorRB,LOW);
    digitalWrite(MotorRF,HIGH);
}

void turn2() {
    digitalWrite(MotorLB,HIGH);
    digitalWrite(MotorLF,LOW);
    digitalWrite(MotorRB,HIGH);
    digitalWrite(MotorRF,LOW);
}


void loop() {
  
    if ( Serial.available() ) // if data is available to read {
        cmd = Serial.read(); // read it and store it in 'cmd'
        // Data format is byte 1 = command, byte 2 = parameter, byte 3 = speedParam
    };
    

    
    switch (cmd) {
        case 1:
        // First byte contains a generic "command" byte. We arbitrarily defined '1' as the command to then check the 2nd parameter byte
        // User can additional commands by adding case 2, 3, 4, etc
        {
            param = Serial.read(); // read the parameter byte
            speedParam = Serial.read(); // read the speed parameter byte
            
            switch (param)  {
                case 1:
                    // Android device requests the Arduino to send some data back to Android
                    if (Serial)  {
                        Serial.write(1);
                        Serial.write(2);
                        Serial.write(3);
                    }
                    
                break;
      
                case 2: //Forwards
                    digitalWrite(MotorLB,LOW);
                    digitalWrite(MotorLF,HIGH);
                    digitalWrite(MotorRB,LOW);
                    digitalWrite(MotorRF,HIGH);
                    analogWrite(pwmMotorR,Speed);
                    analogWrite(pwmMotorL,Speed);

                break;
      
                case 3: //Backwards
                    digitalWrite(MotorLB,HIGH);
                    digitalWrite(MotorLF,LOW);
                    digitalWrite(MotorRB,HIGH);
                    digitalWrite(MotorRF,LOW);
                    analogWrite(pwmMotorR,Speed);
                    analogWrite(pwmMotorL,Speed);

                break;
            
                case 4: // Turn Left
                    // if (the MotorLF is HIGH AND the MotorRF is HIGH) {
                        turn1();
                    // }

                    // if (the MotorLB is HIGH AND the MotorRB is HIGH) {
                        // turn2();
                    // }                    
                    
                    analogWrite(pwmMotorR,Speed);
                    analogWrite(pwmMotorL,Speed);
                
                break;
                
                case 5: // Turn Right
                    // if (the MotorLF is HIGH AND the MotorRF is HIGH) {
                        turn2();
                    // }

                    // if (the MotorLB is HIGH AND the MotorRB is HIGH) {
                        // turn1();
                    // }                    
                    
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

                case 7: // Autonomous (polygon path)
                    // Moving forward
                    digitalWrite(MotorLF,HIGH);
                    digitalWrite(MotorLB,LOW);
                    digitalWrite(MotorRF,HIGH);
                    digitalWrite(MotorRB,LOW);
                    analogWrite(pwmMotorR,Speed); 
                    analogWrite(pwmMotorL,Speed);  
                    
                    delay(3000) // 3 seconds, delay is in milliseconds
                    
                    // Turning right
                    digitalWrite(MotorLF,HIGH);
                    digitalWrite(MotorLB,LOW);
                    digitalWrite(MotorRF,LOW);
                    digitalWrite(MotorRB,HIGH);
                    analogWrite(pwmMotorR,Speed); 
                    analogWrite(pwmMotorL,Speed);  
                    
                    delay(3000) // 3 seconds, delay is in milliseconds                    
                    

                break;

                case 8: // Autonomous (circle path)
                    digitalWrite(MotorLF,HIGH);
                    digitalWrite(MotorLB,LOW);
                    digitalWrite(MotorRF,LOW);
                    digitalWrite(MotorRB,HIGH);
                    analogWrite(pwmMotorR,Speed); 
                    analogWrite(pwmMotorL,Speed);   

                break;
                
                default: break; // do nothing
                
        
            } // switch (param)
            
            switch (speedParam){
                case 1:
                    // Android device requests the Arduino to send some data back to Android
                    if (Serial)  {
                        Serial.write(1);
                        Serial.write(2);
                        Serial.write(3);
                    }
                    
                break;
                
                case 2:// Fast
                    Speed = 255;
                    Serial.write(Speed);
                    digitalWrite(redLED, HIGH);
                    digitalWrite(blueLED, LOW);
                    digitalWrite(whiteLED, LOW);
                    digitalWrite(greenLED, LOW);

                break;
      
                case 3:// Slow
                    Speed = 75;
                    Serial.write(Speed);
                    digitalWrite(redLED, LOW);
                    digitalWrite(blueLED, LOW);
                    digitalWrite(whiteLED, HIGH);
                    digitalWrite(greenLED, LOW);

                break;

                case 4:// Medium
                    Speed = 150;
                    Serial.write(Speed);
                    digitalWrite(redLED, LOW);
                    digitalWrite(blueLED, HIGH);
                    digitalWrite(whiteLED, LOW);
                    digitalWrite(greenLED, LOW);

                break;
      
                default: break; // do nothing
                
            } // switch (speedParam)

        } // switch (cmd) case 1
    
        default: break; // do nothing
        
    } // switch (cmd)

  delay(READ_RATE); // wait 100ms for next reading

}
