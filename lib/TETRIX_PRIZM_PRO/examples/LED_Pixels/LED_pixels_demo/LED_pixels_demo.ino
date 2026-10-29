/*
Prizm Pro example sketch for using the Prizm Pro LED RGB Pixels
Refer to the Prizm Pro Arduino Library reference for a complete list of functions

###################  Pixel Patterns
PATTERN_SPARKLE
PATTERN_CHASE
PATTERN_TWINKLE
PATTERN_SWEEP
PATTERN_RAINBOW
PATTERN_FADE
###################
*/

// create some color variables
long RED;
long GREEN;
long BLUE;
long MAGENTA;


#include <PRIZM_PRO.h>
PRIZM prizm;

void setup() {
  
  prizm.PrizmBegin();   // initialize Prizm Pro, wait for start

  // Here is how to use the packPixeColor function to pack RGB colors into a variable
  // Colors variables can be created for any combination of RGB values
   RED      = prizm.packPixelColor(255,0,0);
   GREEN    = prizm.packPixelColor(0,255,0);
   BLUE     = prizm.packPixelColor(0,0,255);
   MAGENTA  = prizm.packPixelColor(150,0,150);

  // Brightness can be adjusted at any time in code - range is 0 - 100%
  // If not set, the default is 50.
  // prizm.setPixelBrightness(75);
  
}

void loop() {

  // set Pixels 1,2,3 to a RGB color packed into a variable
  prizm.setPixelColor(1,RED);
  prizm.setPixelColor(2,GREEN);
  prizm.setPixelColor(3,BLUE);
  // pause for 2 seconds
  delay(2000);
  // turn all of the pixels off
  prizm.clearPixels();
  // pause 1 second
  delay(1000);
  // set pixel 1 to an RGB color - equal value of red and green make a yellow shade
  prizm.setPixelRGB(1,150,150,0);
  // pause 2 seconds
  delay(2000);
  // turn off pixel 1
  prizm.clearPixel(1);
  // pause 1 second
  delay(1000);
  // show a sparkle pattern on the pixels (see other patterns listed at the top of sketch)
  prizm.setPixelPattern(PATTERN_SPARKLE);
  // pause 2 seconds
  delay(2000);
  // get a pixel color from the color wheel (see color wheel graphic Arduino library reference)
  long color = prizm.getWheelColor(170);
  // set pixel 2 to the wheel color stored in color variable
  prizm.setPixelColor(2,color);
  // pause 2 seconds
  delay(2000);
  // turn off pixel 2
  prizm.clearPixel(2);

}
