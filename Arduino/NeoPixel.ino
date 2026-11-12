 #include <Adafruit_NeoPixel.h>

 #define PIN 0       
 #define NUMPIXELS 4

Adafruit_NeoPixel pixels(NUMPIXELS, PIN);

void setup() {
  // put your setup code here, to run once:
    pixels.begin();
    pixels.clear();
    pixels.setBrightness(255/100.0*20);

    for(int cnt=0;cnt<5;cnt++) {
         pixels.setPixelColor(0, pixels.Color(255, 0, 0));
         pixels.show();
        delay(500);

        pixels.setPixelColor(0, pixels.Color(0, 255, 0));
        pixels.show();
        delay(500);
    }
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
}

void loop() {
  // put your main code here, to run repeatedly:
}
