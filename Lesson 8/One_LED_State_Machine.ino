#define LED_PIN 26
#define BUTTON_PIN 24

enum LED_STATE {OFF, ON, BLINKING};

LED_STATE currentLEDState;
bool previousButton;
bool currentButton;

void setup() {
  // set pin modes
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  // set the LEDs to off;
  digitalWrite(LED_PIN, LOW);
  currentLEDState = OFF;
  // check set initial state to unpressed
  previousButton = false;
  // enable serial connection
  Serial.begin(9600);
}

void loop() {
  checkState();
  updateLEDs();
}

void checkState() {
  // check for button press
  currentButton = isPressed(BUTTON_PIN);
  // check if we transitioned from unpressed to pressed
  if (currentButton == true && previousButton == false) {
    Serial.println("Button was just pressed");
    previousButton = currentButton;
    // change the state of the LED
    if (currentLEDState == OFF) {
      // switch from OFF to ON
      currentLEDState = ON;
      Serial.println("LED switched to ON!");
    } else {
      // toggle LED to OFF
      currentLEDState = OFF;
      Serial.println("LED switched to OFF!");
    }
  }
  // check if we transitioned from pressed to unpressed
  else if (currentButton == false && previousButton == true) {
    Serial.println("Button was just released");
    previousButton = currentButton;
  }
}

void updateLEDs() {
  // update LEDs based on the state of the LED
  if (currentLEDState == ON) { digitalWrite(LED_PIN, ON); }
  else if (currentLEDState == OFF) { digitalWrite(LED_PIN, OFF); }
}

bool isPressed(int pin) {
  if (digitalRead(pin) == LOW) { return true; }
  return false;
}