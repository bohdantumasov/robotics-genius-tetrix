/*  PRIZM Pro Controller example program for 2 wheel drive taskbot.
 *  This program uses the Line Finder and the Ultrasonic sensor at the same time. 
 *  The robot will follow the edge of a black line (stripe) on a white surface and scan for an object
 *  in its path. Once detected, it will raise it's servo operated flag and wait for the obstacle to be cleared, then continue on. 
 *  The line sensor is connected to sensor port 3. The sonic sensor is connected to
 *  sensor port 1. The red LED shows the line sensor status. The green LED shows the 
 *  sonic sensor status.
 *  author PWU 11/07/2024
 */

  #include <PRIZM_PRO.h>      // include PRIZM library
  PRIZM prizm;                // instantiate a PRIZM Pro object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin();           // initialize PRIZM Pro
  prizm.setMotorInvert(1,1);    // invert the direction of DC Motor 1
                                // to harmonize the direction of
                                // opposite facing drive motors
  prizm.setServoSpeed(1,50);    // set servo 1 speed to 50;                              
}

void loop() {
    if(prizm.getLineSensor(3) == 1){
        prizm.setMotorPowers(30,125);     // line detected
        prizm.setRedLED(HIGH);
      }
      else
      {
        prizm.setMotorPowers(125,30);     // no line detected
        prizm.setRedLED(LOW);
      }  
  
    while(prizm.getSonicSensor(1, UNITS_CM) < 25){    // object is in path, loop here until cleared, sensor on port 1, units = cm
          prizm.setGreenLED(HIGH);                    // turn on
          prizm.setMotorPowers(125,125);              // stop, obstacle detected
          prizm.setServoPosition(1,0);                // raise detection flag!
      }

  prizm.setGreenLED(LOW);                 // turn off green LED
  prizm.setServoPosition(1,90);           // lowered flag position 
}
