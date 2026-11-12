#include <math.h>

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);

    Serial.println(exp(1.3));
    Serial.println(exp(5.1));
    Serial.println(exp(2.2));
    Serial.println(exp(0.7));
    Serial.println(exp(1.1));

    double sumY = exp(1.3)+exp(5.1)+exp(2.2)+exp(0.7)+exp(1.1);
    Serial.println(sumY);

    Serial.println(exp(1.3)/sumY);
     Serial.println(exp(5.1)/sumY);
    Serial.println(exp(2.2)/sumY);
    Serial.println(exp(0.7)/sumY);
    Serial.println(exp(1.1)/sumY);
}

void loop() {
  // put your main code here, to run repeatedly:

}
