#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "model.h"

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

void setup() {  
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // brown-out reset disable
  
  Serial.begin(115200);
  initMotor();
  initHCSR04();
}

const int SAMPLE_COUNT = 500;

void loop() {
  for(int i=0;i<SAMPLE_COUNT;i++) {
  
    int left = 0, right = 0;
    getDistanceCM(left, right);
    
    Serial.print("right: ");
    Serial.print(right);
    Serial.print(" left: ");
    Serial.print(left);    
    Serial.println();
  
    double I[] = {left/250.0, right/250.0};
    double P[3] = {};
  
    predict(I, P);  
  
    printf("%.4f, %.4f, %.4f\n", P[0], P[1], P[2]);
  
    if(P[0]>P[1] && P[0]>P[2]) { // if(round(P[0])==1) {  
      turnLeft();
      delay(500);
    } else if(P[2]>P[1]) { // else if(round(P[2])==1) {
      turnRight();
      delay(500);
    } else {
      goForward();
      delay(100);
    }
  }
  
  stopMotor();
  for(;;) ;

}
