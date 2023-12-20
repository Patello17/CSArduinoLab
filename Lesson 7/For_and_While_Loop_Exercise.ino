int MAX_NUMBER = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.println("");
  Serial.begin(9600);
  for (int i = 0; i <= MAX_NUMBER; i++) {
    Serial.print(i);
    if (i != MAX_NUMBER)
      Serial.print(", ");
  }
  Serial.println("");
  int count = MAX_NUMBER;
  while (count >= 0) {
    Serial.print(count);
    if (count != 0)
      Serial.print(", ");
    count--;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
