double x1 = 0.05, x2 = 0.10;
double w1 = 0.15, w2 = 0.20;
double w3 = 0.25, w4 = 0.30;
double b1 = 0.35, b2 = 0.35;
double w5 = 0.40, w6 = 0.45;
double w7 = 0.50, w8 = 0.55;
double b3 = 0.60, b4 = 0.60;
double y1T = 0.01, y2T = 0.99;
double lr = 0.01;
void setup() {
    Serial.begin(115200);

    for(int epoch=0;epoch<1000;epoch++) {
        double h1 = x1*w1 + x2*w2 + 1*b1;
        double h2 = x1*w3 + x2*w4 + 1*b2;
        // RELU feed forward
        h1=(h1>0)?h1:0;
        h2=(h2>0)?h2:0;

        double y1 = h1*w5 + h2*w6 + 1*b3;
        double y2 = h1*w7 + h2*w8 + 1*b4;
        // sigmoid feed forward
        y1=1/(1+exp(-y1));
        y2=1/(1+exp(-y2));
        double E = ((y1-y1T)*(y1-y1T) + (y2-y2T)*(y2-y2T))/2;
                double y1E = y1 - y1T;
        double y2E = y2 - y2T;
        // sigmoid back propagation
        y1E=y1*(1-y1)*y1E;
        y2E=y2*(1-y2)*y2E;
        double w5E = y1E*h1;
        double w6E = y1E*h2;
        double w7E = y2E*h1;
        double w8E = y2E*h2;
        double b3E = y1E*1;
        double b4E = y2E*1;
        double h1E = y1E*w5 + y2E*w7;
        double h2E = y1E*w6 + y2E*w8;
        // RELU back propagation
        h1E=(h1>0)?h1E:0;
        h2E=(h2>0)?h2E:0;
        double w1E = h1E*x1;
        double w2E = h1E*x2;
        double w3E = h2E*x1;
        double w4E = h2E*x2;
        double b1E = h1E*1;
        double b2E = h2E*1;
        w5 -= lr*w5E;
        w6 -= lr*w6E;
        w7 -= lr*w7E;
        w8 -= lr*w8E;
        b3 -= lr*b3E;
        b4 -= lr*b4E;
        w1 -= lr*w1E;
        w2 -= lr*w2E;
        w3 -= lr*w3E;
        w4 -= lr*w4E;
        b1 -= lr*b1E;
        b2 -= lr*b2E;
        
        Serial.print("epoch = "); Serial.println(epoch);
        Serial.print("y1 : "); Serial.println(y1, 3);
        Serial.print("y2 : "); Serial.println(y2, 3);
        if(E<0.0000001) break;
    }
}
void loop() {
}
