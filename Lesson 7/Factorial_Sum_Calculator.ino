void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  unsigned long factorialOne = calculate_factorial(8);
  unsigned long factorialTwo = calculate_factorial(10);
  
  Serial.println("");
  Serial.print("Factorial 1: ");
  Serial.println(factorialOne);
  Serial.print("Factorial 2: ");
  Serial.println(factorialTwo);
  Serial.print("Sum: ");
  Serial.println(add_numbers(factorialOne, factorialTwo));
}

void loop() {
  // put your main code here, to run repeatedly:
}

double calculate_factorial(int number) {
  long factorial = 1.0;
  for (int i = 1; i <= number; i++) {
    factorial *= i;
  }
  return factorial;
}

long add_numbers(long number1, long number2) {
  return (number1 + number2);
}
