/*
  edits made as of 6/28:
  - split function "ultrasonic" into functions "ultrasonic" and "ultrasonicAction"
  - moved distance and duration to be global variables, and stated and define each separately
  - left the code operating ultrasonic in function "ultrasonic" and moved the if statement to stop movement into "ultrasonicAction"


  noticed that each time the collisionavodiance button is pressed (whether to turn on or off) the younity bot would act as if
  it had just been turned on. maybe is has something to do with the way cases are stored and saved

  // wait, if speed never equal 0 gotta find another way

  6/29 edits:
  - wrote code that sends out a string if the motors aren't spinning or the speed is 0, and another string otherwise.

  - wrote code on app inventor side to break out of case 12 and the ultrasonic when the directional buttons were pressed. (will later want to
  disable this breakout from each event handler when the button is clicked, so that ultrasonic can be active and stop a "reckless driver"

  EDIT NEXT:
  - PUT TEXT IN APP INVENTOR TO READ THE VALUE OF INCREMENTOR (to see if its changing, and if so, why it has no effect on the US if statement)
  - also search for youtube videos of how to send an unsigned one byte number to app using HC06
  - also search arduino reference on how to make functions with parameters

  (if time)
  - look at the comments for byte to get speed to change independently of directions
  - find out how to cause buttons in app to revert to look as if they were never pressed when they are pressed again.
  (this will allow for current spee din app to be indicated by button color change rather than text)


*/

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


#define trigPin 11
#define echoPin 12
#define USGnd 4
#define USVcc 3


#define READ_RATE 100 // How often the serial link is read, in milliseconds
#define FLASH_RATE 100 // The on/off period in milliseconds, for the LED Flash status feedback


byte cmd; // Stores the next byte of incoming data, which is a "command" to do something
byte param; // Stores the 2nd byte, which is the command parameter

int Speed = 150;  //Defines the speed of the robot
int incrementForTest = 0;

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

// Got Ultrasonic to continually give reading (called in loop, defined trig and echo pins correctly)

// split these in two separate US functions so that one could run indepedently of the other

unsigned long duration;
long distance;

void ultraSonic() {

  // long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); //, 10 * 1000000); // 10 seconds
  distance = (duration / 2) / 29.1;

}


void newUltraSonicAction() {

  if (distance > 30 * cm) {
    Serial.print("dist: is over 30 cm");
  }

  if (distance <= 30 * cm && distance > 0 * cm) { // This is where the LED On/Off happens
    Serial.print("dist: " + String(distance) + " cm");
  }

  if (distance == 0 * cm) { // This is where the LED On/Off happens
    Serial.print("probably not working");
  }

}


void ultraSonicAction() {
  /* when the condition in the if statement was replace with 1 == 0 (a condition that is always false) the US code
    did not run when the US button on the app was pressed. This indicates that the condition of distance < 20 * cm is
    always reading true for some reason. What can be tried is an incrementing variable, and when the incrementing variable
    gets larger than a certain value and the button is held down, trigger US

  */
  incrementForTest += 1;
  delay(1000); //( 1 / (READ_RATE / 1000));
  if (incrementForTest >= 20) {//(distance < 20 * cm) { // This is where the LED On/Off happens
    // When the Red condition is met, the Green LED should turn off
    stopped();
    delay(1000);
    backward();
    delay(200);
    stopped();
    // startOver = 0;
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

  ultraSonic();
  newUltraSonicAction();
  delay(300); /* delay neeeded so the current data sent doesn't interrupt the last data sent and print something like "dist: 30cdist: 20cm:" instead of "dist: 20 cm" */
  /*
    if (Speed == 0 || (digitalRead(MotorLF) == LOW && digitalRead(MotorLB) == LOW && digitalRead(MotorRF) == LOW && digitalRead(MotorRB) == LOW) ) {

      String speedCheck = String(Speed);
         Serial.print("forUS"); // sends to the companion app the speed value of the motors
    } else {
       Serial.print("reg"); // sends to the companion app the speed value of the motors
    }
  */

  float distPerSec = wheelDiam * PI * (rpm / 60);

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
    // Data format is byte 1 = command, byte 2 = parameter
  };


  /* This acts like a nest. When the app sends the first byte, it stores it as cmd and switches in cmd. The first byte containing 1
    causes it to run the first (and only) case in switch (cmd). Within this case, the second byte is stored as param and then switches
    in param with all the familiar cases for control


    tests:

    comment out the inner case 1 and see how that affects functionality of the code. Do the same with 2-5

    the only thing the outer case 1 is about is reading the 2nd byte and going into swithcing between cases for that

    thats why the byte sequences:
    1,2 for forward
    1,3 for backward
    1,6 for stop
    1,7 for fast

    after sending the 1 for the first byte, the code enter the switching for param. What if an outer case 2 were created to change speed?
    1,2 forward
    2,1 slow
    2,2 medium
    2,3 fast

    by copying the content in outer case 1 and pssting that next to it in the code (renaming it case 2) and keeping cases only for speed,
    speed and direction should be able to be controlled independenttly without needed code to switch in app inventor.
    Though in the second outer case should rename the param variable as speedParam or something different

  */

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
            //forward();
            //digitalWrite(MotorLF, HIGH);
            //digitalWrite(MotorRF, HIGH);
            //  ultraSonic();
            ultraSonicAction();
            //delay(10000);

            // because the read rate is 100 ms, I want to make this 1 second (10x read rate). But I want this 1 second regardless of the read rate
            // READ_RATE/1000 gets the length of time of readrate in seconds, while 1/(READ_RATE/1000) gets the multiplier one must multiply by to ensure
            // that a process is 1 second long



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
