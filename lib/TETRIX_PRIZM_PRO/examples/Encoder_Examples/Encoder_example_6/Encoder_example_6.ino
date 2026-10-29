/* Implement PID control of TETRIX motors equipped with encoders using the PRIZM PRO controller.
 * The recommended DC motor is the TETRIX TorqueNADO - part number 44260.
 * This example demonstrates how to use constant speed functions to accurately
 * spin a DC motor + encoder at a constant speed rate in degrees per second. 
 * For more detailed information on using the PRIZM library functions,
 * Please see the Arduino Library functions grid in the TETRIX PRIZM Programmer's guide 
 * which can be viewed and downloaded at www.pitsco.com
 */


#include <PRIZM_PRO.h>    // Include PRIZM PRO Library

PRIZM prizm;              // Instantiate an object named prizm


void setup() {

  prizm.PrizmBegin();     // Initiates the PRIZM PRO controller - must be called in the setup of each sketch
  

}

void loop() {

  prizm.setMotorSpeeds(200,200,-200,-200);        // Spin DC motors 1 and 2 at a constant 200 degrees per second and motors 3 and 4 at -200 degrees per second. 
                                                  // The +/- sign of speed parameter determines direction
                                                  // For TETRIX TorqueNADO encoders, max speed rate is approximately 600 degrees per second.

  delay(5000);          // wait here for 5 seconds

  prizm.PrizmEnd();     // end program
  
}
