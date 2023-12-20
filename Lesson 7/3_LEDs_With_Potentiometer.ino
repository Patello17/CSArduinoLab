int GREEN_LED = 44;
int YELLOW_LED = 46;
int RED_LED = 48;
int POT_LED = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(POT_LED, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  double val = analogRead(POT_LED);
  val = (val * 5.0) / 1023.0;
  Serial.println(val);
  if (0 <= val && val <= 1.67) {
    digitalWrite(GREEN_LED, HIGH); digitalWrite(YELLOW_LED, LOW); digitalWrite(RED_LED, LOW);
  }
  else if (1.67 < val && val <= 3.33) {
    digitalWrite(GREEN_LED, LOW); digitalWrite(YELLOW_LED, HIGH); digitalWrite(RED_LED, LOW);
  }
  else if (3.33 < val && val <= 5) {
    digitalWrite(GREEN_LED, LOW); digitalWrite(YELLOW_LED, LOW); digitalWrite(RED_LED, HIGH); 
  }
}
