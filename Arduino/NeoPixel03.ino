
#include <Adafruit_NeoPixel.h>

#define PIN 0       
#define NUMPIXELS 4

Adafruit_NeoPixel pixels(NUMPIXELS, PIN);

// 제어할 색상들을 미리 배열로 정의 (빨강, 초록, 파랑, 노랑)
uint32_t colors[4];

void setup() {
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(255 / 100.0 * 20);

  // 사용할 색상 데이터 채워 넣기
  colors[0] = pixels.Color(255, 0, 0);   // 0번: 빨강
  colors[1] = pixels.Color(0, 255, 0);   // 1번: 초록
  colors[2] = pixels.Color(0, 0, 255);   // 2번: 파랑
  colors[3] = pixels.Color(255, 255, 0); // 3번: 노랑
}

void loop() {
  // 1. 0.3초 간격으로 LED가 하나씩 차례대로 켜짐
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, colors[i]); // i번째 LED에 i번째 색상 지정
    pixels.show();
    delay(300); // 다음 LED가 켜질 때까지 대기
  }

  // 4개가 다 켜진 상태로 1초간 유지
  delay(1000);

  // 2. 전체 LED를 동시에 끄기
  pixels.clear();
  pixels.show();

  // 꺼진 상태로 1초간 유지 후 다시 loop의 처음으로 이동
  delay(1000);
}