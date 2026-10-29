/*  This program will read the digital signal of the
 *  Line Finder sensor attached to sensor port 3.
 *  If the sensor is facing a reflective surface and 
 *  receiving a reflected IR beam, the red LED (pixel 1)
 *  will switch on. If the sensor is facing a dark 
 *  surface, or too far away from a reflective surface
 *  or over a non-reflective surface, the red LED will be off. 
 */
  
  #include <PRIZM_PRO.h>    //include the PRIZM Pro Library
  PRIZM prizm;              //create an object name of "prizm"

void setup() {          //this code runs once

  prizm.PrizmBegin();   //initialize PRIZM Pro
  
}

void loop() {           //this code repeats in a loop

  // line sensor connected to sensor port 3
  
  if(prizm.getLineSensor(3) == HIGH) {prizm.setRedLED(LOW);}  // Turn Red LED off

  if(prizm.getLineSensor(3) == LOW)  {prizm.setRedLED(HIGH);} // Turn Red LED on (Red defaults to pixel 1)
  
  delay(50);  //slow the loop down

}
