void setup() {
  // put your setup code here, to run once:
  // set pin modes
  pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // read analog input values (1 - 1023)
  int sensorValue = analogRead(A0);
  // convert analog input into brightnessValue (1 - 255)
  float brightnessValue = sensorValue * (255.0 / 1023.0);

  // send pwm signal to LED
  analogWrite(12, brightnessValue);
}
