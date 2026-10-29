/*  PRIZM Pro Controller example program
 *  This program will move a 2 wheel drive robot in a square driving pattern using a forward and right turn function.
 *  The left motor is on port 1 and the right motor is on port 2.
 *  author PWU 11/07/2024  
*/
  #include <PRIZM_PRO.h>      // include PRIZM Pro library
  PRIZM prizm;                // instantiate a PRIZM Pro object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin();         // initialize PRIZM Pro
  prizm.setMotorInvert(1,1);  // invert the direction of DC Motor 1 to harmonize direction
                              
}

void loop() {

for(int x=0; x<=3; x++){    // Do this four times, increment x by + 1
  forward();
  rightTurn();
 }
  prizm.PrizmEnd();
}

void forward(){                       // function to go forward
  prizm.setMotorPowers(50,50);        // go forward at 50% power
  delay(3000);                        // wait here for 3 seconds while motors 1 and 2 spin
  prizm.setMotorPowers(125,125);      // stop both motors with in brake mode
  delay(1000);                        // wait here for 1 second

  }

void rightTurn(){                     // function for a right turn
  prizm.setMotorPowers(50,-50);       // make a right turn
  delay(900);                         // wait here for 0.9 seconds (900 milliseconds) while motors spin 1 and 2 to make a right turn (this delay may need +/- adjustment)
  prizm.setMotorPowers(125,125);      // stop both motors with in brake mode
  delay(1000);                        // wait here for 1 second

  }


  


  


  
