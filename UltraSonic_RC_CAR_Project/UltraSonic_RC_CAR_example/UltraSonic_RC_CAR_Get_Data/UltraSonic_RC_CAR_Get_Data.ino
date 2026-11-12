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
    distanceCM[i] = 100;//duration/58;  
  }

  right = distanceCM[0];
  left = distanceCM[1];
}

const int SAFEDISTANCE = 20;

void setup() { 
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // brown-out reset disable
  
  Serial.begin(115200);
  initMotor();
  initHCSR04();
}

const int SAMPLE_COUNT = 1000;
const int INPUT_NODES = 2;
const int OUTPUT_NODES = 3;

long input[SAMPLE_COUNT][INPUT_NODES] = {0,};
long target[SAMPLE_COUNT][OUTPUT_NODES] = {0,};

void loop() {
  for(int i=0;i<SAMPLE_COUNT;i++) {
    int left = 0, right = 0;
    getDistanceCM(left, right);
    input[i][0] = left;
    input[i][1] = right;

    Serial.print(i);
    Serial.print("right: ");
    Serial.print(right);
    Serial.print(" left: ");
    Serial.print(left);
    Serial.print(", ");
  
    if(left<SAFEDISTANCE||right<SAFEDISTANCE) {
      if(left>right) {
        Serial.println("turn left");
        target[i][0] = 1;
        turnLeft();
      } else {
        Serial.println("turn right");
        target[i][2] = 1;
        turnRight();
      }
      delay(500);
    } else {
      Serial.println("go forward");
      target[i][1] = 1;
      goForward();
      delay(100);
    }
  }
  
  stopMotor();
  for(;;) {
    if(Serial.available()>0) {
      char userInput = Serial.read();
      if(userInput == 'p') {
         // python code
         printf("# python data\n\n");
         printf("import numpy as np\n\n");
         printf("I = np.array([\n");
         int i;
         for(i=0;i<SAMPLE_COUNT-1;i++) {
          printf("\t[[%d,%d]],\n", input[i][0], input[i][1]);
         }         
         printf("\t[[%d,%d]]\n", input[i][0], input[i][1]);
         printf("])\n");
         
         printf("T = np.array([\n");
         for(i=0;i<SAMPLE_COUNT-1;i++) {
          printf("\t[[%d,%d,%d]],\n", target[i][0], target[i][1], target[i][2]);
         }         
         printf("\t[[%d,%d,%d]]\n", target[i][0], target[i][1], target[i][2]);
         printf("])\n");
      } else if(userInput == 'c') {   
         // arduino code
         printf("// c/c++ data\n\n");
         printf("double I[][2] = {\n");
         int i;
         for(i=0;i<SAMPLE_COUNT-1;i++) {
          printf("\t{%d,%d},\n", input[i][0], input[i][1]);
         }         
         printf("\t{%d,%d}\n", input[i][0], input[i][1]);
         printf("};\n");
      }
    }
  }
}
