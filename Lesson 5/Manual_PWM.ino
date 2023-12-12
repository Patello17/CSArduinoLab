double dutyCycle = 0.25;
double periodTime = 1000.0 / 60.0;

void setup() {
  // put your setup code here, to run once:
  
  // set pin modes
  pinMode(12, OUTPUT);
  pinMode(9, INPUT_PULLUP);
}

void loop() {

  // turn on; delay based on dutyCycle percent
  digitalWrite(12, HIGH);
  int highTime = (double)(dutyCycle * periodTime);
  delay(highTime);

  // turn off; delay based on (1 - dutyCycle) percent  
  digitalWrite(12, LOW);
  int lowTime = (double)((1 - dutyCycle) * periodTime);
  delay(lowTime);

  // change dutyCycle based on button press
  if (digitalRead(9) == LOW) {
    dutyCycle += 0.05;
  }
  // reset dutyCycle to 0 if it is greater than 100%
  if (dutyCycle > 1.0) { dutyCycle = 0.0; }
}
