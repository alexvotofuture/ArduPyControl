#include <Adafruit_DotStar.h>
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET

// Here's how to control the LEDs from any two pins:
#define DATAPIN    5
#define CLOCKPIN   6
#define NUMPIXELS 60 // Number of LEDs in strip

Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN);
int serialMessage = 0;
int temporaryIncrement = 1;

void setup() {
  Serial.begin(115200);
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

void loop() {
 if (Serial.available() > 0) {
  serialMessage = (Serial.read(),DEC);
  Serial.print(serialMessage);
 }
  int r=random(0,255);
  int g=random(0,255);
  int b=random(0,255);
  selectWipe(strip.Color(r, g, b), serialMessage, 5); //Uncomment this to make the led count respond to a serial message sent from Python
}

void selectWipe(uint32_t c, int pixelLength, int wait) { //converts mapPotVal to pixelLength
  for(uint16_t i=0; i<pixelLength; i++) {
      strip.setPixelColor(i, c);
      strip.show();
  }
  for(uint16_t i=pixelLength; i<strip.numPixels(); i++){
    strip.setPixelColor(i, 0x000000); //make all black
    strip.show();
  }
  delay(wait);
}
