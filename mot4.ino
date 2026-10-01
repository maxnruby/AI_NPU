int mot[4] = {25,12,17,21};
int freq = 1;
int res = 10;

void setup() {
  // put your setup code here, to run once:
  for(int i=0; i<4; i++) {
    ledcAttach(mot[i], freq, res);
  }
  for(int i=0; i<4; i++) {
    ledcWrite(mot[i],100);
  }
   delay(5000);
  for(int i=0; i<4; i++) {
    ledcWrite(mot[i],0);
  }
}

  
void loop() {
  // put your main code here, to run repeatedly:
 }