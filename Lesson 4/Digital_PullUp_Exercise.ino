void setup() {
  // put your setup code here, to run once:
  // initialize serial connection
  Serial.begin(9600);
  // set pin modes
  pinMode(52, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(52) == LOW){
    Serial.println("ON");
  }
}
