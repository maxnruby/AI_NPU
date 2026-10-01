#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  tft.begin();
  tft.setRotation(3); // 가로 160, 세로 80 모드
  
  tft.invertDisplay(false); 

  tft.fillScreen(TFT_DARKGREY); 
}

void loop() {
  // ==========================================
  // 1. 미소 짓는 미니 이모지 (🙂)
  // ==========================================
  tft.fillScreen(TFT_DARKGREY); 
  
  // 얼굴 (원래 노란색 출력)
  tft.fillCircle(80, 40, 30, TFT_YELLOW);
  
  // 눈 (검은색)
  tft.fillCircle(70, 32, 3, TFT_BLACK);
  tft.fillCircle(90, 32, 3, TFT_BLACK);
  
  // 입 (반원 만들기)
  tft.fillCircle(80, 48, 10, TFT_BLACK);
  tft.fillCircle(80, 45, 10, TFT_YELLOW); 
  
  // 텍스트 안내
  tft.setCursor(5, 5);
  tft.setTextFont(1);
  tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
  tft.print("HAPPY");
  
  delay(2000); 

  // ==========================================
  // 2. 윙크하는 미니 이모지 (😉)
  // ==========================================
  tft.fillScreen(TFT_DARKGREY); 
  
  // 얼굴
  tft.fillCircle(80, 40, 30, TFT_YELLOW);
  
  // 왼쪽 눈
  tft.fillCircle(70, 32, 3, TFT_BLACK);
  
  // 오른쪽 눈 (윙크 가로선)
  tft.drawFastHLine(85, 32, 10, TFT_BLACK);
  tft.drawFastHLine(85, 33, 10, TFT_BLACK); 
  
  // 입
  tft.fillCircle(80, 48, 10, TFT_BLACK);
  tft.fillCircle(80, 45, 10, TFT_YELLOW);
  
  // 텍스트 안내
  tft.setCursor(5, 5);
  tft.setTextFont(1);
  tft.setTextColor(TFT_CYAN, TFT_DARKGREY); 
  tft.print("WINK");
  
  delay(2000); 
}