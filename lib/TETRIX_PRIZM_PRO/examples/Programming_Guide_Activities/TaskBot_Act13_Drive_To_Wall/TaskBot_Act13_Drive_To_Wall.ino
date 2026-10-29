/*   PRIZM Pro Controller example program for 2 wheel drive taskbot.
 *   This program uses the ultrasonic sensor connected to 
 *   sensor port 1 to detect an obstacle in it's driving path
 *   within 25cm. When detected, the robot will stop and wait 
 *   for the object blocking it's path to be cleared.
 *   author PWU 11/07/2024
 */

  #include <PRIZM_PRO.h>      // include PRIZM library
  PRIZM prizm;                // instantiate a PRIZM Pro object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin();         //initialize PRIZM Pro

  prizm.setMotorInvert(1,1);      // invert the direction of DC Motor 1
                                  // to harmonize the direction of
                                  // opposite facing drive motors
}

void loop() {

  if(prizm.getSonicSensor(1, UNITS_CM) > 25)  // sonic sensor is on port 1, units = centimeters
  {
    prizm.setMotorPowers(50,50);    // if distance greater than 25cm, do this (motors 1 and 2)
  }
  else
  {
   prizm.setMotorPowers(125,125);   // if distance less than 25cm, do this (motors 1 and 2)
  }   
}
