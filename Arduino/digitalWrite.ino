int LED = 2;
int MOT = 25;

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(MOT, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);
  digitalWrite(MOT, HIGH);
  delay(5);
  digitalWrite(LED, LOW);
  digitalWrite(MOT, LOW);
  delay(5);
}