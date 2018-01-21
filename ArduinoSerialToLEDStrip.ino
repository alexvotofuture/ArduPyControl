
#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
#define NUMPIXELS 60 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    5
#define CLOCKPIN   6

Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN);
const int potPin = 5;
int potVal = 0;
int mapPotVal = 0;
int serialMessage = 0;

void setup() {
  Serial.begin(9600);
  pinMode(potPin, INPUT_PULLUP);
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

//int      head  = 0, tail = -30; // Index of first 'on' and 'off' pixels
//uint32_t color = 0x000000;      // 'On' color (starts red)

void loop() {
 if (Serial.available() > 0) {
  serialMessage = (Serial.read(), DEC);
 }
  int r=random(0,255);
  int g=random(0,255);
  int b=random(0,255);
  potVal = analogRead(potPin);
  mapPotVal = map(potVal, 0, 1023, 0, 59);
  selectWipe(strip.Color(r, g, b), serialMessage, 5); //Uncomment this to make the led count respond to a serial message sent from Python
//  selectWipe(strip.Color(r, g, b), mapPotVal, 5); //Uncomment this to make the led count respond to the potentiometer
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
