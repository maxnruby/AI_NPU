double x1 = 0.02, x2 = 0.05, x3 = 0.12;
double w1 = 0.15, w2 = 0.20, w3 = 0.02;
double w4 = 0.27, w5 = 0.37, w6 = 0.52;
double b1 = 0.12, b2 = 0.39;
double y1T = 0.02, y2T = 0.98;
double lr = 0.01;

void setup() {

            Serial.begin(115200);

            for(int epoch=0;epoch<2000;epoch++) {
            double y1 = x1*w1 + x2*w2 + x3*w3 + 1*b1;
            double y2 = x1*w4 + x2*w5 + x3*w6+ 1*b2;
            double E = (y1-y1T)*(y1-y1T)/2 + (y2-y2T)*(y2-y2T)/2;
            double y1E = y1 - y1T;
            double y2E = y2 - y2T;
            double w1E = y1E*x1;
            double w2E = y1E*x2;
            double w3E = y1E*x3;
            double b1E = y1E*1;
            double w4E = y2E*x1;
            double w5E = y2E*x2;
            double w6E = y2E*x3;
            double b2E = y2E*1;
            w1 -= lr*w1E;
            w2 -= lr*w2E;
            w3 -= lr*w3E;
            b1 -= lr*b1E;
            w4 -= lr*w4E;
            w5 -= lr*w5E;
            w6 -= lr*w6E;
            b2 -= lr*b2E;
           
            Serial.print("epoch = "); Serial.println(epoch);
            Serial.print(" y1 : "); Serial.println(y1, 3);
            Serial.print(" y2 : "); Serial.println(y2, 3);
            Serial.print(" w1 : "); Serial.println(w1, 3); 
            Serial.print(" w2 : "); Serial.println(w2, 3);
            Serial.print(" w3 : "); Serial.println(w3, 3);
            Serial.print(" b1 : "); Serial.println(b1, 3);
            Serial.print(" w4 : "); Serial.println(w4, 3); 
            Serial.print(" w5 : "); Serial.println(w5, 3);
            Serial.print(" w6 : "); Serial.println(w6, 3);
            Serial.print(" b2 : "); Serial.println(b2, 3);
                    
           
            if(E< 0.0000001) break;
      }
  }
void loop() {
}