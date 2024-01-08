#define LED_PIN1 26
#define BUTTON_PIN1 22
#define LED_PIN2 28
#define BUTTON_PIN2 24

enum LED_STATE {OFF, ON, BLINKING};

LED_STATE currentLEDState1; // Current State of the LED
bool previousButton1; // Whether the button was previously pressed
bool currentButton1; // Whether the button is currently pressed
bool blinkState1; // State of the Blinking LED (ON or OFF)
float blinkDelay1; // Interval between blinks
float blinkTime1; // Time to next blinkState relative to current time (currentTime + blinkDelay)

LED_STATE currentLEDState2;
bool previousButton2;
bool currentButton2;
bool blinkState2;
float blinkDelay2;
float blinkTime2;

float currentTime;

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
  // start blinking when state is changed to BLINKING
  blinkState1 = true;
  blinkState2 = true;
  // set blink intervals
  blinkDelay1 = 500.0;
  blinkDelay2 = 250.0;
  // enable serial connection
  Serial.begin(9600);
}

void loop() {
  currentTime = millis();
  checkState(BUTTON_PIN1, &currentButton1, &previousButton1, &currentLEDState1, &blinkTime1);
  checkState(BUTTON_PIN2, &currentButton2, &previousButton2, &currentLEDState2, &blinkTime2);
  updateLEDs();
}

void checkState(int pin, bool* currentButton, bool* previousButton, LED_STATE* currentLEDState, float* blinkTime) {
  // check for button press
  *currentButton = isPressed(pin);
  // check if we transitioned from unpressed to pressed
  if (*currentButton == true && *previousButton == false) {
    // Serial.println("Button was just pressed");
    *previousButton = *currentButton;
    // change the state of the LED
    if (*currentLEDState == OFF) {
      // switch from OFF to ON
      *currentLEDState = ON;
      Serial.println("LED switched to ON!");
    } 
    else if (*currentLEDState == ON) {
      // switch from ON to BLINKING
      *currentLEDState = BLINKING;
      *blinkTime = currentTime;
      Serial.println("LED switched to BLINKING!");
    }
    else if (*currentLEDState == BLINKING){
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
  else if (currentLEDState1 == BLINKING) { blink(LED_PIN1, &blinkState1, &blinkTime1, &blinkDelay1); }
  else if (currentLEDState1 == OFF) { digitalWrite(LED_PIN1, OFF); }

  if (currentLEDState2 == ON) { digitalWrite(LED_PIN2, ON); }
  else if (currentLEDState2 == BLINKING) { blink(LED_PIN2, &blinkState2, &blinkTime2, &blinkDelay2); }
  else if (currentLEDState2 == OFF) { digitalWrite(LED_PIN2, OFF); }
}

bool isPressed(int pin) {
  if (digitalRead(pin) == LOW) { return true; }
  return false;
}

bool blink(int pin, bool* blinkState, float* blinkTime, float* blinkDelay) {
  // change state when some time has passed
  if (*blinkTime == currentTime) {
    // change from ON to OFF
    if (*blinkState == true) {
      digitalWrite(pin, OFF);
      *blinkState = false;
    }
    // change from OFF to ON
    else if (*blinkState == false) {
      digitalWrite(pin, ON);
      *blinkState = true;
    }
    *blinkTime = currentTime + *blinkDelay;
  }
}