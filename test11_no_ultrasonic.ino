// Changing that Tx and Rx
#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 12);


#define pwmMotorL 10
#define pwmMotorR 9

#define MotorLB 8
#define MotorLF 7
#define MotorRB 6 //plus is forward back is minus
#define MotorRF 5

#define trigPin 12 
#define echoPin 11 
#define USGnd 4 
#define USVcc 3

#define READ_RATE 100 // How often the serial link is read, in milliseconds
#define FLASH_RATE 100 // The on/off period in milliseconds, for the LED Flash status feedback


byte cmd; // Stores the next byte of incoming data, which is a "command" to do something
byte param; // Stores the 2nd byte, which is the command parameter

int Speed = 150;  //Defines the speed of the robot

int cm = 1; // centimeters
int in = cm/2.54; // inches
int ft = in/12; // feet

// int Bord = 0; // This is already defined in the foor loop within case 10
int c = 0;
int num = 0;


void square() {
    digitalWrite(MotorLF,HIGH);
    digitalWrite(MotorLB,LOW);
    digitalWrite(MotorRF,HIGH);
    digitalWrite(MotorRB,LOW);
    analogWrite(pwmMotorR,255); 
    analogWrite(pwmMotorL,255);  

    delay(3000); // 3 seconds, delay is in milliseconds

    // Turning right
    digitalWrite(MotorLF,HIGH);
    digitalWrite(MotorLB,LOW);
    digitalWrite(MotorRF,LOW);
    digitalWrite(MotorRB,HIGH);
    analogWrite(pwmMotorR,255); 
    analogWrite(pwmMotorL,255);  

    delay(3000); // 3 seconds, delay is in milliseconds
}

void setup() {
    // put your setup code here, to run once:

    pinMode(13,OUTPUT);//LED built in
    pinMode(pwmMotorL,OUTPUT);//TX
    pinMode(pwmMotorR,OUTPUT);//Turn L
    pinMode(MotorLF,OUTPUT);//Motor L Forward
    pinMode(MotorLB,OUTPUT);//Motor L Back
    pinMode(MotorRF,OUTPUT);// PWN/speed controll
    pinMode(MotorRB,OUTPUT);//Turn R
    pinMode(MotorRF,OUTPUT);//Motor R Forward
    pinMode(trigPin,OUTPUT);// 
    pinMode(echoPin,INPUT);// 
    pinMode(USVcc,OUTPUT); 
    pinMode(USGnd,OUTPUT); 
    digitalWrite(USGnd,LOW);
    digitalWrite(USVcc,HIGH);
    Serial.begin(9600);// Serial (Bluetooth) Communication
}

void loop() {
    long duration, distance;
    digitalWrite(trigPin, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin, HIGH);

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
    
                case 2: //Forwards
                    c = 2;
                    digitalWrite(MotorLF,HIGH);
                    digitalWrite(MotorLB,LOW);
                    digitalWrite(MotorRF,HIGH);
                    digitalWrite(MotorRB,LOW);
                    analogWrite(pwmMotorR,Speed);
                    analogWrite(pwmMotorL,Speed);

                break;
    
                case 3: //Backwards
                    c = 3;
                    digitalWrite(MotorLF,LOW);
                    digitalWrite(MotorLB,HIGH);
                    digitalWrite(MotorRB,HIGH);
                    digitalWrite(MotorRF,LOW);
                    analogWrite(pwmMotorR,Speed);
                    analogWrite(pwmMotorL,Speed);

                break;

                case 4: // Turn Left
                    c = 4;
                    digitalWrite(MotorLF,HIGH);
                    digitalWrite(MotorLB,LOW);
                    digitalWrite(MotorRB,HIGH);
                    digitalWrite(MotorRF,LOW);
                    analogWrite(pwmMotorR,Speed);
                    analogWrite(pwmMotorL,Speed);

                break;
    
                case 5: //Turn Right
                    c = 5;
                    digitalWrite(MotorLF,LOW);
                    digitalWrite(MotorLB,HIGH);
                    digitalWrite(MotorRB,LOW);
                    digitalWrite(MotorRF,HIGH);
                    analogWrite(pwmMotorL,Speed);
                    analogWrite(pwmMotorR,Speed);

                break; 
    
                case 6: // Stop
                    c = 6;
                    analogWrite(pwmMotorR,Speed);
                    digitalWrite(MotorLF,LOW);
                    digitalWrite(MotorLB,LOW);
                    digitalWrite(MotorRF,LOW);
                    digitalWrite(MotorRB,LOW);
                    analogWrite(pwmMotorL,Speed);

                break;

                case 7:// Fast
                    c = 7;
                    Speed = 255;
                    Serial.write(Speed);

                break;

                case 8:// Slow
                    c = 8;
                    Speed = 75;
                    Serial.write(Speed);

                break;
    
                case 9:
                    c = 9;
                    Speed = 150;
                    Serial.write(Speed);

                break;
    
                case 10:
                    c = 10;                    
                    square();
                    delay(50);
                    square();
                    delay(50);     
                    square();
                    delay(50);                    
                    square();
                    delay(30000);                    
                    }
                         
                break;
    
                case 11:

                    c = 11;
                    
                    digitalWrite(MotorLF, HIGH);
                    digitalWrite(MotorLB, LOW);
                    digitalWrite(MotorRF, HIGH);
                    digitalWrite(MotorRB, LOW);
                    analogWrite(pwmMotorR, 255);
                    analogWrite(pwmMotorL, 155);

                break;                                  
               
                } // switch (param)
  
            } // switch (cmd) case 1
    
        default: break; // do nothing
    
    } // switch (cmd)

    delay(READ_RATE); // wait 100ms for next readin

}

