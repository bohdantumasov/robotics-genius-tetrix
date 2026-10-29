/*  PRIZM Pro Controller example program
 *  This program will cause the a 2 wheel drive taskbot to drive in a continuous circle. 
 *  Press the red reset button to stop the program.
 *  author PWU 11/07/2024
 *  
 */

  #include <PRIZM_PRO.h>      // include PRIZM Pro library
  PRIZM prizm;                // instantiate a PRIZM Pro object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin();           // initialize PRIZM Pro
  prizm.setMotorInvert(1,1);    // invert the direction of DC Motor 1 to harmonize direction
                              
}

void loop() {

  prizm.setMotorPowers(50,25);    // spin motor 1 a 50% power and motor 2 at 25% power
                                  // resulting in the robot driving in a clockwise circle.
}
