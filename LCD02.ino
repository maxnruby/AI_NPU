#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  tft.begin();
  tft.setRotation(3); // 가로 160, 세로 80 모드로 설정
  tft.fillScreen(TFT_DARKGREY); 
}

void loop() {
  // ==========================================
  // 1. 미소 짓는 미니 이모지 (🙂)
  // ==========================================
  tft.fillScreen(TFT_DARKGREY); // 화면 지우기
  
  // 얼굴 (중심 X:80, Y:40, 반지름:30, 색상:노란색)
  tft.fillCircle(80, 40, 30, TFT_YELLOW);
  
  // 왼쪽 눈, 오른쪽 눈 (검은색 미니 원)
  tft.fillCircle(70, 32, 3, TFT_BLACK);
  tft.fillCircle(90, 32, 3, TFT_BLACK);
  
  // 미소 짓는 입 (작은 원을 겹쳐서 반원 만들기)
  tft.fillCircle(80, 48, 10, TFT_BLACK);
  tft.fillCircle(80, 45, 10, TFT_YELLOW); 
  
  // 상단 미니 텍스트 안내 (폰트 크기 1로 축소)
  tft.setCursor(5, 5);
  tft.setTextFont(1);
  tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
  tft.print("HAPPY");
  
  delay(2000); // 2초 유지


  // ==========================================
  // 2. 윙크하는 미니 이모지 (😉)
  // ==========================================
  tft.fillScreen(TFT_DARKGREY); // 화면 지우기
  
  // 얼굴
  tft.fillCircle(80, 40, 30, TFT_YELLOW);
  
  // 왼쪽 눈 (동그란 눈)
  tft.fillCircle(70, 32, 3, TFT_BLACK);
  
  // 오른쪽 눈 (윙크 - 가로 짧은 선)
  tft.drawFastHLine(85, 32, 10, TFT_BLACK);
  tft.drawFastHLine(85, 33, 10, TFT_BLACK); // 두께감을 위해 한 줄 더
  
  // 미소 짓는 입
  tft.fillCircle(80, 48, 10, TFT_BLACK);
  tft.fillCircle(80, 45, 10, TFT_YELLOW);
  
  // 상단 미니 텍스트 안내
  tft.setCursor(5, 5);
  tft.setTextFont(1);
  tft.setTextColor(TFT_CYAN, TFT_DARKGREY);
  tft.print("WINK");
  
  delay(2000); // 2초 유지
}