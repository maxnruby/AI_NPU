int dcMotors[] = {25,26,12,27,16,17,22,21};
int forward[] = {HIGH,LOW};
int backward[] = {LOW,HIGH};
int stop[] = {HIGH,HIGH};

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<sizeof(dcMotors)/sizeof(dcMotors[0]);i++)
      pinMode(dcMotors[i], OUTPUT);

  for(int cnt=0;cnt<5;cnt++) {
        for(int i=0;i<sizeof(dcMotors)/sizeof(dcMotors[0]);i++)
            digitalWrite(dcMotors[i], forward[i%2]);

        delay(500);

          for(int i=0;i<sizeof(dcMotors)/sizeof(dcMotors[0]);i++)
              digitalWrite(dcMotors[i], backward[i%2]);
        delay(500);
  }
  for(int i=0;i<sizeof(dcMotors)/sizeof(dcMotors[0]);i++)
      digitalWrite(dcMotors[i], stop[i%2]);
 
}

void loop() {
  // put your main code here, to run repeatedly:

}
