/*   PRIZM Pro Controller example program for 2 wheel drive taskbot.
 *   Left motor is on motor port 1, right motor is on motor port 2.
 *   This program uses the ultrasonic sensor connected to sensor port 1 to detect objects in its 
 *   driving path. When detected, the robot will stop, backup, make a right turn and continue on.
 *   author PWU 11/07/2024
 */

  #include <PRIZM_PRO.h>     // include PRIZM Pro library
  PRIZM prizm;               // instantiate a PRIZM Pro object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin(); //initialize PRIZM Pro
  
  prizm.setMotorInvert(1,1);      // invert the direction of DC Motor 1
                                  // to harmonize the direction of
                                  // opposite facing drive motors
}

void loop() {

  if(prizm.getSonicSensor(1, UNITS_CM) > 25)     // obstacle sense range set at 25 centimeters, sensor on port 1, units = centimeters
  {
    prizm.setMotorPowers(35,35);          // forward while no obstacle detected 
    prizm.setRedLED(LOW);                 // turn off the red LED
    prizm.setGreenLED(HIGH);              // turn on green LED
  }
  else
  {
   prizm.setGreenLED(LOW);                // turn off green LED
   prizm.setRedLED(HIGH);                 // detected obstacle, turn red LED 
   prizm.setMotorPowers(125,125);         // stop, obstacle detected
   delay(500);
   prizm.setMotorPowers(-35,-35);         // back up
   delay(1000);
   prizm.setMotorPowers(125,125);         // stop
   delay(500);
   prizm.setMotorPowers(35,-35);          // make a right turn
   delay(1500);
   
  }   
}
