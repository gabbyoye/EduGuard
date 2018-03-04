
/*Cody Clemons
HackFSU
3-3-2018*/
#include <Adafruit_NeoPixel.h>

#define PIN            6

#define NUMPIXELS      16
#define LOCK           7

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  pinMode(LOCK,OUTPUT);
  digitalWrite(LOCK, HIGH);

}

void loop() {
  for (int i = NUMPIXELS; i >= 0; i--) {
      pixels.setPixelColor(i, pixels.Color(100, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    
  bool auth=1;
  if (auth) {
    digitalWrite(LOCK,LOW);
    for (int i = NUMPIXELS; i >= 0; i--) {
      pixels.setPixelColor(i, pixels.Color(0 , 75, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(30); // Delay for a period of time (in milliseconds).
    }
    delay(3000);
    for (int i = NUMPIXELS; i >= 0; i--) {
      pixels.setPixelColor(i, pixels.Color(0 , 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    digitalWrite(LOCK,HIGH);
    while(true){}
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  }
  else if (!auth){
    for (int i = 0; i < 2; i++) {
      for (int i = NUMPIXELS; i >= 0; i--) {
        pixels.setPixelColor(i, pixels.Color(100 , 0, 0)); // Moderately bright green color.
         // This sends the updated pixel color to the hardware.
      }
      pixels.show();
      delay(375);
      for (int i = NUMPIXELS; i >= 0; i--) {
        pixels.setPixelColor(i, pixels.Color(0 , 0, 0)); // Moderately bright green color.
         // This sends the updated pixel color to the hardware.
      }
      pixels.show();
      delay(250);
    }
    while(true){}
  }
  


}

