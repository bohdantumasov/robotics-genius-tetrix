/* This example demonstrates how to read the PRIZM PRO controller's battery voltage and print it to the Serial Moniitor.
 * For more detailed information on using the PRIZM library functions,
 * Please see the Arduino Library functions grid in the TETRIX PRIZM Programmer's guide 
 * which can be viewed and downloaded at www.pitsco.com
 */


#include <PRIZM_PRO.h>    // Include PRIZM PRO Library

PRIZM prizm;              // Instantiate an object named prizm
      



void setup() {

  Serial.begin(115200);   // Setup the serial monitor at 9600 baud. You must open the serial monitor to view data
  prizm.PrizmBegin();     // Initiates the PRIZM controller - must be called in the setup of each PRIZM sketch
  

}

void loop() {

  
  double x = prizm.getBatteryVoltage();       // Place the battery voltage returned by the function into
                                              // double variable type will return 2 decimal place number 
                                              // For example, a value of 12.50 = 12.50 battery pack voltage.

  Serial.println(x);
  delay(250);       // print to serial monitor ever 250 milliseconds (1/4 second).                                           
                                                 

  

  
}
