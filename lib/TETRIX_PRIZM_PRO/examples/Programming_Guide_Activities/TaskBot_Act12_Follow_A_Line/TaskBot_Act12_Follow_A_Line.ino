/*  PRIZM Pro Controller example program
 *  This program implements line following with a 2 wheel drive TaskBot. Using the line finder sensor   
 *  on sensor port 3, the robot will follow the edge of a black stripe on a white surface. 
 *  The DC drive motors 1 and 2 will power one motor at a time resulting in back and forth forward motion to
 *  keep the robot traversing the line edge.
 *  author PWU 11/07/204
 */

  #include <PRIZM_PRO.h>     // include PRIZM Pro library
  PRIZM prizm;               // instantiate a PRIZM Pro object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin();   // initialize PRIZM

  prizm.setMotorInvert(1,1);      // invert the direction of DC Motor 1
                                  // to harmonize the direction of
                                  // opposite facing drive motors
}

void loop() {

  // no beam reflected, line detected
  if(prizm.getLineSensor(3) == 0){prizm.setMotorPowers(125,30); prizm.setRedLED(LOW);}  

  // relected beam, no line detected
  if(prizm.getLineSensor(3) == 1){prizm.setMotorPowers(30,125); prizm.setRedLED(HIGH);} 
   
}
