int trigPin = 14;
int echoPin = 35;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    
    int distance= duration / 58;

    Serial.print("Distance: ");
    Serial.println(distance);
 }

