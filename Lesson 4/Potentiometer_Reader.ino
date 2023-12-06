void setup() {
  // put your setup code here, to run once:
  // initialize serial connection
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // read input from sensor (0 - 1023)
  int sensorValue = analogRead(A0);
  // scale value (0 - 5)
  float voltage = sensorValue * (5.0 / 1023.0);
  // display analog voltage
  Serial.println(voltage);
}
