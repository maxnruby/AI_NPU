#include <SPI.h>
#include <TFT_eSPI.h>

 TFT_eSPI tft = TFT_eSPI();

void setup() {
  // put your setup code here, to run once:
    tft.begin();
    tft.setRotation(3);

    tft.fillScreen(TFT_DARKGREY);

    tft.setCursor(0, 10);
    tft.setTextFont(2);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.setTextSize(1);
    tft.println("Hello World!");

    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW);
    tft.println(1234.56);

}

void loop() {
  // put your main code here, to run repeatedly:

}
