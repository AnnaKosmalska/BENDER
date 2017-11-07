

int a_pin = A0;
int pwm_pin = 9;

void setup() {
  //put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  int potenc = analogRead(a_pin);

  int led = map(potenc, 0, 1023, 0, 255);
  analogWrite(pwm_pin, led);
  
  Serial.println(potenc);
  delay(100);
}
