#define LED_PIN1 26
#define BUTTON_PIN1 22
#define LED_PIN2 28
#define BUTTON_PIN2 24

enum LED_STATE {OFF, ON, BLINKING};

LED_STATE currentLEDState1;
bool previousButton1;
bool currentButton1;

LED_STATE currentLEDState2;
bool previousButton2;
bool currentButton2;

void setup() {
  // set pin modes
  pinMode(LED_PIN1, OUTPUT);
  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  // set the LEDs to off;
  digitalWrite(LED_PIN1, LOW);
  currentLEDState1 = OFF;
  digitalWrite(LED_PIN2, LOW);
  currentLEDState2 = OFF;
  // check set initial state to unpressed
  previousButton1 = false;
  previousButton2 = false;
  // enable serial connection
  Serial.begin(9600);
}

void loop() {
  checkState(BUTTON_PIN1, &currentButton1, &previousButton1, &currentLEDState1);
  checkState(BUTTON_PIN2, &currentButton2, &previousButton2, &currentLEDState2);
  updateLEDs();
}

void checkState(int pin, bool *currentButton, bool *previousButton, LED_STATE *currentLEDState) {
  // check for button press
  *currentButton = isPressed(pin);
  // check if we transitioned from unpressed to pressed
  if (*currentButton == true && *previousButton == false) {
    Serial.println("Button was just pressed");
    *previousButton = *currentButton;
    // change the state of the LED
    if (*currentLEDState == OFF) {
      // switch from OFF to ON
      *currentLEDState = ON;
      Serial.println("LED switched to ON!");
    } else {
      // toggle LED to OFF
      *currentLEDState = OFF;
      Serial.println("LED switched to OFF!");
    }
  }
  // check if we transitioned from pressed to unpressed
  else if (*currentButton == false && *previousButton == true) {
    Serial.println("Button was just released");
    *previousButton = *currentButton;
  }
}

void updateLEDs() {
  // update LEDs based on the state of the LED
  if (currentLEDState1 == ON) { digitalWrite(LED_PIN1, ON); }
  else if (currentLEDState1 == OFF) { digitalWrite(LED_PIN1, OFF); }

  if (currentLEDState2 == ON) { digitalWrite(LED_PIN2, ON); }
  else if (currentLEDState2 == OFF) { digitalWrite(LED_PIN2, OFF); }
}

bool isPressed(int pin) {
  if (digitalRead(pin) == LOW) { return true; }
  return false;
}