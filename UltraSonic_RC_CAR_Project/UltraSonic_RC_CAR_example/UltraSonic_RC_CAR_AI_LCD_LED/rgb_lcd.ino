#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void lcd_setup() {
  
  tft.begin();
  tft.setRotation(3);

  tft.fillScreen(TFT_BLACK);

  tft.setCursor(0, 10);
  tft.setTextFont(4);
  tft.setTextColor(TFT_RED);
  tft.setTextSize(1);
  tft.println("AI Car");

  tft.setTextFont(4);
  tft.setTextColor(TFT_YELLOW);
  tft.println("I'm World");
  
}
