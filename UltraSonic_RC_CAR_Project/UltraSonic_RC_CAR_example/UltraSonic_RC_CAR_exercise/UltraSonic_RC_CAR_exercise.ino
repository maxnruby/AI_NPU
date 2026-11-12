#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

const int dcMotors[] = {25,26,12,27,16,17,22,21};
const int forward[] = {HIGH,LOW};
const int backward[] = {LOW,HIGH};
const int stop[] = {LOW,LOW};

void initMotor() {
  for(int i=0;i<sizeof(dcMotors)/sizeof(dcMotors[0]);i++)
    pinMode(dcMotors[i], OUTPUT);
}

void goForward() {
    for(int i=0;i<sizeof(dcMotors)/sizeof(dcMotors[0]);i++) 
      digitalWrite(dcMotors[i], forward[i%2]); 
}

void goBackward() {
    for(int i=0;i<sizeof(dcMotors)/sizeof(dcMotors[0]);i++) 
      digitalWrite(dcMotors[i], backward[i%2]);
}

void turnLeft() {
    for(int i=0;i<4;i++) 
      digitalWrite(dcMotors[i], backward[i%2]);        
    for(int i=4;i<8;i++) 
      digitalWrite(dcMotors[i], forward[i%2]); 
}

void turnRight() {
    for(int i=0;i<4;i++) 
      digitalWrite(dcMotors[i], forward[i%2]);        
    for(int i=4;i<8;i++) 
      digitalWrite(dcMotors[i], backward[i%2]); 
}

void stopMotor() {
  for(int i=0;i<sizeof(dcMotors)/sizeof(dcMotors[0]);i++) 
      digitalWrite(dcMotors[i], stop[i%2]);
}

int trigPins[] = {13, 14};
int echoPins[] = {34, 35};

void initHCSR04() {
  for(int i=0;i<sizeof(trigPins)/sizeof(trigPins[0]);i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);  
  }
}

void getDistanceCM(int &left, int &right) {   // 초음파 센서 거리 측정 함수(단위:cm)
  int distanceCM[2] = {0,};
  
  for(int i=0;i<sizeof(trigPins)/sizeof(trigPins[0]);i++) {
    digitalWrite(trigPins[i], LOW);
    delayMicroseconds(2);  
    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);

    long duration = pulseIn(echoPins[i], HIGH);
    distanceCM[i] = duration/58;  
  }

  right = distanceCM[0];
  left = distanceCM[1];
}

const int SAFEDISTANCE = 30;

void setup() { 
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // brown-out reset disable
  
  Serial.begin(115200);
  initMotor();
  initHCSR04();
}

const int SAMPLE_COUNT = 300;

void loop() {
  for(int i=0;i<SAMPLE_COUNT;i++) {
    int left = 0, right =0;
    getDistanceCM(left, right);

    Serial.print("right: ");
    Serial.print(right);
    Serial.print("left: ");
    Serial.print(left);
    Serial.println();

    if(left<SAFEDISTANCE||right<SAFEDISTANCE){
      if(left>right) {
        turnLeft();
      } else {
        turnRight();
      }
      delay(500);
    } else {
      goForward();
      delay(100);
    }

  }

stopMotor();
for(;;);
}
