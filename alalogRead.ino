int cds = 39;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println(analogRead(cds));
    delay(100);
}
