
/*
 * pulseSensorRemote for herm3TICa v0.1 | 02/2015
 * ------------------------- 
 *  
 * Send pulse sensor data via serial/xbee
 *
 * rev 1:
 * - Filtering sensor readings with Kalman filter
 * - Sending the data in binary
 *
 * (cc) 2015 herm3TICa n3m3da
 * http://herm3tica.tv/
 * http://www.d3cod3.org
 */

#include "Kalman.h"

const char HEADER = 'H';
const char FOOTER = 'F';

int sensorPin = 1;    // select the input pin for the pulse sensor
int sensorValue = 0;  // variable to store the value coming from the sensor

Kalman kalmanValue;

void setup() {
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  // Wait for xbee to stabilize
  delay(300);
  
  // capture initial sansors values
  kalmanValue.init(analogRead(sensorPin));
  
}

void loop() {
  
  Serial.write(HEADER); // 1 BYTE
  
  sensorValue    = (int)kalmanValue.update(analogRead(sensorPin));
  sendBinary(sensorValue);   // 2 BYTES
  
  Serial.write(FOOTER); // 1 BYTE
  
  // delay 20ms to let the ADC recover:
  delay(20);
  
  // total message 4 BYTES long ==> 16 bits
    
  /* RECEIVING (on the other side)
    * 
    * We have to wait for a message of 4 BYTES to arrive,
    * and start the reading from the HEADER
    *
    * then we read the analog value (2 BYTES), re-converting binary to integer,
    * where:
    *
    * finalValue = least significant byte + most significant byte*256
   */
                  
}
