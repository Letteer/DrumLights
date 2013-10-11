/* Knock Sensor
  
   This sketch reads a piezo element to detect a knocking sound. 
   It reads an analog pin and compares the result to a set threshold. 
   If the result is greater than the threshold, it writes
   "knock" to the serial port, and toggles the LED on pin 13.
  
   The circuit:
    * + connection of the piezo attached to analog in 0
    * - connection of the piezo attached to ground
    * 1-megohm resistor attached from analog in 0 to ground

   http://www.arduino.cc/en/Tutorial/Knock
   
   created 25 Mar 2007
   by David Cuartielles <http://www.0j0.org>
   modified 30 Aug 2011
   by Tom Igoe
   
   This example code is in the public domain.

 */
 
#include <Adafruit_NeoPixel.h>

const int ledPin = 6;      // led connected to digital pin 13
const int knockSensor = A0; // the piezo is connected to analog pin 0
const int threshold = 10;  // threshold value to decide when the detected sound is a knock or not
int sensorReading = 0;      // variable to store the value read from the sensor pin
int ledState = LOW;         // variable used to store the last LED status, to toggle the light

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  //pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  Serial.begin(9600);
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
  //rainbow(20);
  //rainbowCycle(20);
  
  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(knockSensor);    
  
  // if the sensor reading is greater than the threshold:
  if (sensorReading >= threshold) {
    if (ledState) {
      colorWipe(strip.Color(255, 0, 0), 50); // Red
    } else {
      strip.show();
    }
    ledState = !ledState;  
  }
  delay(100);  // delay to avoid overloading the serial port buffer
}

//// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

//void rainbow(uint8_t wait) {
//  uint16_t i, j;
//
//  for(j=0; j<256; j++) {
//    for(i=0; i<strip.numPixels(); i++) {
//      strip.setPixelColor(i, Wheel((i+j) & 255));
//    }
//    strip.show();
//    delay(wait);
//  }
//}

// Slightly different, this makes the rainbow equally distributed throughout
//void rainbowCycle(uint8_t wait) {
//  uint16_t i, j;
//
//  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
//    for(i=0; i< strip.numPixels(); i++) {
//      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
//    }
//    strip.show();
//    delay(wait);
//  }
//}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
//uint32_t Wheel(byte WheelPos) {
//  if(WheelPos < 85) {
//   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//  } else if(WheelPos < 170) {
//   WheelPos -= 85;
//   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//  } else {
//   WheelPos -= 170;
//   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//  }
//}

