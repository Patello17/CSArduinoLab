void setup() {
  // put your setup code here, to run once:
  
  // initialize serial connection
  Serial.begin(9600);
  char characterName[]="Peter";
  int characterAge = 18;

  Serial.print("There once was a man named ");
  Serial.print(characterName);
  Serial.println(".");
  

  Serial.print("He was ");
  Serial.print(characterAge);
  Serial.println(" years old.");  

}

void loop() {
  // put your main code here, to run repeatedly:

}
