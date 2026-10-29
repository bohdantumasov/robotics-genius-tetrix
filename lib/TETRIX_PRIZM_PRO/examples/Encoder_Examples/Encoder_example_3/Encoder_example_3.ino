/* Implement PID control of TETRIX motors equipped with encoders using the PRIZM Pro controller.
 * The recommended DC motor is the TETRIX TorqueNADO - part number 44260.
 * This example demonstrates how to use position targetting functions to accurately
 * position a DC motor + encoder to an encoder count position and hold the position
 * in a servo like mode. For more detailed information on using the PRIZM library functions,
 * Please see the Arduino Library functions grid in the TETRIX PRIZM PRO Programmer's guide 
 * which can be viewed and downloaded at www.pitsco.com
 */


#include <PRIZM_PRO.h>    // Include PRIZM PRO Library

PRIZM prizm;              // Instantiate an object named prizm PRO




void setup() {

  prizm.PrizmBegin();    // Initiates the PRIZM PRO controller - must be called in the setup of each sketch
  

}

void loop() {

  prizm.setMotorTargets(360,1440,360,1440,360,1440,360,1440);     // Spin DC motors 1,2,3,4 at a constant 360 degrees per second and stop when encoder count reaches 1440.
                                                                  // For TETRIX TorqueNADO encoders, 1440 = 1 clockwise motor shaft revolution. (1440 / 4 = 360)

  delay(2000);    // wait here for 2 seconds while motors get to their destination

  prizm.setMotorTargets(360,0,360,0,360,0,360,0);                // Spin DC motors 1,2,3,4 at 360 degrees per second back to encoder position "0".   

  delay(2000);    // wait here for 2 seconds, then repeat                                     
}
