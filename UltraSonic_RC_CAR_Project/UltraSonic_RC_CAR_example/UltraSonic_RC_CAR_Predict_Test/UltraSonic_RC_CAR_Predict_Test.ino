#include "model.h"
#include "mydata.h"

void setup() {
  
  Serial.begin(115200);
  
  double P[3];
  
  for(int n=0;n<SIZE_I;n++) {
    I[n][0] /= 250.0;
    I[n][1] /= 250.0;

    predict(I[n], P);
    if(n>=976)
      printf("%.4f, %.4f, %.4f\n", P[0], P[1], P[2]);
  }
  
}

void loop() {
  
}
