
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
int pyCommand = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Connection Initialized");
  pinMode(potPin, INPUT_PULLUP);
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

void loop() {
  if(Serial.available() > 0) {
    char commandArray[Serial.available()+1];
    for(int i; i<Serial.available(); i++){ 
      commandArray[i] = Serial.read();
    }
    commandArray[Serial.available()+1] = '/0';
    Serial.print("Received command: "); Serial.println(commandArray);
  }
 /* 
//  potVal = analogRead(potPin);
//  mapPotVal = map(potVal, 0, 1023, 0, 59);
  selectWipe(pyCommand); //Uncomment this to make the led count respond to a serial message sent from Python
//  selectWipe(mapPotVal); //Uncomment this to make the led count respond to the potentiometer
*/
}

void selectWipe(char pixelLength) { //converts mapPotVal to pixelLength
  int r=random(0,255);
  int g=random(0,255);
  int b=random(0,255);
  uint32_t c = strip.Color(r, g, b);
  for(uint16_t i=0; i<pixelLength; i++) {
      strip.setPixelColor(i, c);
      strip.show();
  }
  for(uint16_t i=pixelLength; i<strip.numPixels(); i++){ //for all remaining, unlit pixels...
    strip.setPixelColor(i, 0x000000); //set remaining unlit pixels to the color black
    strip.show();
  }
}
