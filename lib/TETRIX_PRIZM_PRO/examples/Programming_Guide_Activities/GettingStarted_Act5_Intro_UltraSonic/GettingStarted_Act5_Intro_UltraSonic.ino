/*   PRIZM Pro Controller example program
 *   This example program will read the digital signal of the
 *   Ultrasonic sensor attached to the digital sensor port D3.
 *   The distance in centimeters of an object placed in front
 *   of the sensor will be sent to the serial monitor window.
 *   When using Serial Monitor, be sure to set the USB CDC on Boot option
 *   in the Tools menu to Enabled.
 * 
 */

  #include <PRIZM_PRO.h>      // include the PRIZM Library
  PRIZM prizm;                // instantiate a PRIZM object “prizm” so we can use its functions

void setup() {     //this code runs once

  prizm.PrizmBegin();       // initialize PRIZM Pro

  Serial.begin(115200);     // configure the serial monitor for 115200 baud rate
 
}

void loop() {     //this code repeats in a loop

  Serial.print(prizm.getSonicSensor(3, UNITS_CM));   // print the distance measured in centimeters on sensor port 3 to the serial monitor. 

  Serial.println(" Centimeters");                    // print " Centimeters"

  delay(200);   //slow down loop. Wait for 200ms to keep from printing to serial monitor to fast.        
}
