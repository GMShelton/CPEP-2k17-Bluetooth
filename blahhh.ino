#include <SoftwareSerial.h>                     // to use pin 4 and 5 as RX and TX ports

#define sw_serial_rx_pin 3 //  Connect this pin to TX on the esp8266
#define sw_serial_tx_pin 4 //  Connect this pin to RX on the esp8266

void setup() {
  // put your setup code here, to run once:
pinMode (12, OUTPUT); // LED

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(12, HIGH);
delay(2000);
digitalWrite(12, LOW);
delay(1000);

}
