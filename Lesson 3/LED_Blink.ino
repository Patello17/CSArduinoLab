void setup() {
  // put your setup code here, to run once:
  pinMode(52, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(52, HIGH);
  delay(500);
  digitalWrite(52, LOW);
  delay(500);
}
