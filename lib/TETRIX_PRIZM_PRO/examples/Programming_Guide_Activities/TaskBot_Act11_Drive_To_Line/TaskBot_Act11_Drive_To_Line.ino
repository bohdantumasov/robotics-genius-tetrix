/*  PRIZM Pro Controller example program
 *  This program will move a 2 wheel drive TaskBot forward on a white (reflective) surface until it detects a black (non-reflective)
 *  line. When the line is detected, the robot will stop.
 *  Connect the line finder sensor to sensor port 3.
 *  author PWU 11/07/2024
*/

  #include <PRIZM_PRO.h>      // include PRIZM Pro library
  PRIZM prizm;                // instantiate a PRIZM Pro object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin();     // initialize PRIZM Pro

  prizm.setMotorInvert(1,1);    // invert the direction of DC Motor 1
                                // to harmonize the direction of
                                // opposite facing drive motors
}

void loop() {

  if(prizm.getLineSensor(3) == 0) {     // when sensor is receiving reflected light beam
    prizm.setMotorPowers(35,35);        // turn Motors 1 and 2 on at 35% power 
    
  }                                                                    

  if(prizm.getLineSensor(3) == 1) {     // when sensor detects black stripe, or no longer receiving reflected light beam
    prizm.setMotorPowers(125,125);      // stop motors in brake mode 
    
    while(1){                           // infinite loop - stays locked in this loop until reset is pressed
    prizm.setRedLED(HIGH);              // flash Prizm Pro Pixel LED red on and off until reset
    delay(500);
    prizm.setRedLED(LOW);
    delay(500);
    }
  }
}
