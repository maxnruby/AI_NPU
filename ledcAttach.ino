 int led_pin = 2;
 int mot_pin=25;
 int led_freq=10; //10,100,1000
 int led_resolution=10;

void setup() {
  // put your setup code here, to run once:
    ledcAttach(led_pin, led_freq,led_resolution);
    ledcAttach(mot_pin, led_freq,led_resolution);
    ledcWrite(led_pin, 100);
    ledcWrite(mot_pin, 100);
}

void loop() {
  // put your main code here, to run repeatedly:
}
