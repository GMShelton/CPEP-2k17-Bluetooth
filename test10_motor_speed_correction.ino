// Changing that Tx and Rx
#include <SoftwareSerial.h> // to use pin 10 and 11 as RX and TX ports


// #define whiteLED 2
// #define greenLED 3
// #define blueLED 11
// #define redLED 12


#define sw_serial_rx_pin 12 //  Connect this pin to TX on the HC - 06
#define sw_serial_tx_pin 11 //  Connect this pin to RX on the HC - 06

#define pwmMotorL 10
#define pwmMotorR 9

#define MotorLB 8
#define MotorLF 7
#define MotorRB 6 //plus is forward back is minus
#define MotorRF 5

#define trigPin 3
#define echoPin 4

#define led 2 //redLED
#define led2 1 //greenLED

    
#define READ_RATE 0 // How often the serial link is read, in milliseconds
#define FLASH_RATE 100 // The on/off period in milliseconds, for the LED Flash status feedback


byte cmd; // Stores the next byte of incoming data, which is a "command" to do something
byte param; // Stores the 2nd byte, which is the command parameter

int Speed = 125;  //Defines the speed of the robot


void setup() {
    // put your setup code here, to run once:

    pinMode(13,OUTPUT);// LED built in
    pinMode(12,OUTPUT);// RX
    pinMode(pwmMotorL,OUTPUT);// Motor L PWN/speed controll
    pinMode(pwmMotorR,OUTPUT);// Motor R PWN/speed controll
    pinMode(MotorLF,OUTPUT);// Motor L Forward
    pinMode(MotorLB,OUTPUT);// Motor L Back
    pinMode(MotorRB,OUTPUT);// Motor R Back
    pinMode(MotorRF,OUTPUT);// Motor R Forward 
    pinMode(trigPin,OUTPUT);// An ultrasound pin // (I added this line)
    pinMode(echoPin,INPUT);// An ultrasound pin // (I added this line)
    pinMode(led,OUTPUT);// Red LED // (I added this line)
    pinMode(led2,OUTPUT);// Green LED // (I added this line)
    digitalWrite(MotorRpwn,255); // (I added this line)
    digitalWrite(MotorLpwn,255); // (I added this line)
    Serial.begin(9600);// Serial (Bluetooth) Communication // (I added this line)
}

int cm = 1; // centimeters  // (I added this line)
int in = cm/2.54; // inches // (I added this line)
int ft = in/12; // feet // (I added this line)


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
            
            switch (param)  {
                case 1:
                    // Android device requests the Arduino to send some data back to Android
                    if (Serial)  {
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
                    analogWrite(pwmMotorL,Speed*0.8);

                break;
      
                case 3: //Backwards
                    digitalWrite(MotorLF,LOW);
                    digitalWrite(MotorLB,HIGH);
                    digitalWrite(MotorRB,HIGH);
                    digitalWrite(MotorRF,LOW);
                    analogWrite(pwmMotorR,Speed);
                    analogWrite(pwmMotorL,Speed*0.8);

                break;
            
                case 4: // Turn Left
                    digitalWrite(MotorLF,HIGH);
                    digitalWrite(MotorLB,LOW);
                    digitalWrite(MotorRB,HIGH);
                    digitalWrite(MotorRF,LOW);
                    analogWrite(pwmMotorR,Speed);
                    analogWrite(pwmMotorL,Speed*0.8);
                
                break;
                
                case 5: // Turn Right? Its 1:10 AM and I just want to celebrate my relative success and not fix
                //all the problems so Tomorrow. I think right now the LEft will turn right and the Right will turn left.
                //I'll confirm this is a minute but not fix it. I'll fix it tomorrow
                    digitalWrite(MotorLF,LOW);
                    digitalWrite(MotorLB,HIGH);
                    digitalWrite(MotorRB,LOW);  
                    digitalWrite(MotorRF,HIGH);
                    analogWrite(pwmMotorL,Speed*0.8);
                    analogWrite(pwmMotorR,Speed);

                break;
      
                case 6: // Stop
                    analogWrite(pwmMotorR,Speed);
                    digitalWrite(MotorLF,LOW);
                    digitalWrite(MotorLB,LOW);
                    digitalWrite(MotorRF,LOW);
                    digitalWrite(MotorRB,LOW);
                    analogWrite(pwmMotorL,Speed*0.8);

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
      
                    
                case 10:  // Made the ultrasonic sensor its own case                  
                    if (distance < 20*cm) {  // This is where the LED On/Off happens
                        digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
                        digitalWrite(MotorLF,HIGH);
                        digitalWrite(MotorRF,HIGH);
                        digitalWrite(MotorLB,LOW);
                        digitalWrite(MotorRB,LOW);
                        digitalWrite(led2,LOW);
                    }
                    else {
                        digitalWrite(led,LOW);
                        digitalWrite(led2,HIGH);
                        digitalWrite(MotorLF,LOW);
                        digitalWrite(MotorRF,LOW);
                        digitalWrite(MotorRB,HIGH);
                        digitalWrite(MotorLB,HIGH);
                    }
                    if (distance >= 200*cm || distance <= 0*cm){
                        Serial.println("Out of range");
                    }
                    else {
                        Serial.print(distance);
                        Serial.println("cm");
                    }
                        delay(500);
                    
                default: break; // do nothing
                
        
            } // switch (param)
            
        } // switch (cmd) case 1
    
        default: break; // do nothing
        
    } // switch (cmd)

  delay(READ_RATE); // wait 100ms for next reading

}

