#define SWITCH_MODE_PIN 26
#define MORSE_INPUT_PIN 24
#define LED_PIN 32
#define BUZZER_PIN 34

#include "encoding.h"
#include "decoding.h"

enum CODING_MODE {ENCODING, DECODING};

CODING_MODE codingMode;
bool currentModePress;
bool previousModePress;

void setup() {
  // set pin modes
  pinMode(SWITCH_MODE_PIN, INPUT_PULLUP);
  pinMode(MORSE_INPUT_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  // set ENCODING as default
  codingMode = ENCODING;
  // set initial press to unpressed
  previousModePress = false;
  Serial.begin(9600);
}

void loop() {
  checkState();
  updateMode();
}

void checkState() {
  // check for button press
  currentModePress = isPressed(SWITCH_MODE_PIN);
  // check if we transitioned from unpressed to pressed
  if (currentModePress && !previousModePress) {
    previousModePress = currentModePress;
    if (codingMode == ENCODING) { codingMode = DECODING; }
    else if (codingMode == DECODING) { codingMode = ENCODING; }
  }
  // check if we transitioned from pressed to unpressed
  else if (!currentModePress && previousModePress) { 
    Serial.println("");
    previousModePress = currentModePress; 
  }
}

void updateMode() {
  // update mode based on the current state
  if (codingMode == ENCODING) {
    // run encoding logic
    // Serial.println("Encoding");
    encode(LED_PIN, BUZZER_PIN);
  }
  else if (codingMode == DECODING) {
    // run decoding logic
    // Serial.println("Decoding");
    decode(LED_PIN, BUZZER_PIN, MORSE_INPUT_PIN);
  }
}

bool isPressed(int pin) {
  if (digitalRead(pin) == LOW) { return true; }
  return false;
}
