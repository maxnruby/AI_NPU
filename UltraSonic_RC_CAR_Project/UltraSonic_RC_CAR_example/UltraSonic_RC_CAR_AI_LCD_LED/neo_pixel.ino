#include <Adafruit_NeoPixel.h>

#define PIN       0
#define NUMPIXELS 4 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t BLACK = pixels.Color(0, 0, 0);
uint32_t RED = pixels.Color(255, 0, 0);
uint32_t YELLOW = pixels.Color(255, 150, 0);
uint32_t GREEN = pixels.Color(0, 255, 0);
uint32_t CYAN = pixels.Color(0, 255, 255);
uint32_t BLUE = pixels.Color(0, 0, 255);
uint32_t PURPLE = pixels.Color(180, 0, 255);
uint32_t WHITE = pixels.Color(255, 255, 255);
uint32_t COLORS[] = {BLACK, RED, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE};

uint32_t wheel(int pos) {
  //Input a value 0 to 255 to get a color value.
  //The colours are a transition r - g - b - back to r.
  if(pos < 0 || pos > 255) {
    return pixels.Color(0, 0, 0);
  } else if(pos < 85) {
    return pixels.Color(255 - pos * 3, pos * 3, 0);
  } else if(pos < 170) {
    pos -= 85;
    return pixels.Color(0, 255 - pos * 3, pos * 3);
  } else {
    pos -= 170;
    return pixels.Color(pos * 3, 0, 255 - pos * 3);
  }
}

void rainbow_cycle(int wait) {
  int NUM_LEDS = pixels.numPixels();

  for(int j=0;j<255;j++) {
    for(int i=0;i<NUM_LEDS;i++) {
      int rc_index = (i*256.0/NUM_LEDS)+j;
      pixels.setPixelColor(i, wheel(rc_index&255));
    }
    pixels.show();
    delay(wait);
  }

  pixels.clear();
  pixels.show();
}

void neopixel_setup() {
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(255/100.0*20);

  rainbow_cycle(10);
}

void neopixelMain(void * arg) {
  neopixel_setup();

  for(;;) rainbow_cycle(10);
}
