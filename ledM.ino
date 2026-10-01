int led_pin = 2;
int led_freq = 100;
int led_resolution = 10;

void setup() {
  // put your setup code here, to run once:
ledcAttach(led_pin, led_freq,led_resolution);
ledcWrite(led_pin, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int t_high=0;t_high<=1024;t_high++) {
    ledcWrite(led_pin, t_high);
    delay(1);
  }
}
