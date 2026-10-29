/*  PRIZM Pro Controller example program
 *  This program will move a 2 wheel drive TaskBot forward for 3 seconds, stop and end program.
 *  author PWU 11/07/2024
 */

  #include <PRIZM_PRO.h>     // include PRIZM Pro library
  PRIZM prizm;              // instantiate a PRIZM Pro object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin();    // initialize PRIZM Pro

  prizm.setMotorInvert(1,1);     // invert the direction of DC Motor 1
                                 // to harmonize the direction of opposite facing drive motors
}

void loop() {

  prizm.setMotorPowers(50,50);   // turn Motors 1 and 2 on at 50% power
  delay(3000);                   // wait here for 3 seconds while motors are spinning
  prizm.PrizmEnd();              // end program and reset PRIZM

}
