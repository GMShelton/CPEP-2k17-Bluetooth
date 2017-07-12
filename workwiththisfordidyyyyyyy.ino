
const int temperaturePin = 0;

#define LEDPIN 8 
#define LEDPINTWO 9
#define READ_RATE 100 
#define FLASH_RATE 100


byte cmd;
byte param;


void setup() {
 pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
  Serial.begin(9600);
}

void loop() {

  float voltage, degreesC, degreesF;


  voltage = getVoltage(temperaturePin);

  degreesC = (voltage - 0.5) * 100.0;

  degreesF = degreesC * (9.0/5.0) + 32.0;

  Serial.print("voltage: ");
  Serial.print(voltage);
  Serial.print("  deg C: ");
  Serial.print(degreesC);
  Serial.print("  deg F: ");
  Serial.println(degreesF);


  delay(1000);
}


float getVoltage(int pin)
{
  return (analogRead(pin) * 0.004882814);

if ( Serial.available() )       // if data is available to read
  {
    cmd = Serial.read();         // read it and store it in 'cmd'
    // Data format is byte 1 = command, byte 2 = parameter
  };
  
  switch ( cmd ) {
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
             digitalWrite(LEDPINTWO, LOW);
             break;
           case 3: 
             // Turn off status LED
             flashLED(3);
             digitalWrite(LEDPINTWO, HIGH);
             digitalWrite(LEDPIN, LOW);
             break;
           case 4:
              // Demonstrate flashing the LED 4 times
              flashLED(4);
              break;
           case 5:
              // Demonstrate flashing the LED 5 times
              // Could add code here to control a servo via PWM outputs
              flashLED(5);
              break;
           default: break; // do nothing
         } // switch (param)
      } // switch (cmd) case 1
      default: break; // do nothing
  } // switch (cmd)
  
  delay(READ_RATE);                    // wait 100ms for next reading
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
