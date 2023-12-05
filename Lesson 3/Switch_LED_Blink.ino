void setup() {
  // put your setup code here, to run once:
  pinMode(50, INPUT);
  pinMode(52, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(50)){
    digitalWrite(52, HIGH);
  }
  else {
    digitalWrite(52, LOW);
  }
}
