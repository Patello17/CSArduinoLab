void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);
  pinMode(9, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  // play tone when button is pressed
  if (digitalRead(9) == LOW) {
    tone(12, 1000);
  }
  // don't play tone if button is not pressed
  else { noTone(12); }
}
