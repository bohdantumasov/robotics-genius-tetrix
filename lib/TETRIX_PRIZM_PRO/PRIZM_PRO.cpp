/*
	TETRIX PRIZM Pro robotics controller
  Updated to support the new PRIZM Pro
  Some legacy support for PRIZM is still supported in this library for code compatibility
 	Written by: Paul W. Uttley
	11/04/2024
	Version pro_1.0
	=============== Added support for DC and Servo Motor EXPANSIONansion Controllers
	Default address for DC box is 1. Default for Servo box is 2.
	Additional boxes can be added in a daisy chain, and if so the addresses will need to be set different
	Valid address range for PRIZM to support is address 1 - 4.
*/

#include "esp_system.h"
#include "esp_task_wdt.h"
#include "esp32-hal-ledc.h"
#include <Wire.h>
#include "PRIZM_PRO.h"

// This method only works in downloaded IDE, not the cloud
/*
#if defined(CONFIG_FREERTOS_HZ)  // This macro exists only in later versions 3.x
    #define USING_ESP32_VERSION 3
#else
    #define USING_ESP32_VERSION 2     // The arduino cloud uses esp32 core 2. Change this to 3 if using core version 3
#endif
*/

// Check at compile time to see which version of esp32 boards manager core is being used by downloaded or Cloud IDE
#if defined(ESP_ARDUINO_VERSION_MAJOR)
    #if ESP_ARDUINO_VERSION_MAJOR >= 3
        #define USING_ESP32_VERSION 3
        //#pragma message("ESP32 Core version 3.x detected")  // show message in verbose compiler output
    #else
        #define USING_ESP32_VERSION 2
        //#pragma message("ESP32 Core version 2.x detected")
    #endif
#else
    //#pragma message("ESP_ARDUINO_VERSION_MAJOR not defined. Assuming version 2.x")
    #define USING_ESP32_VERSION 2
#endif


Adafruit_NeoPixel pixels(3, 21, NEO_GRB + NEO_KHZ800);

void PRIZM::setSoundNote(uint16_t note, uint32_t duration){
  #if(USING_ESP32_VERSION == 2)
    tone(14, note);
    delay(duration);                // Wait for the duration
    if(duration > 0) {noTone(14);}  // sound off
  #else
    ledcWriteTone(14, note);        // Set the specified frequency
    delay(duration);                // Wait for the duration
    if(duration > 0) {ledcWriteTone(14, 0);} // sound off
  #endif
}

void PRIZM::setSoundTone(uint16_t f_tone, uint32_t duration){
  #if(USING_ESP32_VERSION == 2)
    tone(14, f_tone);     // uses core 2
    delay(duration);                // Wait for the duration
    if(duration > 0) {noTone(14);}  // sound off
  #else
    ledcWriteTone(14, f_tone);      // Set frequency
    delay(duration);                // Wait for the duration
    if(duration > 0) {ledcWriteTone(14, 0);} // sound off
  #endif
}

void PRIZM::setSoundEffect(uint8_t effect){
  if(effect == 1) UFO();
  if(effect == 2) randomNoise();
  if(effect == 3) alarm();
  if(effect == 4) whistleUp();
  if(effect == 5) whistleDown();
  if(effect == 6) siren();
  if(effect == 7) correct();
  if(effect == 8) incorrect();
}

void PRIZM::setSoundOff(){
  #if(USING_ESP32_VERSION == 2)
    noTone(14);
  #else
    ledcWriteTone(14, 0);
  #endif
}

void PRIZM::UFO(){
  for (int i = 500; i < 1500; i += 10) {
    #if(USING_ESP32_VERSION == 2)
    //  tone(14, i, 10);
      tone(14, i);
      delay(10);
    #else
      ledcWriteTone(14, i);
      delay(10);
    #endif
  }
  for (int i = 1500; i > 500; i -= 10) {
    #if(USING_ESP32_VERSION == 2)
    //  tone(14, i, 10);
      tone(14, i);
      delay(10);
    #else
      ledcWriteTone(14, i);
      delay(10);
    #endif
  }
  #if(USING_ESP32_VERSION == 2)
    noTone(14);
  #else
    ledcWriteTone(14, 0);
  #endif
}

void PRIZM::randomNoise(){
  for (int i = 0; i < 25; i++) {
    #if(USING_ESP32_VERSION == 2)
    //  tone(14, random(800, 2000), 100); // Random high frequencies
      tone(14, random(800, 2000)); // Random high frequencies
      delay(100);
    #else
      int freq = random(800, 2000);
      ledcWriteTone(14, freq);
      delay(100);
    #endif
  }
  #if(USING_ESP32_VERSION == 2)
    noTone(14);
  #else
    ledcWriteTone(14, 0);
  #endif
}

void PRIZM::alarm(){
  for (int i = 0; i < 5; i++) {
    #if(USING_ESP32_VERSION == 2)
    //  tone(14, 600, 300); // Low tone
    //  tone(14, 900, 300); // High tone
      tone(14, 600); // Low tone
      delay(300);
      tone(14, 900); // High tone
      delay(300);
    #else
      ledcWriteTone(14, 600);
      delay(300);
      ledcWriteTone(14, 900);
      delay(300);
    #endif
  }
  #if(USING_ESP32_VERSION == 2)
    noTone(14);
  #else
    ledcWriteTone(14, 0);
  #endif
}

void PRIZM::whistleUp(){
  for (int i = 400; i <= 2000; i+=20) {
    #if(USING_ESP32_VERSION == 2)
    //  tone(14, i, (10000 / i));
      tone(14, i);
      delay(10000 / i);
    #else
      ledcWriteTone(14, i);
      delay(10000 / i);
    #endif
  }
  #if(USING_ESP32_VERSION == 2)
    noTone(14);
  #else
    ledcWriteTone(14, 0);
  #endif
}

void PRIZM::whistleDown(){
  for (int i = 2000; i >= 400; i-=20) {
    #if(USING_ESP32_VERSION == 2)
    //  tone(14, i, (10000 / i));
      tone(14, i);
      delay(10000 / i);
    #else
      ledcWriteTone(14, i);
      delay(10000 / i);
    #endif
  }
  #if(USING_ESP32_VERSION == 2)
    noTone(14);
  #else
    ledcWriteTone(14, 0);
  #endif
}

void PRIZM::siren(){
  for (int i = 500; i <= 1000; i+=25) {
    #if(USING_ESP32_VERSION == 2)
    //  tone(14, i, 20); // Gradually increase frequency
      tone(14, i);       // Gradually increase frequency
      delay(20);
    #else
      ledcWriteTone(14, i);
      delay(20);
    #endif
  }

  for (int i = 1000; i >= 500; i-=25) {
    #if(USING_ESP32_VERSION == 2)
    //  tone(14, i, 20); // Gradually decrease frequency
      tone(14, i);       // Gradually decrease frequency
      delay(20);
    #else
      ledcWriteTone(14, i);
      delay(20);
    #endif
  }
  #if(USING_ESP32_VERSION == 2)
    noTone(14);
  #else
    ledcWriteTone(14, 0);
  #endif
}

void PRIZM::correct(){
  #if(USING_ESP32_VERSION == 2)
  //  tone(14, 350, 100);
  //  tone(14, 700, 100);
    tone(14, 350);
    delay(100);
    tone(14, 700);
    delay(100);
    noTone(14);
  #else
    ledcWriteTone(14, 350);
    delay(100);
    ledcWriteTone(14, 700);
    delay(100);
    ledcWriteTone(14, 0);
  #endif
}

void PRIZM::incorrect(){
  #if(USING_ESP32_VERSION == 2)
  //  tone(14, 700, 100);
  //  tone(14, 350, 100);
    tone(14, 700);
    delay(100);
    tone(14, 350);
    delay(100);
    noTone(14);
  #else
    ledcWriteTone(14, 700);
    delay(100);
    ledcWriteTone(14, 350);
    delay(100);
    ledcWriteTone(14, 0);
  #endif
}

void PRIZM::enablePixels(){
  // Initialize NeoPixel strip
  pixels.begin();
  pixels.clear();
  pixels.show();
  pixels.setBrightness(128); // 0 - 255
  pixels.show();
}

void PRIZM::clearPixel(uint8_t pixel) {
  pixels.setPixelColor((pixel-1), 0);
  pixels.show();
}

void PRIZM::clearPixels() {
  pixels.clear();
  pixels.show();
}

void PRIZM::setPixelColor(uint8_t pixel, uint32_t color) {
  pixels.setPixelColor((pixel-1), color);
  pixels.show();
}

void PRIZM::setPixelRGB(uint8_t pixel, uint8_t red, uint8_t green, uint8_t blue){
  pixels.setPixelColor((pixel-1), pixels.Color(red, green, blue));
  pixels.show();
}

void PRIZM::setPixelBrightness(uint8_t percent){
  uint8_t brightness = map(percent,0,100,1,255);  // don't allow zero, it set pixel color to off
  pixels.setBrightness(brightness); // 0 - 255
  pixels.show();
}

uint32_t PRIZM::packPixelColor(uint8_t R, uint8_t G, uint8_t B ){
  uint32_t colorpacked = pixels.Color(R, G, B);
  return colorpacked;
}

uint32_t PRIZM::getWheelColor(uint8_t WheelPos){
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void PRIZM::setPixelPattern(uint8_t pattern, uint8_t R, uint8_t G, uint8_t B){
  if(pattern == 1) SPARKLE(R, G, B);
  if(pattern == 2) CHASE(R, G, B);
  if(pattern == 3) TWINKLE();
  if(pattern == 4) SWEEP(R, G, B);
  if(pattern == 5) RAINBOW();
  if(pattern == 6) FADE(R, G, B);
}

void PRIZM::SPARKLE(uint8_t R, uint8_t G, uint8_t B){
  for(int x = 0; x <= 25; x++){
      uint8_t pixel = random(0, 3);  // Pick a random pixel (0 to 2 for 3 LEDs)
      uint32_t color = pixels.Color(R,G,B); // GET THE COLOR
      pixels.setPixelColor(pixel, color);   // Turn on the random pixel
      pixels.show();
      delay(50);  // Wait for a moment
      pixels.setPixelColor(pixel, 0);  // Turn it off again
      pixels.show();
      delay(50);  // Pause before next sparkle
    }
    pixels.clear();
    pixels.show();
}

void PRIZM::CHASE(uint8_t R, uint8_t G, uint8_t B){
  for (int x = 0; x <= 3; x++){
    for (int i = 0; i < 3; i++) {  // For 3 pixels
      uint32_t color = pixels.Color(R,G,B);
      pixels.setPixelColor(i, color);  // Light up one pixel
      pixels.show();
      delay(75);  // Wait for a moment
      pixels.setPixelColor(i, 0);  // Turn off the pixel
      pixels.show();
      delay(75);  // Pause before next sparkle
    }
  }
  pixels.clear();
  pixels.show();
}

void PRIZM::TWINKLE(){
  for(int x = 0; x <= 50; x++){
     for (int i = 0; i < 3; i++) {
       uint32_t color = pixels.Color(random(1,255),random(1,255),random(1,255));
        pixels.setPixelColor(i, random(0, 10) < 5 ? color : 0);  // Randomly turn on/off
      }
      pixels.show();
      delay(50);
    }
    pixels.clear();
    pixels.show();
}

void PRIZM::SWEEP(uint8_t R, uint8_t G, uint8_t B){
  for (int x = 0; x <= 5; x++){
    uint32_t color = pixels.Color(R,G,B);
      for (int i = 0; i < 3; i++) {  // Move right
        pixels.setPixelColor(i, color);
        pixels.show();
        delay(100);
        pixels.setPixelColor(i, 0);
        pixels.show();
      }
      for (int i = 2; i >= 0; i--) {  // Move left
        pixels.setPixelColor(i, color);
        pixels.show();
        delay(100);
        pixels.setPixelColor(i, 0);
        pixels.show();
      }
    }
    pixels.clear();
    pixels.show();
}

void PRIZM::RAINBOW(){
  uint16_t i, j;
  for(j=0; j<256*2; j++) { //  cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++) {
      pixels.setPixelColor(i, getWheelColor(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(11);
  }
  pixels.clear();
  pixels.show();
}

void PRIZM::FADE(uint8_t R, uint8_t G, uint8_t B){
  uint32_t color = pixels.Color(R,G,B);
      for (int brightness = 0; brightness < 256; brightness++) {
        uint32_t newColor = pixels.Color((color >> 16 & 0xFF) * brightness / 255,
                                        (color >> 8 & 0xFF) * brightness / 255,
                                        (color & 0xFF) * brightness / 255);
        for (int i = 0; i < 3; i++) {
          pixels.setPixelColor(i, newColor);
        }
        pixels.show();
        delay(5);
      }
      for (int brightness = 255; brightness >= 0; brightness--) {
        uint32_t newColor = pixels.Color((color >> 16 & 0xFF) * brightness / 255,
                                        (color >> 8 & 0xFF) * brightness / 255,
                                        (color & 0xFF) * brightness / 255);
        for (int i = 0; i < 3; i++) {
          pixels.setPixelColor(i, newColor);
        }
        pixels.show();
        delay(5);
      }
    pixels.clear();
    pixels.show();
}

void PRIZM::setMotorSpeedPID(uint8_t P, uint8_t I, uint8_t D){	//=== Change the speed PID parameters for DC Chip

  uint8_t lobyteP;
  uint8_t hibyteP;
  uint8_t lobyteI;
  uint8_t hibyteI;
  uint8_t lobyteD;
  uint8_t hibyteD;

  lobyteP  = lowByte(P);
  hibyteP  = highByte(P);
  lobyteI  = lowByte(I);
  hibyteI  = highByte(I);
  lobyteD  = lowByte(D);
  hibyteD  = highByte(D);

  Wire1.beginTransmission(5);
  Wire1.write(0X4D);
  Wire1.write(hibyteP);
  Wire1.write(lobyteP);
  Wire1.write(hibyteI);
  Wire1.write(lobyteI);
  Wire1.write(hibyteD);
  Wire1.write(lobyteD);
  Wire1.endTransmission();
  delay(I2C_pace);

}

void PRIZM::setMotorTargetPID(uint8_t P, uint8_t I, uint8_t D){	//=== Change the target PID parameters for DC chip

  uint8_t lobyteP;
  uint8_t hibyteP;
  uint8_t lobyteI;
  uint8_t hibyteI;
  uint8_t lobyteD;
  uint8_t hibyteD;

  lobyteP  = lowByte(P);
  hibyteP  = highByte(P);
  lobyteI  = lowByte(I);
  hibyteI  = highByte(I);
  lobyteD  = lowByte(D);
  hibyteD  = highByte(D);

  Wire1.beginTransmission(5);    	   //transmit to DC address
  Wire1.write(0X4E);
  Wire1.write(hibyteP);
  Wire1.write(lobyteP);
  Wire1.write(hibyteI);
  Wire1.write(lobyteI);
  Wire1.write(hibyteD);
  Wire1.write(lobyteD);
  Wire1.endTransmission();
  delay(I2C_pace);

}

uint8_t PRIZM::readDCFirmware(){	  //==== Request firmware version of DC motor chip
  uint8_t byte1;
  uint8_t DCversion;

  Wire1.beginTransmission(5);
  Wire1.write(0x26);
  Wire1.endTransmission();
  delay(I2C_pace);
  Wire1.requestFrom(5, 1);
  byte1 = Wire1.read();
  DCversion=byte1;
  delay(I2C_pace);
  return DCversion;
}

uint8_t PRIZM::getDCFirmware(){	  //==== Request firmware version of DC motor chip
  uint8_t byte1;
  uint8_t DCversion;

  Wire1.beginTransmission(5);
  Wire1.write(0x26);
  Wire1.endTransmission();
  delay(I2C_pace);
  Wire1.requestFrom(5, 1);
  byte1 = Wire1.read();
  DCversion=byte1;
  delay(I2C_pace);
  return DCversion;
}

uint8_t PRIZM::readSVOFirmware(){		//==== Request firmware version of Servo motor chip
  uint8_t byte1;
  uint8_t SVOversion;

  Wire1.beginTransmission(6);
  Wire1.write(0x26);
  Wire1.endTransmission();
  delay(I2C_pace);
  Wire1.requestFrom(6, 1);
  byte1 = Wire1.read();
  SVOversion=byte1;
  delay(I2C_pace);
  return SVOversion;
}

uint8_t PRIZM::getSVOFirmware(){		//==== Request firmware version of Servo motor chip
  uint8_t byte1;
  uint8_t SVOversion;

  Wire1.beginTransmission(6);
  Wire1.write(0x26);
  Wire1.endTransmission();
  delay(I2C_pace);
  Wire1.requestFrom(6, 1);
  byte1 = Wire1.read();
  SVOversion=byte1;
  delay(I2C_pace);
  return SVOversion;
}

void PRIZM::PrizmBegin(uint8_t I2C_delay){    // Initialize I2C coms and enable motors
  Wire.begin(8,9,100000);         // ESP32 has 2 I2C HW buses. Port 6 is the default
  Wire1.begin(1,2);						    // ESP32 internal motor and servo chip bus
  Wire1.setClock(400000);         // 400000 for 400 kHz

  I2C_pace = I2C_delay;           // This sets a delay between I2C bus read and writes

  #if(USING_ESP32_VERSION == 3)
  ledcAttach(14, 100, 12);        // Attach sound pin, pwm freq, 12 bit
  #endif
  #if(USING_ESP32_VERSION == 2)
  ledcAttachPin(14, 0);           // Attach sound pin, pwm freq, 12 bit
  #endif

  ledcWrite(14, 0);               // sound off

  delay(500);               			// Give EXPANSION controllers time to reset
  enablePixels();                 // Initialize pixel object
  clearPixels();                  // set pixels off
  	     								          // SW reset on Expansion and DC + Servo chips at addresses 5 and 6 (7 is not used)
  Wire1.beginTransmission(5);     // Supported I2C addresses for EXPANSIONansion controllers is 1 - 4 (4 boxes total)
  Wire1.write(0x20);             	// If additional boxes above that are added at different addresses, 0x27 writes for each need to be added as well.
  Wire1.endTransmission();        // No guarantee that more than 4 boxes will work on single I2C bus because of cable capacitance
  delay(I2C_pace);
  Wire1.beginTransmission(6);
  Wire1.write(0x20);
  Wire1.endTransmission();
  delay(I2C_pace);
  Wire.beginTransmission(1);
  Wire.write(0x27);
  Wire.endTransmission();
  delay(10);
  Wire.beginTransmission(2);
  Wire.write(0x27);
  Wire.endTransmission();
  delay(10);
  Wire.beginTransmission(3);
  Wire.write(0x27);
  Wire.endTransmission();
  delay(10);
  Wire.beginTransmission(4);
  Wire.write(0x27);
  Wire.endTransmission();
  delay(10);

  setSoundTone(700, 100);
  setSoundTone(350, 100);
  setSoundOff();
  setStartLED(HIGH);  					           // Turn on when we're reset

  while(!readStartButton()){delay(0);}     // wait for the program start (green) button pressed
  setStartLED(LOW);   					           // turn green off

  setSoundTone(350, 100);
  setSoundTone(700, 100);
  setSoundOff();

  Wire1.beginTransmission(5);    	// Supported I2C addresses for EXPANSIONansion controllers is 1 - 4 (4 boxes total)
  Wire1.write(0x20);             	// Do a reset on Expansions and PRIZM Motor chips after green button start
  Wire1.endTransmission();        // If additional boxes above that are added at different addresses, 0x27 writes for each need to be added as well.
  delay(I2C_pace);								// No guarantee that more than 4 boxes will work on single I2C bus because of cable capacitance
  Wire1.beginTransmission(6);
  Wire1.write(0x20);
  Wire1.endTransmission();
  delay(I2C_pace);
  Wire.beginTransmission(1);
  Wire.write(0x27);
  Wire.endTransmission();
  delay(10);
  Wire.beginTransmission(2);
  Wire.write(0x27);
  Wire.endTransmission();
  delay(10);
  Wire.beginTransmission(3);
  Wire.write(0x27);
  Wire.endTransmission();
  delay(10);
  Wire.beginTransmission(4);
  Wire.write(0x27);
  Wire.endTransmission();
  delay(10);

  delay(1000);     							  // 1 second delay between time GO button is pushed and program starts gives time for resets

  Wire1.beginTransmission(5);   	// Send an "Enable" Byte to DC and Servo controller chips and EXPANSIONansion controllers
  Wire1.write(0x1E);              // enable command so that the robots won't move without a PRIZMBegin statement
  Wire1.endTransmission();
  delay(I2C_pace);
  Wire1.beginTransmission(6);
  Wire1.write(0x1E);
  Wire1.endTransmission();
  delay(I2C_pace);

  Wire.beginTransmission(1);
  Wire.write(0x25);
  Wire.endTransmission();
  delay(10);
  Wire.beginTransmission(2);
  Wire.write(0x25);
  Wire.endTransmission();
  delay(10);
  Wire.beginTransmission(3);
  Wire.write(0x25);
  Wire.endTransmission();
  delay(10);
  Wire.beginTransmission(4);
  Wire.write(0x25);
  Wire.endTransmission();
  delay(10);

//  Wire.end();
//  Wire.begin(6,7,100000); // this ishow you change I2C pins

}

void PRIZM::PrizmEnd(){  //======= Send a SW reset to all I2C devices(resets everything) This is done mainly to stop all motors

  Wire1.beginTransmission(5);     		// Supported I2C addresses for EXPANSIONansion controllers is 1 - 4
  Wire1.write(0x20);                	// 5 and 6 is PRIZM DC and Servo chips
  Wire1.endTransmission();
  delay(I2C_pace);
  Wire1.beginTransmission(6);
  Wire1.write(0x20);
  Wire1.endTransmission();
  delay(I2C_pace);
  Wire1.beginTransmission(1);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(I2C_pace);
  Wire1.beginTransmission(2);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(I2C_pace);
  Wire1.beginTransmission(3);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(I2C_pace);
  Wire1.beginTransmission(4);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(I2C_pace);


  // This was how the wdt works for the esp32 core 2.x
	// Configure hardware watchdog timer (use default timeout value of 50 ms)
#if(USING_ESP32_VERSION == 2)
	  esp_task_wdt_init(0.05, true);  // Initialize the hardware WDT
	  esp_task_wdt_add(NULL);         // Add current task to WDT
#endif

// This is the change made for esp32 core 3.x
// Set up configuration for the watchdog timer
#if(USING_ESP32_VERSION == 3)
  esp_task_wdt_config_t wdt_config = {
      .timeout_ms = 50,  // Set timeout to 50 ms
      .trigger_panic = true
  };
  // Initialize the watchdog timer with the new config structure
  esp_task_wdt_init(&wdt_config); // Pass the structure instead of an integer
  esp_task_wdt_add(NULL);         // Add the current task to the watchdog
#endif

	 for(;;)		// timeout loop  -- this will reset the ESP32
	  {
	  }

}

double PRIZM::readBatteryVoltage(){
  uint16_t Bvoltage;
  uint8_t byte1;
  uint8_t byte2;
  Wire1.beginTransmission(5);
  Wire1.write(0x59);
  Wire1.endTransmission();
  delay(I2C_pace);

  Wire1.requestFrom(5, 4);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  delay(I2C_pace);
  Bvoltage = byte2 << 8 | byte1;   // Reconstruct the 16-bit integer
  double volts = (Bvoltage * 1.6) / 100;
  return volts;
}

double PRIZM::getBatteryVoltage(){
  uint16_t Bvoltage;
  uint8_t byte1;
  uint8_t byte2;
  Wire1.beginTransmission(5);
  Wire1.write(0x59);
  Wire1.endTransmission();
  delay(I2C_pace);

  Wire1.requestFrom(5, 4);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  delay(I2C_pace);
  Bvoltage = byte2 << 8 | byte1;   // Reconstruct the 16-bit integer
  double volts = (Bvoltage * 1.6) / 100;
  return volts;
}

uint8_t PRIZM::readLineSensor(uint8_t port){     // Can sense black or white (follow the edge of a black line on a white surface)
  uint8_t pin;
  uint8_t BWstate; // black or white
  if(port == 1) {pin = 6;}
  if(port == 2) {pin = 15;}
  if(port == 3) {pin = 17;}
  if(port == 4) {pin = 10;}
  if(port == 5) {pin = 35;}
  if(port == 6) {pin = 9;}
  pinMode(pin, INPUT);
  if(HIGH == digitalRead(pin)){BWstate = 1;} else {BWstate = 0;}
  return BWstate;
}

uint8_t PRIZM::getLineSensor(uint8_t port){     // Can sense black or white (follow the edge of a black line on a white surface)
  uint8_t pin;
  uint8_t BWstate; // black or white
  if(port == 1) {pin = 6;}
  if(port == 2) {pin = 15;}
  if(port == 3) {pin = 17;}
  if(port == 4) {pin = 10;}
  if(port == 5) {pin = 35;}
  if(port == 6) {pin = 9;}
  pinMode(pin, INPUT);
  if(HIGH == digitalRead(pin)){BWstate = 1;} else {BWstate = 0;}
  return BWstate;
}

uint16_t PRIZM::readSonicSensorCM(uint8_t port){   // Returns distance of object from sensor in Centimeters
  delayMicroseconds(1000);  // added in version 2 to help with reading accuracy, can't read sonic sensors very fast
  uint8_t pin;
  uint16_t duration;
  if(port == 1) {pin = 6;}
  if(port == 2) {pin = 15;}
  if(port == 3) {pin = 17;}
  if(port == 4) {pin = 10;}
  if(port == 5) {pin = 35;}
  if(port == 6) {pin = 9;}
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin,LOW);
  pinMode(pin,INPUT);
  duration = pulseIn(pin,HIGH);
  return duration/29/2; // convert time of echo to centimeters distance
}

double PRIZM::getSonicSensor(uint8_t port, uint8_t units){   // Returns distance of object from sensor
  delayMicroseconds(1000);  // added in version 2 to help with reading accuracy, can't read sonic sensors very fast
  uint8_t pin;
  double duration;
  if(port == 1) {pin = 6;}
  if(port == 2) {pin = 15;}
  if(port == 3) {pin = 17;}
  if(port == 4) {pin = 10;}
  if(port == 5) {pin = 35;}
  if(port == 6) {pin = 9;}
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin,LOW);
  pinMode(pin,INPUT);
  duration = pulseIn(pin,HIGH);
  if(units == 0) return duration/29/2; // convert time of echo to centimeters distance
  if(units == 1) return duration/74/2; // convert time of echo to inches distance
  return 0;
}

uint16_t PRIZM::readSonicSensorIN(uint8_t port){   // Returns distance of object from sensor in Inches
  delayMicroseconds(1000);  // added in version 2 to help with reading accuracy, can't read sonic sensors very fast
  uint8_t pin;
  uint16_t duration;
  if(port == 1) {pin = 6;}
  if(port == 2) {pin = 15;}
  if(port == 3) {pin = 17;}
  if(port == 4) {pin = 10;}
  if(port == 5) {pin = 35;}
  if(port == 6) {pin = 9;}
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin,LOW);
  pinMode(pin,INPUT);
  duration = pulseIn(pin,HIGH);
  return duration/74/2; // convert time of echo to inches distance
}

uint16_t PRIZM::getSensorAnalog(uint8_t port, uint8_t pin){
  uint8_t apin; // analog input pin
  if (port == 1){
    if(pin == 1) apin = 6;
    if(pin == 2) apin = 7;
  }
  if (port == 2){
    if(pin == 1) apin = 15;
    if(pin == 2) apin = 16;
  }
  if (port == 3){
    if(pin == 1) apin = 17;
    if(pin == 2) apin = 18;
  }
  if (port == 4){
    if(pin == 1) apin = 10;
    if(pin == 2) apin = 11;
  }
  if (port == 5){
    if(pin == 1) apin = 35;
    if(pin == 2) apin = 36;
  }
  if (port == 6){
    if(pin == 1) apin = 9;
    if(pin == 2) apin = 8;
  }
  pinMode(apin, INPUT);
  uint16_t value = analogRead(apin);
  return value;
}

uint8_t PRIZM::getSensorDigital(uint8_t port, uint8_t pin){
  uint8_t dpin; // digital input pin
  if (port == 1){
    if(pin == 1) dpin = 6;
    if(pin == 2) dpin = 7;
  }
  if (port == 2){
    if(pin == 1) dpin = 15;
    if(pin == 2) dpin = 16;
  }
  if (port == 3){
    if(pin == 1) dpin = 17;
    if(pin == 2) dpin = 18;
  }
  if (port == 4){
    if(pin == 1) dpin = 10;
    if(pin == 2) dpin = 11;
  }
  if (port == 5){
    if(pin == 1) dpin = 35;
    if(pin == 2) dpin = 36;
  }
  if (port == 6){
    if(pin == 1) dpin = 9;
    if(pin == 2) dpin = 8;
  }
  pinMode(dpin, INPUT);
  uint8_t value = digitalRead(dpin);
  return value;
}

void PRIZM::setSensorDigital(uint8_t port, uint8_t pin, uint8_t level){
  uint8_t dpin; // digital output pin
  if (port == 1){
    if(pin == 1) dpin = 6;
    if(pin == 2) dpin = 7;
  }
  if (port == 2){
    if(pin == 1) dpin = 15;
    if(pin == 2) dpin = 16;
  }
  if (port == 3){
    if(pin == 1) dpin = 17;
    if(pin == 2) dpin = 18;
  }
  if (port == 4){
    if(pin == 1) dpin = 10;
    if(pin == 2) dpin = 11;
  }
  if (port == 5){
    if(pin == 1) dpin = 35;
    if(pin == 2) dpin = 36;
  }
  if (port == 6){
    if(pin == 1) dpin = 9;
    if(pin == 2) dpin = 8;
  }
  pinMode(dpin, OUTPUT);
  digitalWrite(dpin, level);
}


void PRIZM::setStartLED (uint8_t state){
  pinMode(12, OUTPUT); //===== GREEN Start Button LED is on pin 12
  if (state==1){digitalWrite(12, HIGH);}
  if (state==0){digitalWrite(12, LOW);}
}

void PRIZM::setRedLED (uint8_t state){
  uint32_t redColor = pixels.Color(255, 0, 0);  // Pure red
  if (state==1){pixels.setPixelColor(0, redColor); pixels.show();}
  if (state==0){clearPixel(1);}
}

void PRIZM::setGreenLED (uint8_t state){
  uint32_t greenColor = pixels.Color(0, 255, 0);  // Pure green
  if (state==1){pixels.setPixelColor(1, greenColor); pixels.show();}
  if (state==0){clearPixel(2);}
}

void PRIZM::setBlueLED (uint8_t state){
  uint32_t blueColor = pixels.Color(0, 0, 255);  // Pure blue
  if (state==1){pixels.setPixelColor(2, blueColor); pixels.show();}
  if (state==0){clearPixel(3);}
}

uint8_t PRIZM::readStartButton(){       //============== function returns; unpressed button == 0; pressed button == 1
  pinMode(5, INPUT); 	// Button is on pin 5; unpressed = high, pressed = low
  uint8_t StartBtn = digitalRead(5);
  StartBtn = !StartBtn; // toggle to make pressed true and unpressed false
  return StartBtn;
}

uint8_t PRIZM::getButton(uint8_t button){       //============== function returns; unpressed button == 0; pressed button == 1
  pinMode(button, INPUT); 	// Button is on pin 5; unpressed = high, pressed = low
  uint8_t btn = digitalRead(button);
  btn = !btn;       // toggle to make pressed true and unpressed false
  return btn;
}

void PRIZM::setServoSpeed (uint8_t channel, uint8_t servospeed){   //=========== function for setting PRIZM servo speeds individually

  uint8_t xmit = 0;
  // gotta see if new position is different than last - servo chip can't be hit with fast repeating i2c interupts
  if(channel==1 && servospeed != lastServoSpeed_1) {xmit = 1; lastServoSpeed_1 = servospeed;}
  if(channel==2 && servospeed != lastServoSpeed_2) {xmit = 1; lastServoSpeed_2 = servospeed;}
  if(channel==3 && servospeed != lastServoSpeed_3) {xmit = 1; lastServoSpeed_3 = servospeed;}
  if(channel==4 && servospeed != lastServoSpeed_4) {xmit = 1; lastServoSpeed_4 = servospeed;}
  if(channel==5 && servospeed != lastServoSpeed_5) {xmit = 1; lastServoSpeed_5 = servospeed;}
  if(channel==6 && servospeed != lastServoSpeed_6) {xmit = 1; lastServoSpeed_6 = servospeed;}

  if(xmit == 1){
      if(channel==1){channel= 0x28;}
      if(channel==2){channel= 0x29;}
      if(channel==3){channel= 0x2A;}
      if(channel==4){channel= 0x2B;}
      if(channel==5){channel= 0x2C;}
      if(channel==6){channel= 0x2D;}

      Wire1.beginTransmission(6);
      Wire1.write(channel);
      Wire1.write(servospeed);
      Wire1.endTransmission();
      delay(I2C_pace);
    }
}

void PRIZM::setServoSpeeds (uint8_t servospeed1, uint8_t servospeed2, uint8_t servospeed3, uint8_t servospeed4, uint8_t servospeed5, uint8_t servospeed6){   // function to set all PRIZM servo speeds at once

  uint8_t xmit = 0;
  // gotta see if new position is different than last - servo chip can't be hit with fast repeating i2c interupts
  if(servospeed1 != lastServoSpeed_1) {xmit = 1; lastServoSpeed_1 = servospeed1;}
  if(servospeed2 != lastServoSpeed_2) {xmit = 1; lastServoSpeed_2 = servospeed2;}
  if(servospeed3 != lastServoSpeed_3) {xmit = 1; lastServoSpeed_3 = servospeed3;}
  if(servospeed4 != lastServoSpeed_4) {xmit = 1; lastServoSpeed_4 = servospeed4;}
  if(servospeed5 != lastServoSpeed_5) {xmit = 1; lastServoSpeed_5 = servospeed5;}
  if(servospeed6 != lastServoSpeed_6) {xmit = 1; lastServoSpeed_6 = servospeed6;}

  if(xmit == 1){
      Wire1.beginTransmission(6);
      Wire1.write(0x2E);
      Wire1.write(servospeed1);
      Wire1.write(servospeed2);
      Wire1.write(servospeed3);
      Wire1.write(servospeed4);
      Wire1.write(servospeed5);
      Wire1.write(servospeed6);
      Wire1.endTransmission();
      delay(I2C_pace);
    }
}

void PRIZM::setServoPosition (uint8_t channel, uint8_t servoposition){   //function to set PRIZM servo positions individually

  uint8_t xmit = 0;
  // gotta see if new position is different than last - servo chip can't be hit with fast repeating i2c interupts
  if(channel==1 && servoposition != lastPosition_1) {xmit = 1; lastPosition_1 = servoposition;}
  if(channel==2 && servoposition != lastPosition_2) {xmit = 1; lastPosition_2 = servoposition;}
  if(channel==3 && servoposition != lastPosition_3) {xmit = 1; lastPosition_3 = servoposition;}
  if(channel==4 && servoposition != lastPosition_4) {xmit = 1; lastPosition_4 = servoposition;}
  if(channel==5 && servoposition != lastPosition_5) {xmit = 1; lastPosition_5 = servoposition;}
  if(channel==6 && servoposition != lastPosition_6) {xmit = 1; lastPosition_6 = servoposition;}

  if(xmit == 1){
      if(channel==1){channel= 0x2F;}
      if(channel==2){channel= 0x30;}
      if(channel==3){channel= 0x31;}
      if(channel==4){channel= 0x32;}
      if(channel==5){channel= 0x33;}
      if(channel==6){channel= 0x34;}

      Wire1.beginTransmission(6);
      Wire1.write(channel);
      Wire1.write(servoposition);
      Wire1.endTransmission();
      delay(I2C_pace);
  }
}

void PRIZM::setServoPositions (uint8_t servoposition1, uint8_t servoposition2, uint8_t servoposition3, uint8_t servoposition4, uint8_t servoposition5, uint8_t servoposition6){  // Sets all PRIZM servo positions at once

  uint8_t xmit = 0;
  // gotta see if new position is different than last - servo chip can't be hit with fast repeating i2c interupts
  if(servoposition1 != lastPosition_1) {xmit = 1; lastPosition_1 = servoposition1;}
  if(servoposition2 != lastPosition_2) {xmit = 1; lastPosition_2 = servoposition2;}
  if(servoposition3 != lastPosition_3) {xmit = 1; lastPosition_3 = servoposition3;}
  if(servoposition4 != lastPosition_4) {xmit = 1; lastPosition_4 = servoposition4;}
  if(servoposition5 != lastPosition_5) {xmit = 1; lastPosition_5 = servoposition5;}
  if(servoposition6 != lastPosition_6) {xmit = 1; lastPosition_6 = servoposition6;}

  if(xmit == 1){
      Wire1.beginTransmission(6);
      Wire1.write(0x35);
      Wire1.write(servoposition1);
      Wire1.write(servoposition2);
      Wire1.write(servoposition3);
      Wire1.write(servoposition4);
      Wire1.write(servoposition5);
      Wire1.write(servoposition6);
      Wire1.endTransmission();
      delay(I2C_pace);
    }

}

void PRIZM::setCRServoState (uint8_t channel, int16_t state, int8_t trim){   // function to set PRIZM CR servos speed and direction -100|0|100
  uint8_t xmit=0;
  // gotta see if new position is different than last - servo chip can't be hit with fast repeating i2c interupts
  if(channel==1 && state != lastState_1) {xmit = 1; lastState_1 = state;}
  if(channel==2 && state != lastState_2) {xmit = 1; lastState_2 = state;}
  if(channel==3 && state != lastState_3) {xmit = 1; lastState_3 = state;}
  if(channel==4 && state != lastState_4) {xmit = 1; lastState_4 = state;}
  if(channel==5 && state != lastState_5) {xmit = 1; lastState_5 = state;}
  if(channel==6 && state != lastState_6) {xmit = 1; lastState_6 = state;}

  if(xmit == 1){
    	if(channel==1){channel= 0x2F;}
      if(channel==2){channel= 0x30;}
      if(channel==3){channel= 0x31;}
      if(channel==4){channel= 0x32;}
      if(channel==5){channel= 0x33;}
      if(channel==6){channel= 0x34;}

    	uint8_t crspeed = map(state,-100,100,0,180);
    	crspeed = crspeed + trim;
    	crspeed = constrain(crspeed,0,180);

      Wire1.beginTransmission(6);
      Wire1.write(channel);
      Wire1.write(crspeed);
      Wire1.endTransmission();
      delay(I2C_pace);
  }

}

uint8_t PRIZM::readServoPosition (uint8_t channel){		// read the servo PRIZM servo positions
  uint8_t readServoPosition;    // return value variable

  if(channel==1){channel= 0x36;}
  if(channel==2){channel= 0x37;}
  if(channel==3){channel= 0x38;}
  if(channel==4){channel= 0x39;}
  if(channel==5){channel= 0x3A;}
  if(channel==6){channel= 0x3B;}

  Wire1.beginTransmission(6);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(I2C_pace);
  Wire1.requestFrom(6, 1);
  readServoPosition = Wire1.read();
  delay(I2C_pace);
  return readServoPosition;
}

uint8_t PRIZM::getServoPosition (uint8_t channel){		// read the servo PRIZM servo positions
  uint8_t readServoPosition;    // return value variable

  if(channel==1){channel= 0x36;}
  if(channel==2){channel= 0x37;}
  if(channel==3){channel= 0x38;}
  if(channel==4){channel= 0x39;}
  if(channel==5){channel= 0x3A;}
  if(channel==6){channel= 0x3B;}

  Wire1.beginTransmission(6);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(I2C_pace);
  Wire1.requestFrom(6, 1);
  readServoPosition = Wire1.read();
  delay(I2C_pace);
  return readServoPosition;
}

void PRIZM::enableServos(uint8_t condition){
  if(condition == 0){           // disable
    Wire1.beginTransmission(6);
    Wire1.write(0x3E);
    Wire1.endTransmission();
  }
  if(condition == 1){           // re-enable
    Wire1.beginTransmission(6);
    Wire1.write(0x3F);
    Wire1.endTransmission();
  }
  delay(I2C_pace);
}

void PRIZM::setMotorPWM_Freq(uint16_t freq){  // set/change the DC motor PWM frequency, default is 12KHz
  uint8_t highByte = (freq >> 8) & 0xFF;
  uint8_t lowByte  = freq & 0xFF;

  	Wire1.beginTransmission(5);
  	Wire1.write(0x21);
  	Wire1.write(highByte);
		Wire1.write(lowByte);
  	Wire1.endTransmission();
    delay(I2C_pace);
}

void PRIZM::setMotorBrake(uint8_t channel, uint8_t brake){
  if(brake) setMotorPower(channel, 125); // brake
  if(!brake) setMotorPower(channel, 0);  // coast, release brake
}

void PRIZM::setMotorPower(uint8_t channel, int16_t power)	// set Motor Channel power on PRIZM
{

	if(channel==1){channel = 0x28;}   	// DC channel 1
	if(channel==2){channel = 0x29;}   	// DC channel 2
	if(channel==3){channel = 0x2A;}   	// DC channel 2
	if(channel==4){channel = 0x2B;}   	// DC channel 2

	uint8_t highByte = (power >> 8) & 0xFF;
  uint8_t lowByte  = power & 0xFF;

  	Wire1.beginTransmission(5);
  	Wire1.write(channel);
  	Wire1.write(highByte);
		Wire1.write(lowByte);
  	Wire1.endTransmission();
	  delay(I2C_pace);
}


void PRIZM::setMotorPowers (int16_t power1, int16_t power2, int16_t power3, int16_t power4){     //power only Block Command for PRIZM Motor 1-4 (all in one transmission)

	uint8_t highByte1 = (power1 >> 8) & 0xFF;
  uint8_t lowByte1  = power1 & 0xFF;
	uint8_t highByte2 = (power2 >> 8) & 0xFF;
  uint8_t lowByte2  = power2 & 0xFF;
	uint8_t highByte3 = (power3 >> 8) & 0xFF;
  uint8_t lowByte3  = power3 & 0xFF;
	uint8_t highByte4 = (power4 >> 8) & 0xFF;
  uint8_t lowByte4  = power4 & 0xFF;

  Wire1.beginTransmission(5);
  Wire1.write(0x2E);
  Wire1.write(highByte1);
  Wire1.write(lowByte1);
	Wire1.write(highByte2);
  Wire1.write(lowByte2);
	Wire1.write(highByte3);
  Wire1.write(lowByte3);
	Wire1.write(highByte4);
  Wire1.write(lowByte4);
  Wire1.endTransmission();
  delay(I2C_pace);

}

void PRIZM::setMotorSpeed (uint8_t channel, int16_t Mspeed){      // === set speed of each PRIZM DC motor == requires a 1440 CPR installed encoder to do the PID

	uint8_t highByte = (Mspeed >> 8) & 0xFF;
  uint8_t lowByte  = Mspeed & 0xFF;

	if(channel==1){channel = 0x2F;}   	// DC channel 1
	if(channel==2){channel = 0x30;}   	// DC channel 2
	if(channel==3){channel = 0x31;}   	// DC channel 3
	if(channel==4){channel = 0x32;}   	// DC channel 4

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.write(highByte);
  Wire1.write(lowByte);
  Wire1.endTransmission();
  delay(I2C_pace);

}

void PRIZM::setMotorSpeeds (int16_t Mspeed1, int16_t Mspeed2, int16_t Mspeed3, int16_t Mspeed4){      // === BLOCK write to set speeds of all PRIZM motors at once == 1440 CPR encoder must be installed to do PID

	uint8_t highByte1 = (Mspeed1 >> 8) & 0xFF;
	uint8_t lowByte1  = Mspeed1 & 0xFF;
	uint8_t highByte2 = (Mspeed2 >> 8) & 0xFF;
	uint8_t lowByte2  = Mspeed2 & 0xFF;
	uint8_t highByte3 = (Mspeed3 >> 8) & 0xFF;
	uint8_t lowByte3  = Mspeed3 & 0xFF;
	uint8_t highByte4 = (Mspeed4 >> 8) & 0xFF;
	uint8_t lowByte4  = Mspeed4 & 0xFF;

  Wire1.beginTransmission(5);
  Wire1.write(0x33);
  Wire1.write(highByte1);
  Wire1.write(lowByte1);
  Wire1.write(highByte2);
  Wire1.write(lowByte2);
	Wire1.write(highByte3);
	Wire1.write(lowByte3);
	Wire1.write(highByte4);
	Wire1.write(lowByte4);
  Wire1.endTransmission();
  delay(I2C_pace);
}

void PRIZM::setMotorTarget (uint8_t channel, int16_t Mspeed, int32_t Mtarget){      // === set speed and encoder target of each PRIZM DC motor == requires a 1440 CPR encoder to do the PID

  uint8_t highByte1 = (Mspeed >> 8) & 0xFF;
	uint8_t lowByte1  = Mspeed & 0xFF;

  uint8_t one   = (Mtarget>>24) & 0xFF;
  uint8_t two   = (Mtarget>>16) & 0xFF;
  uint8_t three = (Mtarget>>8) & 0xFF;
  uint8_t four  = (Mtarget) & 0xFF;

  if(channel==1){channel= 0x34;}   // DC channel 1
  if(channel==2){channel= 0x35;}   // DC channel 2
  if(channel==3){channel= 0x36;}   // DC channel 3
  if(channel==4){channel= 0x37;}   // DC channel 4

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.write(highByte1);
  Wire1.write(lowByte1);
  Wire1.write(one);
  Wire1.write(two);
  Wire1.write(three);
  Wire1.write(four);
  Wire1.endTransmission();
  delay(I2C_pace);
}

void PRIZM::setMotorTargets (int16_t Mspeed1, int32_t Mtarget1, int16_t Mspeed2, int32_t Mtarget2, int16_t Mspeed3, int32_t Mtarget3, int16_t Mspeed4, int32_t Mtarget4){      // === BLOCK WRITE set speed and encoder target of both PRIZM DC motors == requires a 1440 CPR encoder to do the PID

  uint8_t highByte1 = (Mspeed1 >> 8) & 0xFF;
	uint8_t lowByte1  = Mspeed1 & 0xFF;
  uint8_t highByte2 = (Mspeed2 >> 8) & 0xFF;
	uint8_t lowByte2  = Mspeed2 & 0xFF;
  uint8_t highByte3 = (Mspeed3 >> 8) & 0xFF;
	uint8_t lowByte3  = Mspeed3 & 0xFF;
  uint8_t highByte4 = (Mspeed4 >> 8) & 0xFF;
	uint8_t lowByte4  = Mspeed4 & 0xFF;

  uint8_t one   = (Mtarget1>>24) & 0xFF;
  uint8_t two   = (Mtarget1>>16) & 0xFF;
  uint8_t three = (Mtarget1>>8) & 0xFF;
  uint8_t four  = (Mtarget1) & 0xFF;

  uint8_t five   = (Mtarget2>>24) & 0xFF;
  uint8_t six    = (Mtarget2>>16) & 0xFF;
  uint8_t seven  = (Mtarget2>>8) & 0xFF;
  uint8_t eight  = (Mtarget2) & 0xFF;

  uint8_t nine   = (Mtarget3>>24) & 0xFF;
  uint8_t ten    = (Mtarget3>>16) & 0xFF;
  uint8_t eleven = (Mtarget3>>8) & 0xFF;
  uint8_t twelve = (Mtarget3) & 0xFF;

  uint8_t thirteen   = (Mtarget4>>24) & 0xFF;
  uint8_t fourteen   = (Mtarget4>>16) & 0xFF;
  uint8_t fifteen    = (Mtarget4>>8) & 0xFF;
  uint8_t sixteen    = (Mtarget4) & 0xFF;

  Wire1.beginTransmission(5);
  Wire1.write(0x38);
  Wire1.write(highByte1);
  Wire1.write(lowByte1);
  Wire1.write(one);
  Wire1.write(two);
  Wire1.write(three);
  Wire1.write(four);
  Wire1.write(highByte2);
  Wire1.write(lowByte2);
  Wire1.write(five);
  Wire1.write(six);
  Wire1.write(seven);
  Wire1.write(eight);
  Wire1.write(highByte3);
  Wire1.write(lowByte3);
  Wire1.write(nine);
  Wire1.write(ten);
  Wire1.write(eleven);
  Wire1.write(twelve);
  Wire1.write(highByte4);
  Wire1.write(lowByte4);
  Wire1.write(thirteen);
  Wire1.write(fourteen);
  Wire1.write(fifteen);
  Wire1.write(sixteen);
  Wire1.endTransmission();
  delay(I2C_pace);
}

void PRIZM::setMotorDegree (uint8_t channel, int16_t Mspeed, int32_t Mdegrees){      // === set speed and encoder target of each PRIZM DC motor in DEGREES  == requires a 1440 CPR encoder to do the PID

  uint8_t highByte1 = (Mspeed >> 8) & 0xFF;
	uint8_t lowByte1  = Mspeed & 0xFF;

  uint8_t one   = (Mdegrees>>24) & 0xFF;
  uint8_t two   = (Mdegrees>>16) & 0xFF;
  uint8_t three = (Mdegrees>>8) & 0xFF;
  uint8_t four  = (Mdegrees) & 0xFF;

  if(channel==1){channel= 0x4F;}   // DC channel 1
  if(channel==2){channel= 0x50;}   // DC channel 2
  if(channel==3){channel= 0x51;}   // DC channel 3
  if(channel==4){channel= 0x52;}   // DC channel 4

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.write(highByte1);
  Wire1.write(lowByte1);
  Wire1.write(one);
  Wire1.write(two);
  Wire1.write(three);
  Wire1.write(four);
  Wire1.endTransmission();
  delay(I2C_pace);
}

void PRIZM::setMotorDegrees (int16_t Mspeed1, int32_t Mdegrees1, int16_t Mspeed2, int32_t Mdegrees2, int16_t Mspeed3, int32_t Mdegrees3, int16_t Mspeed4, int32_t Mdegrees4){      // === BLOCK WRITE set speed and encoder target in DEGREES of both PRIZM DC motors == requires a 1440 CPR encoder to do the PID

  uint8_t highByte1 = (Mspeed1 >> 8) & 0xFF;
	uint8_t lowByte1  = Mspeed1 & 0xFF;
  uint8_t highByte2 = (Mspeed2 >> 8) & 0xFF;
	uint8_t lowByte2  = Mspeed2 & 0xFF;
  uint8_t highByte3 = (Mspeed3 >> 8) & 0xFF;
	uint8_t lowByte3  = Mspeed3 & 0xFF;
  uint8_t highByte4 = (Mspeed4 >> 8) & 0xFF;
	uint8_t lowByte4  = Mspeed4 & 0xFF;

  uint8_t one   = (Mdegrees1>>24) & 0xFF;
  uint8_t two   = (Mdegrees1>>16) & 0xFF;
  uint8_t three = (Mdegrees1>>8) & 0xFF;
  uint8_t four  = (Mdegrees1) & 0xFF;

  uint8_t five   = (Mdegrees2>>24) & 0xFF;
  uint8_t six    = (Mdegrees2>>16) & 0xFF;
  uint8_t seven  = (Mdegrees2>>8) & 0xFF;
  uint8_t eight  = (Mdegrees2) & 0xFF;

  uint8_t nine   = (Mdegrees3>>24) & 0xFF;
  uint8_t ten    = (Mdegrees3>>16) & 0xFF;
  uint8_t eleven = (Mdegrees3>>8) & 0xFF;
  uint8_t twelve = (Mdegrees3) & 0xFF;

  uint8_t thirteen   = (Mdegrees4>>24) & 0xFF;
  uint8_t fourteen   = (Mdegrees4>>16) & 0xFF;
  uint8_t fifteen    = (Mdegrees4>>8) & 0xFF;
  uint8_t sixteen    = (Mdegrees4) & 0xFF;

  Wire1.beginTransmission(5);
  Wire1.write(0x53);
  Wire1.write(highByte1);
  Wire1.write(lowByte1);
  Wire1.write(one);
  Wire1.write(two);
  Wire1.write(three);
  Wire1.write(four);
  Wire1.write(highByte2);
  Wire1.write(lowByte2);
  Wire1.write(five);
  Wire1.write(six);
  Wire1.write(seven);
  Wire1.write(eight);
  Wire1.write(highByte3);
  Wire1.write(lowByte3);
  Wire1.write(nine);
  Wire1.write(ten);
  Wire1.write(eleven);
  Wire1.write(twelve);
  Wire1.write(highByte4);
  Wire1.write(lowByte4);
  Wire1.write(thirteen);
  Wire1.write(fourteen);
  Wire1.write(fifteen);
  Wire1.write(sixteen);
  Wire1.endTransmission();
  delay(I2C_pace);

}

int32_t PRIZM::readEncoderCount (uint8_t channel){   // ============================= READ PRIZM ENCODER DATA COUNTS ====================================
  int32_t eCount;

  uint8_t byte1;
  uint8_t byte2;
  uint8_t byte3;
  uint8_t byte4;

  if(channel==1){channel= 0x39;}       // channel 1 encoder FOR count value
  if(channel==2){channel= 0x3A;}       // channel 2 encoder FOR count value
  if(channel==3){channel= 0x3B;}       // channel 3 encoder FOR count value
  if(channel==4){channel= 0x3C;}       // channel 4 encoder FOR count value

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(I2C_pace);

  Wire1.requestFrom(5, 4);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  byte3 = Wire1.read();
  byte4 = Wire1.read();
  delay(I2C_pace);

  eCount = byte4 << 24 | byte3 << 16 | byte2 << 8 | byte1;   // Reconstruct the 32-bit signed integer
  return eCount;
}

int32_t PRIZM::getEncoderCount (uint8_t channel){   // ============================= READ PRIZM ENCODER DATA COUNTS ====================================
  int32_t eCount;

  uint8_t byte1;
  uint8_t byte2;
  uint8_t byte3;
  uint8_t byte4;

  if(channel==1){channel= 0x39;}       // channel 1 encoder FOR count value
  if(channel==2){channel= 0x3A;}       // channel 2 encoder FOR count value
  if(channel==3){channel= 0x3B;}       // channel 3 encoder FOR count value
  if(channel==4){channel= 0x3C;}       // channel 4 encoder FOR count value

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(I2C_pace);

  Wire1.requestFrom(5, 4);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  byte3 = Wire1.read();
  byte4 = Wire1.read();
  delay(I2C_pace);

  eCount = byte4 << 24 | byte3 << 16 | byte2 << 8 | byte1;   // Reconstruct the 32-bit signed integer
  return eCount;
}

int32_t PRIZM::readEncoderDegrees (uint8_t channel){   // ============================= READ PRIZM ENCODER DATA DEGREES ====================================
  int32_t eCount;

  uint8_t byte1;
  uint8_t byte2;
  uint8_t byte3;
  uint8_t byte4;

  if(channel==1){channel= 0x54;}       // channel 1 encoder FOR degrees
  if(channel==2){channel= 0x55;}       // channel 2 encoder FOR degrees
  if(channel==3){channel= 0x56;}       // channel 3 encoder FOR degrees
  if(channel==4){channel= 0x57;}       // channel 4 encoder FOR degrees

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(I2C_pace);

  Wire1.requestFrom(5, 4);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  byte3 = Wire1.read();
  byte4 = Wire1.read();
  delay(I2C_pace);

  eCount = byte4 << 24 | byte3 << 16 | byte2 << 8 | byte1;   // Reconstruct the 32-bit signed integer
  return eCount;
}

int32_t PRIZM::getEncoderDegrees (uint8_t channel){   // ============================= READ PRIZM ENCODER DATA DEGREES ====================================
  int32_t eCount;

  uint8_t byte1;
  uint8_t byte2;
  uint8_t byte3;
  uint8_t byte4;

  if(channel==1){channel= 0x54;}       // channel 1 encoder FOR degrees
  if(channel==2){channel= 0x55;}       // channel 2 encoder FOR degrees
  if(channel==3){channel= 0x56;}       // channel 3 encoder FOR degrees
  if(channel==4){channel= 0x57;}       // channel 4 encoder FOR degrees

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(I2C_pace);

  Wire1.requestFrom(5, 4);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  byte3 = Wire1.read();
  byte4 = Wire1.read();
  delay(I2C_pace);

  eCount = byte4 << 24 | byte3 << 16 | byte2 << 8 | byte1;   // Reconstruct the 32-bit signed integer
  return eCount;
}

void PRIZM::resetEncoder (uint8_t channel){    // =================== RESET PRIZM ENCODERS  =============================

  if(channel==1){channel= 0x3E;}       // channel 1 encoder reset command
  if(channel==2){channel= 0x3F;}       // channel 2 encoder reset command
  if(channel==3){channel= 0x40;}       // channel 3 encoder reset command
  if(channel==4){channel= 0x41;}       // channel 4 encoder reset command

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(I2C_pace);

}

void PRIZM::resetEncoders(){					// ================== Reset All PRIZM Encoders at once =========================

  Wire1.beginTransmission(5);
  Wire1.write(0x42);
  Wire1.endTransmission();
  delay(I2C_pace);

}

uint8_t PRIZM::readMotorBusy (uint8_t channel){			// ================== Read Busy Status of PRIZM DC motor channel =======================
  uint8_t byte1;
  uint8_t MotorStatus;

  if(channel==1){channel= 0x43;}       // channel 1 busy flag
  if(channel==2){channel= 0x44;}       // channel 2 busy flag
  if(channel==3){channel= 0x45;}       // channel 1 busy flag
  if(channel==4){channel= 0x46;}       // channel 2 busy flag

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(I2C_pace);

  Wire1.requestFrom(5, 1);
  byte1 = Wire1.read();
  MotorStatus=byte1;
  delay(I2C_pace);

  return MotorStatus;
}

uint8_t PRIZM::getMotorBusy (uint8_t channel){			// ================== Read Busy Status of PRIZM DC motor channel =======================
  uint8_t byte1;
  uint8_t MotorStatus;

  if(channel==1){channel= 0x43;}       // channel 1 busy flag
  if(channel==2){channel= 0x44;}       // channel 2 busy flag
  if(channel==3){channel= 0x45;}       // channel 1 busy flag
  if(channel==4){channel= 0x46;}       // channel 2 busy flag

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(I2C_pace);

  Wire1.requestFrom(5, 1);
  byte1 = Wire1.read();
  MotorStatus=byte1;
  delay(I2C_pace);

  return MotorStatus;
}

void PRIZM::setMotorInvert (uint8_t channel, uint8_t invert){						// ======================== Set the PRIZM DC Motor Direction invert status ====================

  if(channel==1){channel= 0x47;}       // channel 1
  if(channel==2){channel= 0x48;}       // channel 2
  if(channel==3){channel= 0x49;}       // channel 3
  if(channel==4){channel= 0x4A;}       // channel 4

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.write(invert);
  Wire1.endTransmission();
  delay(I2C_pace);

}

//========= EXPANSION BOXES ===========================================================================================================================================================

void EXPANSION::controllerEnable(int address){

	  Wire1.beginTransmission(address);    	// Send an "Enable" Byte to EXPANSION controller at address/ID
	  Wire1.write(0x25);
	  Wire1.endTransmission();
	  delay(25);
}

void EXPANSION::controllerReset(int address){

	  Wire1.beginTransmission(address);    	// Send an "reset" Byte to EXPANSION controller at address/ID
	  Wire1.write(0x27);
	  Wire1.endTransmission();
	  delay(25);
}

//void EXPANSION::WDT_STOP (int address){			//===== This forces a watch dog timer HARD STOP on the expansion controller at address #

//	Wire1.beginTransmission(address);
//  	Wire1.write(0x23);
//  	Wire1.endTransmission();
//  	delay(50);

//}

void EXPANSION::setExpID(int newID){		// === command to change ID/ I2C address of a TETRIX Expansion DC or Servo Controller.
											      // There can only be one expansion box connected to PRIZM when changing ID's.
	int oldID;								// No other I2C devices can be connected to sensor ports when executing this command.

	for (int i = 1; i < 120; i++) {			// Spin up I2C addresses from 1 - 120

    	Wire1.beginTransmission (i);

	    if ((Wire1.endTransmission () == 0) && ((i < 5) || (i > 6))) 	// Capture response from expansion controller (ignore 5 and 6 - they are used by PRIZM)
	      {
	      oldID = i;
	      delay (10);
	      }
        }

		Wire1.beginTransmission(oldID);		// Send new ID/address to the found Expansion Controller
        Wire1.write(0x24);
        Wire1.write(newID);
        Wire1.endTransmission();
 		delay(10);

		pinMode(12, OUTPUT); 				  // ===== GREEN LED is on pin 6
		digitalWrite(12, HIGH);				// Flash PRIZM Pro Green LED when finished
		delay(250);
		digitalWrite(12, LOW);
		delay(250);
		digitalWrite(12, HIGH);
		delay(250);
		digitalWrite(12, LOW);

}

int EXPANSION::readExpID(){					// === command to get the I2C address / ID from a TETRIX DC or Servo Expansion Controller
											    // There can only be one expansion box connected to PRIZM when using this function
	int ID;									// All other I2C devices must also be disconnected from sensor ports when using this function

	for (int i = 1; i < 120; i++) {			// Spin up I2C addresses from 1 - 120

    	Wire1.beginTransmission (i);

	    if ((Wire1.endTransmission () == 0) && ((i < 5) || (i > 6))) 	// Capture response from expansion controller (ignore 5 and 6 - they are used by PRIZM)
	      {
	      ID = i;
	      delay (10);
	      }
        }

	return ID;
}

// added a get for prizm pro
int EXPANSION::getExpID(){					// === command to get the I2C address / ID from a TETRIX DC or Servo Expansion Controller
											    // There can only be one expansion box connected to PRIZM when using this function
	int ID;									// All other I2C devices must also be disconnected from sensor ports when using this function

	for (int i = 1; i < 120; i++) {			// Spin up I2C addresses from 1 - 120

    	Wire1.beginTransmission (i);

	    if ((Wire1.endTransmission () == 0) && ((i < 5) || (i > 6))) 	// Capture response from expansion controller (ignore 5 and 6 - they are used by PRIZM)
	      {
	      ID = i;
	      delay (10);
	      }
        }

	return ID;
}

void EXPANSION::setMotorSpeedPID(int address, int P, int I, int D){	//=== Change the speed PID parameters for DC EXPANSIONANSION

  int lobyteP;
  int hibyteP;
  int lobyteI;
  int hibyteI;
  int lobyteD;
  int hibyteD;

  lobyteP  = lowByte(P);
  hibyteP  = highByte(P);
  lobyteI  = lowByte(I);
  hibyteI  = highByte(I);
  lobyteD  = lowByte(D);
  hibyteD  = highByte(D);

  Wire1.beginTransmission(address);
  Wire1.write(0X56);
  Wire1.write(hibyteP);
  Wire1.write(lobyteP);
  Wire1.write(hibyteI);
  Wire1.write(lobyteI);
  Wire1.write(hibyteD);
  Wire1.write(lobyteD);
  Wire1.endTransmission();
  delay(10);

}

void EXPANSION::setMotorTargetPID(int address, int P, int I, int D){	//=== Change the target PID parameters for DC EXPANSIONANSION

  int lobyteP;
  int hibyteP;
  int lobyteI;
  int hibyteI;
  int lobyteD;
  int hibyteD;

  lobyteP  = lowByte(P);
  hibyteP  = highByte(P);
  lobyteI  = lowByte(I);
  hibyteI  = highByte(I);
  lobyteD  = lowByte(D);
  hibyteD  = highByte(D);

  Wire1.beginTransmission(address);
  Wire1.write(0X57);
  Wire1.write(hibyteP);
  Wire1.write(lobyteP);
  Wire1.write(hibyteI);
  Wire1.write(lobyteI);
  Wire1.write(hibyteD);
  Wire1.write(lobyteD);
  Wire1.endTransmission();
  delay(10);

}

int EXPANSION::readDCFirmware(int address){	  //==== Request firmware version of DC EXPANSIONANSION
  int byte1;
  int DCversion;

  Wire1.beginTransmission(address);
  Wire1.write(0x26);
  Wire1.endTransmission();
  delay(10);
  Wire1.requestFrom(address, 1);
  byte1 = Wire1.read();
  DCversion=byte1;
  delay(10);
  return DCversion;
}

// added a get
int EXPANSION::getDCFirmware(int address){	  //==== Request firmware version of DC EXPANSIONANSION
  int byte1;
  int DCversion;

  Wire1.beginTransmission(address);
  Wire1.write(0x26);
  Wire1.endTransmission();
  delay(10);
  Wire1.requestFrom(address, 1);
  byte1 = Wire1.read();
  DCversion=byte1;
  delay(10);
  return DCversion;
}

int EXPANSION::readSVOFirmware(int address){		//==== Request firmware version of Servo EXPANSIONANSION
  int byte1;
  int SVOversion;

  Wire1.beginTransmission(address);
  Wire1.write(0x26);
  Wire1.endTransmission();
  delay(10);
  Wire1.requestFrom(address, 1);
  byte1 = Wire1.read();
  SVOversion=byte1;
  delay(10);

  return SVOversion;
}

// added a get
int EXPANSION::getSVOFirmware(int address){		//==== Request firmware version of Servo EXPANSIONANSION
  int byte1;
  int SVOversion;

  Wire1.beginTransmission(address);
  Wire1.write(0x26);
  Wire1.endTransmission();
  delay(10);
  Wire1.requestFrom(address, 1);
  byte1 = Wire1.read();
  SVOversion=byte1;
  delay(10);

  return SVOversion;
}

int EXPANSION::readBatteryVoltage(int address){
  int Bvoltage;

  byte byte1;
  byte byte2;

  Wire1.beginTransmission(address);
  Wire1.write(0x53);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(address, 2);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  Bvoltage = byte1;
  Bvoltage = (Bvoltage*256)+byte2;
  delay(10);
  return Bvoltage;
}

// added a get
int EXPANSION::getBatteryVoltage(int address){
  int Bvoltage;

  byte byte1;
  byte byte2;

  Wire1.beginTransmission(address);
  Wire1.write(0x53);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(address, 2);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  Bvoltage = byte1;
  Bvoltage = (Bvoltage*256)+byte2;
  delay(10);
  return Bvoltage;
}

void EXPANSION::setServoSpeed (int address, int channel, int servospeed){   //=========== function for setting servo speeds individually for  servo EXPANSIONANSION

  if(channel==1){channel= 0x28;}
  if(channel==2){channel= 0x29;}
  if(channel==3){channel= 0x2A;}
  if(channel==4){channel= 0x2B;}
  if(channel==5){channel= 0x2C;}
  if(channel==6){channel= 0x2D;}

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.write(servospeed);
  Wire1.endTransmission();
  delay(10);

}

void EXPANSION::setServoSpeeds (int address, int servospeed1, int servospeed2, int servospeed3, int servospeed4, int servospeed5, int servospeed6){   // function to set all EXPANSIONANSION servo speeds at once

  Wire1.beginTransmission(address);
  Wire1.write(0x2E);
  Wire1.write(servospeed1);
  Wire1.write(servospeed2);
  Wire1.write(servospeed3);
  Wire1.write(servospeed4);
  Wire1.write(servospeed5);
  Wire1.write(servospeed6);
  Wire1.endTransmission();
  delay(10);

}

void EXPANSION::setServoPosition (int address, int channel, int servoposition){   //function to set EXPANSION servo positions individually

  if(channel==1){channel= 0x2F;}
  if(channel==2){channel= 0x30;}
  if(channel==3){channel= 0x31;}
  if(channel==4){channel= 0x32;}
  if(channel==5){channel= 0x33;}
  if(channel==6){channel= 0x34;}

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.write(servoposition);
  Wire1.endTransmission();
  delay(10);

}

void EXPANSION::setServoPositions (int address, int servoposition1,int servoposition2,int servoposition3,int servoposition4,int servoposition5,int servoposition6){  // Sets all EXPANSIONANSION servo positions at once

  Wire1.beginTransmission(address);
  Wire1.write(0x35);
  Wire1.write(servoposition1);
  Wire1.write(servoposition2);
  Wire1.write(servoposition3);
  Wire1.write(servoposition4);
  Wire1.write(servoposition5);
  Wire1.write(servoposition6);
  Wire1.endTransmission();
  delay(10);

}

void EXPANSION::setCRServoState (int address, int channel, int servospeed){   // function to set EXPANSIONANSION CR servos speed and direction -100|0|100

  if(channel==1){channel= 0x36;}   // CRservo 1
  if(channel==2){channel= 0x37;}   // CRservo 2

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.write(servospeed);
  Wire1.endTransmission();
  delay(10);

}

int EXPANSION::readServoPosition (int address, int channel){		// read the servo EXPANSIONANSION servo positions
  int readServoPosition;    // return value variable

  if(channel==1){channel= 0x38;}
  if(channel==2){channel= 0x39;}
  if(channel==3){channel= 0x3A;}
  if(channel==4){channel= 0x3B;}
  if(channel==5){channel= 0x3C;}
  if(channel==6){channel= 0x3D;}

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);
  Wire1.requestFrom(address, 1);
  readServoPosition = Wire1.read();
  delay(10);
  return readServoPosition;
}

// added a get
int EXPANSION::getServoPosition (int address, int channel){		// read the servo EXPANSIONANSION servo positions
  int readServoPosition;    // return value variable

  if(channel==1){channel= 0x38;}
  if(channel==2){channel= 0x39;}
  if(channel==3){channel= 0x3A;}
  if(channel==4){channel= 0x3B;}
  if(channel==5){channel= 0x3C;}
  if(channel==6){channel= 0x3D;}

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);
  Wire1.requestFrom(address, 1);
  readServoPosition = Wire1.read();
  delay(10);
  return readServoPosition;
}

void EXPANSION::setMotorPower(int address, int channel, int power){	// set Motor Channel power on DC EXPANSIONANSION

		if(channel==1){channel = 0x40;}   // DC channel 1
  	if(channel==2){channel = 0x41;}   // DC channel 2

  	Wire.beginTransmission(address);
  	Wire.write(channel);
  	Wire.write(power);
  	Wire.endTransmission();
	  delay(10);
}

void EXPANSION::setMotorPowers (int address, int power1, int power2){     //power only Block Command for EXPANSIONANSION Motor 1 and 2 (both in one transmission)

  Wire1.beginTransmission(address);
  Wire1.write(0x42);
  Wire1.write(power1);
  Wire1.write(power2);
  Wire1.endTransmission();
  delay(10);

}

void EXPANSION::setMotorSpeed (int address, int channel, long Mspeed){      // === set speed of each EXPANSIONANSION DC motor == requires a 1440 CPR installed encoder to do the PID

  int lobyte;
  int hibyte;

  lobyte  = lowByte(Mspeed);
  hibyte  = highByte(Mspeed);

  if(channel==1){channel= 0x43;}   // DC channel 1
  if(channel==2){channel= 0x44;}   // DC channel 2

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.write(hibyte);
  Wire1.write(lobyte);
  Wire1.endTransmission();
  delay(10);

}

void EXPANSION::setMotorSpeeds (int address, long Mspeed1, long Mspeed2){      // === BLOCK write to set speeds of both EXPANSIONANSION motors at once == 1440 CPR encoder must be installed to do PID

  int lobyte1;
  int hibyte1;

  int lobyte2;
  int hibyte2;

  lobyte1  = lowByte(Mspeed1);
  hibyte1  = highByte(Mspeed1);

  lobyte2  = lowByte(Mspeed2);
  hibyte2  = highByte(Mspeed2);

  Wire1.beginTransmission(address);
  Wire1.write(0x45);
  Wire1.write(hibyte1);
  Wire1.write(lobyte1);
  Wire1.write(hibyte2);
  Wire1.write(lobyte2);
  Wire1.endTransmission();
  delay(10);
}

void EXPANSION::setMotorTarget (int address, int channel, long Mspeed, long Mtarget){      // === set speed and encoder target of each EXPANSIONANSION DC motor == requires a 1440 CPR encoder to do the PID

  int lobyte;
  int hibyte;

  lobyte  = lowByte(Mspeed);
  hibyte  = highByte(Mspeed);

  byte four  = (Mtarget);
  byte three = (Mtarget>>8);
  byte two   = (Mtarget>>16);
  byte one   = (Mtarget>>24);

  if(channel==1){channel= 0x46;}   // DC channel 1
  if(channel==2){channel= 0x47;}   // DC channel 2

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.write(hibyte);
  Wire1.write(lobyte);
  Wire1.write(one);
  Wire1.write(two);
  Wire1.write(three);
  Wire1.write(four);
  Wire1.endTransmission();
  delay(10);

}

void EXPANSION::setMotorTargets (int address, long Mspeed1, long Mtarget1, long Mspeed2, long Mtarget2){      // === BLOCK WRITE set speed and encoder target of both EXPANSIONANSION DC motors == requires a 1440 CPR encoder to do the PID

  int lobyte1;
  int hibyte1;

  int lobyte2;
  int hibyte2;

  lobyte1  = lowByte(Mspeed1);
  hibyte1  = highByte(Mspeed1);

  lobyte2  = lowByte(Mspeed2);
  hibyte2  = highByte(Mspeed2);

  byte four1  = (Mtarget1);
  byte three1 = (Mtarget1>>8);
  byte two1   = (Mtarget1>>16);
  byte one1   = (Mtarget1>>24);

  byte four2  = (Mtarget2);
  byte three2 = (Mtarget2>>8);
  byte two2   = (Mtarget2>>16);
  byte one2   = (Mtarget2>>24);

  Wire1.beginTransmission(address);
  Wire1.write(0x48);
  Wire1.write(hibyte1);
  Wire1.write(lobyte1);
  Wire1.write(one1);
  Wire1.write(two1);
  Wire1.write(three1);
  Wire1.write(four1);
  Wire1.write(hibyte2);
  Wire1.write(lobyte2);
  Wire1.write(one2);
  Wire1.write(two2);
  Wire1.write(three2);
  Wire1.write(four2);
  Wire1.endTransmission();
  delay(10);

}

void EXPANSION::setMotorDegree (int address, int channel, long Mspeed, long Mdegrees){      // === set speed and encoder target of each EXPANSIONANSION DC motor in DEGREES  == requires a 1440 CPR encoder to do the PID

  int lobyte;
  int hibyte;

  lobyte  = lowByte(Mspeed);
  hibyte  = highByte(Mspeed);

  byte four  = (Mdegrees);
  byte three = (Mdegrees>>8);
  byte two   = (Mdegrees>>16);
  byte one   = (Mdegrees>>24);

  if(channel==1){channel= 0x58;}
  if(channel==2){channel= 0x59;}

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.write(hibyte);
  Wire1.write(lobyte);
  Wire1.write(one);
  Wire1.write(two);
  Wire1.write(three);
  Wire1.write(four);
  Wire1.endTransmission();
  delay(10);

}

void EXPANSION::setMotorDegrees (int address, long Mspeed1, long Mdegrees1, long Mspeed2, long Mdegrees2){      // === BLOCK WRITE set speed and encoder target in DEGREES of both EXPANSIONANSION DC motors == requires a 1440 CPR encoder to do the PID

  int lobyte1;
  int hibyte1;

  int lobyte2;
  int hibyte2;

  lobyte1  = lowByte(Mspeed1);
  hibyte1  = highByte(Mspeed1);

  lobyte2  = lowByte(Mspeed2);
  hibyte2  = highByte(Mspeed2);

  byte four1  = (Mdegrees1);
  byte three1 = (Mdegrees1>>8);
  byte two1   = (Mdegrees1>>16);
  byte one1   = (Mdegrees1>>24);

  byte four2  = (Mdegrees2);
  byte three2 = (Mdegrees2>>8);
  byte two2   = (Mdegrees2>>16);
  byte one2   = (Mdegrees2>>24);

  Wire1.beginTransmission(address);
  Wire1.write(0x5A);
  Wire1.write(hibyte1);
  Wire1.write(lobyte1);
  Wire1.write(one1);
  Wire1.write(two1);
  Wire1.write(three1);
  Wire1.write(four1);
  Wire1.write(hibyte2);
  Wire1.write(lobyte2);
  Wire1.write(one2);
  Wire1.write(two2);
  Wire1.write(three2);
  Wire1.write(four2);
  Wire1.endTransmission();
  delay(10);

}

long EXPANSION::readEncoderCount (int address, int channel){   // ============================= READ EXPANSIONANSION ENCODER DATA COUNTS ====================================
  unsigned long eCount;    // return value variable. We have to pass this an unsigned into Arduino.

  byte byte1;
  byte byte2;
  byte byte3;
  byte byte4;

  if(channel==1){channel= 0x49;}       // channel 1 encoder FOR count value
  if(channel==2){channel= 0x4A;}       // channel 2 encoder FOR count value

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(address, 4);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  byte3 = Wire1.read();
  byte4 = Wire1.read();

  eCount = byte1;
  eCount = (eCount*256)+byte2;
  eCount = (eCount*256)+byte3;
  eCount = (eCount*256)+byte4;
  delay(10);
  return eCount;
}

// added a get
long EXPANSION::getEncoderCount (int address, int channel){   // ============================= READ EXPANSIONANSION ENCODER DATA COUNTS ====================================
  unsigned long eCount;    // return value variable. We have to pass this an unsigned into Arduino.

  byte byte1;
  byte byte2;
  byte byte3;
  byte byte4;

  if(channel==1){channel= 0x49;}       // channel 1 encoder FOR count value
  if(channel==2){channel= 0x4A;}       // channel 2 encoder FOR count value

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(address, 4);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  byte3 = Wire1.read();
  byte4 = Wire1.read();

  eCount = byte1;
  eCount = (eCount*256)+byte2;
  eCount = (eCount*256)+byte3;
  eCount = (eCount*256)+byte4;
  delay(10);
  return eCount;
}

long EXPANSION::readEncoderDegrees (int address, int channel){   // ============================= READ EXPANSIONANSION ENCODER DATA DEGREES ====================================
  unsigned long eCount;    // return value variable. We have to pass this an unsigned into Arduino.

  byte byte1;
  byte byte2;
  byte byte3;
  byte byte4;

  if(channel==1){channel= 0x5B;}       // channel 1 encoder FOR degrees
  if(channel==2){channel= 0x5C;}       // channel 2 encoder FOR degrees

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(address, 4);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  byte3 = Wire1.read();
  byte4 = Wire1.read();

  eCount = byte1;
  eCount = (eCount*256)+byte2;
  eCount = (eCount*256)+byte3;
  eCount = (eCount*256)+byte4;
  delay(10);
  return eCount;
}

// added a get
long EXPANSION::getEncoderDegrees (int address, int channel){   // ============================= READ EXPANSIONANSION ENCODER DATA DEGREES ====================================
  unsigned long eCount;    // return value variable. We have to pass this an unsigned into Arduino.

  byte byte1;
  byte byte2;
  byte byte3;
  byte byte4;

  if(channel==1){channel= 0x5B;}       // channel 1 encoder FOR degrees
  if(channel==2){channel= 0x5C;}       // channel 2 encoder FOR degrees

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(address, 4);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  byte3 = Wire1.read();
  byte4 = Wire1.read();

  eCount = byte1;
  eCount = (eCount*256)+byte2;
  eCount = (eCount*256)+byte3;
  eCount = (eCount*256)+byte4;
  delay(10);
  return eCount;
}

void EXPANSION::resetEncoder (int address, int channel){    // =================== RESET EXPANSIONANSION ENCODERS 1 or 2 =============================

  if(channel==1){channel= 0x4C;}       // channel 1 encoder reset command
  if(channel==2){channel= 0x4D;}       // channel 2 encoder reset command

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

}

void EXPANSION::resetEncoders(int address){			// ================== Reset BOTH EXPANSIONANSION Encoders at once =========================

  Wire1.beginTransmission(address);
  Wire1.write(0x4E);
  Wire1.endTransmission();
  delay(10);

}

int EXPANSION::readMotorBusy (int address, int channel){			// ================== Read Busy Status of EXPANSIONANSION DC motor channel =======================
  int byte1;
  int MotorStatus;

  if(channel==1){channel= 0x4F;}       // channel 1 busy flag
  if(channel==2){channel= 0x50;}       // channel 2 busy flag

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(address, 1);
  byte1 = Wire1.read();
  MotorStatus=byte1;
  delay(10);

  return MotorStatus;
}

// added a get
int EXPANSION::getMotorBusy (int address, int channel){			// ================== Read Busy Status of EXPANSIONANSION DC motor channel =======================
  int byte1;
  int MotorStatus;

  if(channel==1){channel= 0x4F;}       // channel 1 busy flag
  if(channel==2){channel= 0x50;}       // channel 2 busy flag

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(address, 1);
  byte1 = Wire1.read();
  MotorStatus=byte1;
  delay(10);

  return MotorStatus;
}

int EXPANSION::readMotorCurrent (int address, int channel){		// ================ Read DC motor current of EXPANSIONANSION DC channels ======================
  int Mcurrent;

  byte byte1;
  byte byte2;

  if(channel==1){channel= 0x54;}       // read DC motor 1 current
  if(channel==2){channel= 0x55;}       // read DC motor 2 current

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(address, 2);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  Mcurrent = byte1;
  Mcurrent = (Mcurrent*256)+byte2;
  delay(10);
  return (Mcurrent);     // return Mcurrent in milliamps
}

// added a get
int EXPANSION::getMotorCurrent (int address, int channel){		// ================ Read DC motor current of EXPANSIONANSION DC channels ======================
  int Mcurrent;

  byte byte1;
  byte byte2;

  if(channel==1){channel= 0x54;}       // read DC motor 1 current
  if(channel==2){channel= 0x55;}       // read DC motor 2 current

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(address, 2);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  Mcurrent = byte1;
  Mcurrent = (Mcurrent*256)+byte2;
  delay(10);
  return (Mcurrent);     // return Mcurrent in milliamps
}

void EXPANSION::setMotorInvert (int address, int channel, int invert){			// ======================== Set the EXPANSIONANSION DC Motor Direction invert status ====================

  if(channel==1){channel= 0x51;}       // channel 1
  if(channel==2){channel= 0x52;}       // channel 2

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.write(invert);
  Wire1.endTransmission();
  delay(10);

}
