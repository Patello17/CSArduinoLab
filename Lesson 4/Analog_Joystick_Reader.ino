void setup() {
  // put your setup code here, to run once:
  // initialize serial connection
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // read x, y values (bottomLeft = (0.00, 0.00), rest = (0.50, 0.50))
  int sensorValueX = analogRead(A0);
  int sensorValueY = analogRead(A1);

  // convert input values to coordinates between (-1.0, 1.0)
  float xCoordinate = (2.0 * sensorValueX / 1023.0) - 1;
  float yCoordinate = (2.0 * sensorValueY / 1023.0) - 1;

  Serial.print(xCoordinate);
  Serial.print(", ");
  Serial.println(yCoordinate);
}
