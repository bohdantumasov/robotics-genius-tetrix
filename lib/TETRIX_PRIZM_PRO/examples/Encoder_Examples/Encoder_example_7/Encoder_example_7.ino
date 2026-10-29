/* Implement PID control of TETRIX motors equipped with encoders using the PRIZM PRO controller.
 * The recommended DC motor is the TETRIX TorqueNADO - part number 44260.
 * This example demonstrates how to use the degree targetting functions to accurately
 * position a DC motor + encoder to a position in units of degrees at a constant speed rate in degrees per second. 
 * For more detailed information on using the PRIZM library functions,
 * Please see the Arduino Library functions grid in the TETRIX PRIZM PRO Programmer's guide 
 * which can be viewed and downloaded at www.pitsco.com
 */


#include <PRIZM_PRO.h>    // Include PRIZM PRO Library

PRIZM prizm;              // Instantiate an object named prizm


void setup() {

  prizm.PrizmBegin();     // Initiates the PRIZM PRO controller - must be called in the setup of each sketch
  

}

void loop() {

  prizm.setMotorDegree(1,200,360);       // Spin DC motor 1 360 degrees at a constant 200 degrees per second and stop. 
                                         // The +/- sign of the target position parameter determines direction.
                                         // For TETRIX TorqueNADO encoders, max speed rate is approximately 600 degrees per second.

  delay(4000);          // wait here for 4 seconds

  prizm.resetEncoder(1);                 // Reset encoder count to zero

  prizm.setMotorDegree(1,200,360);       // Spin another 360 degrees
  
  delay(4000);          // wait here for 4 seconds

  prizm.resetEncoder(1);                 // Reset encoder count to zero and repeat loop

  
}
