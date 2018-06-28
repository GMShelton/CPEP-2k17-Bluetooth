// Changing that Tx and Rx
#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 12);

// MotorRB - Right motor, in backward direction
// MotorRF - Right motor, in forward direction
// MotorLB - Left motor, in backward direction
// MotorLF - Left motor, in forward direction
// pwmMotorL - Pulse-Width Modulation for Left motor
// pwmMotorR - Pulse-Width Modulation for Right motor


// Some of the variables dealing with younity bot dimensions, speed, etc. are specific to the younity bot built by Conrad


#define pwmMotorL 10
#define pwmMotorR 9


#define MotorRB 8 //plus is forward back is minus
#define MotorRF 7

#define MotorLB 6
#define MotorLF 5


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
int in = cm / 2.54; // inches
int ft = in / 12; // feet

// int Bord = 0; // This is already defined in the foor loop within case 10
int num = 0; // for controlling ultrasonic
int startOver = 0; // for controlling ultrasonic (why not make 10 to prevent errors from automatically running when plug in?)
int startOverCircle = 0; // for controlling ultrasonic (why not make 10 to prevent errors from automatically running when plug in?)


int botLength = 8.75 * in;
int botWidth = 8.5 * in;
int turnRadius = sqrt(sq((botLength / 2)) + sq((botWidth / 2))) + 2 * in;

float nextStep = 1;

float botTurnsPerMin = 42;  // things like these should be calibrations you can adjust directly from the app
float degreeTurn = 90;
float turnTime = degreeTurn / (360 * (botTurnsPerMin / 60));

float wheelDiam = 2.5 * in / 12; // diam of wheel in ft
float rpm = 4;

// slow - (83 rev  / 59.6 sec ) 60 sec = 83.557 rpm
// med1 - (152 rev  / 62.5 sec ) 60 sec = 126.67 rpm
// fast1 - (180 rev  / 61.2 sec ) 60 sec = 176.471 rpm
// fast2 - (176.2 rev  / 62.8 sec ) 60 sec = 168.344 rpm

float distPerSec = wheelDiam * PI * (rpm / 60); // (dist/rev)(rev/sec) = dist/sec;
//float moveTime = distPerSec;
/// 150 rpm


void forward() {
  digitalWrite(MotorLF, HIGH);
  digitalWrite(MotorLB, LOW);
  digitalWrite(MotorRF, HIGH);
  digitalWrite(MotorRB, LOW);
  analogWrite(pwmMotorR, Speed);
  analogWrite(pwmMotorL, Speed);

}


void backward() {
  digitalWrite(MotorLF, LOW);
  digitalWrite(MotorLB, HIGH);
  digitalWrite(MotorRF, LOW);
  digitalWrite(MotorRB, HIGH);
  analogWrite(pwmMotorR, Speed);
  analogWrite(pwmMotorL, Speed);

}

void left() {
  digitalWrite(MotorLF, LOW);
  digitalWrite(MotorLB, HIGH);
  digitalWrite(MotorRF, HIGH);
  digitalWrite(MotorRB, LOW);
  analogWrite(pwmMotorR, Speed);
  analogWrite(pwmMotorL, Speed);

}

void right() {
  digitalWrite(MotorLF, HIGH);
  digitalWrite(MotorLB, LOW);
  digitalWrite(MotorRF, LOW);
  digitalWrite(MotorRB, HIGH);
  analogWrite(pwmMotorR, Speed);
  analogWrite(pwmMotorL, Speed);

}

void stopped() {
  digitalWrite(MotorLF, LOW);
  digitalWrite(MotorLB, LOW);
  digitalWrite(MotorRF, LOW);
  digitalWrite(MotorRB, LOW);
  analogWrite(pwmMotorR, Speed);
  analogWrite(pwmMotorL, Speed);

}



void ultraSonic() {

  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  if (distance < 20 * cm) { // This is where the LED On/Off happens
    // When the Red condition is met, the Green LED should turn off
    stopped();
    delay(1000);
    backward();
    delay(200);
    stopped();
    startOver = 0;
    delay(2000);

  }
}


void ultraSonicMaze() {

  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;


  if (distance < 10 * cm) { // This is where the LED On/Off happens
    // When the Red condition is met, the Green LED should turn off
    //left();

    if (nextStep == 1) {
      stopped();
      delay(1000 * 5);
      backward();
      delay(2 / distPerSec);
      stopped();
      left();
      delay(1000 * turnTime);
      forward();
      delay(2 / distPerSec);
      right();
      delay(1000 * turnTime);

      nextStep += 0.5;
    }
    /*
            if (nextStep == 1.5) {
              stopped();
              delay(1000*5);
              backward();
              delay(200*5*2);
              stopped();
              right();
              delay(1000 * turnTime);
              forward();
              delay(1000*5);
              left();
              delay(1000 * turnTime);

              nextStep += 0.5;

            }


            if (nextStep == 2) {
              stopped();
              delay(1000*5);
              backward();
              delay(200*5*2);
              stopped();
              left();
              delay(1000 * turnTime);
              forward();
              delay(1000*5);
              right();
              delay(1000 * turnTime);

              nextStep += 0.5;
            }
    */
  }
  //else {
  //forward();
  //}

}

void ultraSonic2() {

  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  if (distance < 30 * cm) { // This is where the LED On/Off happens
    // When the Red condition is met, the Green LED should turn off
    stopped();
    delay(1000);
    /*
      digitalWrite(MotorLF,LOW);
      digitalWrite(MotorRF,LOW);
      digitalWrite(MotorLB,HIGH);
      digitalWrite(MotorRB,HIGH);
      delay(1000);
      digitalWrite(MotorLF,LOW);
      digitalWrite(MotorRF,LOW);
      digitalWrite(MotorLB,LOW);
      digitalWrite(MotorRB,LOW);
      startOver = 0;
      delay(2000);
      Speed = 0;
      Serial.write(Speed);
    */
  }
}


void square() {
  if (startOver <= 4) {

    //Fast
    forward();
    analogWrite(pwmMotorR, 255);
    analogWrite(pwmMotorL, 255);
    ultraSonic();
    startOver = 0;
    delay(2000);
    delay(3000); // 3 seconds, delay is in milliseconds

    // Turning right

    right();
    analogWrite(pwmMotorR, 255);
    analogWrite(pwmMotorL, 255);
    ultraSonic();
    startOver = 0;
    delay(2000);
    delay(3000); // 3 seconds, delay is in milliseconds

    //stop
    stopped();
    analogWrite(pwmMotorR, 255);
    analogWrite(pwmMotorL, 255);
    ultraSonic();
    startOver = 0;
    delay(2000);
    delay(50);
    startOver += 1;
  }
}


// fix to include the curly for the if statement for the circulc fucntion
void circle() {
  if (startOverCircle <= 4);
  right();
  analogWrite(pwmMotorR, 255);
  analogWrite(pwmMotorL, 100);
  ultraSonic();
  startOver = 0;
  delay(2000);
  delay(3000);
  right();
  analogWrite(pwmMotorR, 255);
  analogWrite(pwmMotorL, 100);
  ultraSonic();
  startOver = 0;
  delay(2000);
  delay(3000);
  startOverCircle += 1;
}



void setup() {
  // put your setup code here, to run once:

  pinMode(13, OUTPUT); //LED built in
  pinMode(pwmMotorL, OUTPUT); // PWN/speed controll
  pinMode(pwmMotorR, OUTPUT); // PWN/speed controll
  pinMode(MotorLF, OUTPUT); //Motor L Forward
  pinMode(MotorLB, OUTPUT); //Motor L Back
  pinMode(MotorRF, OUTPUT); // Motor R Forward
  pinMode(MotorRB, OUTPUT); //Motor R Back
  pinMode(trigPin, OUTPUT); //
  pinMode(echoPin, INPUT); //
  pinMode(USVcc, OUTPUT);
  pinMode(USGnd, OUTPUT);
  digitalWrite(pwmMotorR, 0);
  digitalWrite(pwmMotorL, 0);
  digitalWrite(USGnd, LOW);
  digitalWrite(USVcc, HIGH);
  Serial.begin(9600);// Serial (Bluetooth) Communication
}

void loop() {

  float distPerSec = wheelDiam * PI * (rpm / 60);
  
  /* already part of ultrasonic code
    long duration, distance;
    digitalWrite(trigPin, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin, HIGH);

    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;
  */


  if (Speed == 75) {
    rpm = (83 / 59.6) * 60;
  } else if (Speed == 150) {
    rpm = (152 / 62.5) * 60;
  } else if (Speed == 225) {
    rpm = 0.5 * ((176.2 / 62.8) + (180 / 61.2)) * 60;
  }


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
            forward();
            analogWrite(pwmMotorR, Speed);
            analogWrite(pwmMotorL, Speed);

            break;

          case 3: //Backwards
            backward();
            analogWrite(pwmMotorR, Speed);
            analogWrite(pwmMotorL, Speed);

            break;


          case 4: // Turn Left
            left();
            analogWrite(pwmMotorL, Speed);
            analogWrite(pwmMotorR, Speed);

            break;

          case 5: //Turn Right
            right();
            analogWrite(pwmMotorR, Speed);
            analogWrite(pwmMotorL, Speed);


            break;

          case 6: // Stop
            analogWrite(pwmMotorR, Speed);
            stopped();
            analogWrite(pwmMotorL, Speed);

            break;

          case 7:// Fast
            Speed = 255;
            Serial.write(Speed);

            break;

          case 8:// Slow
            Speed = 75;
            Serial.write(Speed);

            break;

          case 9:
            Speed = 150;
            Serial.write(Speed);

            break;

          case 10:
            Serial.write(1);
            startOver = 0;
            square();

            delay(50);
            square();

            delay(50);
            square();

            delay(50);
            square();
            ultraSonic();


            break;

          case 11:
            circle();
            break;

          case 12:
            forward();
            //digitalWrite(MotorLF, HIGH);
            //digitalWrite(MotorRF, HIGH);
            ultraSonic();
            //delay(10000);
            break;


          case 13:
            //obstacle 1

            //backward();
            ultraSonicMaze();

            break;


          default: break; // do nothing

        } // switch (param)

      }

  } // switch (cmd) case 1

  // switch (cmd)

  delay(READ_RATE); // wait 100ms for next reading

}
