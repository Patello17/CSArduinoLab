// #define PRESS_EXIT_DETECTION_TIME 2000 // how long to press to exit detection mode in milliseconds
#define EXIT_DETECTION_TIME 5000 // how long to wait to exit detection mode in milliseconds
#define DOT_DETECTION_TIME 500 // how long to press to register a dot in milliseconds
#define DASH_DETECTION_TIME 1500 // how long to press to register a dash in milliseconds
#define LETTER_PAUSE_DETECTION_TIME 1000 // how long to press to register a dash in milliseconds
#define WORD_PAUSE_DETECTION_TIME 3500 // how long to press to register a dash in milliseconds

#include "decoding.h"
#include <ArxContainer.h>
#include <List.hpp>

// map to store decoding keys and values
arx::map<String, String, 47> decodingMap = {
    {".-", "A"},
    {"-...", "B"},
    {"-.-.", "C"},
    {"-..", "D"},
    {".", "E"},
    {"..-.", "F"},
    {"--.", "G"},
    {"....", "H"},
    {"..", "I"},
    {".---", "J"},
    {"-.-", "K"},
    {".-..", "L"},
    {"--", "M"},
    {"-.", "N"},
    {"---", "O"},
    {".--.", "P"},
    {"--.-", "Q"},
    {".-.", "R"},
    {"...", "S"},
    {"-", "T"},
    {"..-", "U"},
    {"...-", "V"},
    {".--", "W"},
    {"-..-", "X"},
    {"-.--", "Y"},
    {"--..", "Z"},
    {".----", "1"},
    {"..---", "2"},
    {"...--", "3"},
    {"....-", "4"},
    {".....", "5"},
    {"-....", "6"},
    {"--...", "7"},
    {"---..", "8"},
    {"----.", "9"},
    {"-----", "0"},
    {"..--..", "?"},
    {"-.-.--", "!"},
    {".-.-.-", "."},
    {"--..--", ","},
    {"-.-.-.", ";"},
    {"---...", ":"},
    {".-.-.", "+"},
    {"-....-", "-"},
    {"/", "-..-."},
    {"-...-", "="}
};

bool currentButtonState = false;
bool previousButtonState = false;
bool morseInputState = false;
float buttonPressDuration; // how long the button is pressed
float buttonUnpressDuration; // how long the button is unpressed

float timeAtTrigger = millis();
float timeAtRelease = millis();
float elapsedExitTime = 0.0;
bool allowDot;
bool allowDash;
bool allowLetterSpace;
bool allowWordSpace;
bool allowReset;
String morseMessage = "";
String alphabetMessage = "";

void decode(int ledPin, int buzzerPin, int inputPin) {
    decodeMessage(detectMorse(ledPin, buzzerPin, inputPin));
    outputAlphabet();
}
String detectMorse(int ledPin, int buzzerPin, int inputPin) {
    
    if (elapsedExitTime >= EXIT_DETECTION_TIME && allowReset) {
        // reset variables
        timeAtTrigger = 0.0;
        timeAtRelease = 0.0;
        buttonPressDuration = 0.0;
        buttonUnpressDuration = 0.0;
        elapsedExitTime = 0.0;
        allowReset = false;
        morseMessage = "";
    }
    else {
        // check for button press
        if (digitalRead(inputPin) == LOW) { 
            currentButtonState = true; 
        } else currentButtonState = false;

        // check if we transitioned from unpressed to pressed
        if (currentButtonState && !previousButtonState) {
            previousButtonState = currentButtonState;
            morseInputState = true;
            timeAtTrigger = millis(); // get time when button is first pressed
            allowReset = true;
            allowLetterSpace = true;
            allowWordSpace = true;
        }
        // check if we transitioned from pressed to unpressed
        else if (!currentButtonState && previousButtonState) {
           previousButtonState = currentButtonState;
           morseInputState = false;
           timeAtRelease = millis(); // get time when button is released
           allowDot = true;
           allowDash = true;
        }

        // find how long the button is being pressed or unpressed, and update LED and buzzer
        if (morseInputState) { 
            buttonPressDuration = millis() - timeAtTrigger; 
            buttonUnpressDuration = 0.0;
            elapsedExitTime = 0.0;
            digitalWrite(ledPin, HIGH);
            digitalWrite(buzzerPin, HIGH);
        }
        else {
            buttonUnpressDuration = millis() - timeAtRelease;
            buttonPressDuration = 0.0;
            elapsedExitTime = millis() - timeAtRelease;
            digitalWrite(ledPin, LOW);
            digitalWrite(buzzerPin, LOW);
        }

        // note morse signal
        if (0 < buttonPressDuration && buttonPressDuration < DOT_DETECTION_TIME && allowDot) {
            morseMessage += ".";
            allowDot = false;
        }
        else if (DOT_DETECTION_TIME < buttonPressDuration && buttonPressDuration < DASH_DETECTION_TIME && allowDash) {
            morseMessage.remove(morseMessage.length() - 1);
            morseMessage += "-";
            allowDash = false;
        }
        // note morse space
        if (LETTER_PAUSE_DETECTION_TIME < buttonUnpressDuration && buttonUnpressDuration < WORD_PAUSE_DETECTION_TIME && allowLetterSpace && morseMessage.length() > 0) {
            morseMessage += "|";
            allowLetterSpace = false;
        }
        else if (WORD_PAUSE_DETECTION_TIME < buttonUnpressDuration && allowWordSpace && morseMessage.length() > 0) {
            morseMessage.remove(morseMessage.length() - 1);
            morseMessage += "/";
            allowWordSpace = false;
        }
    }
    // Serial.print("Pressed: ");
    // Serial.print(buttonPressDuration);
    // Serial.print(" ||| Unpressed: ");
    // Serial.print(buttonUnpressDuration);
    // Serial.print(" ||| State: ");
    // Serial.println(morseInputState);
    // Serial.print(buttonPressDuration);
    // Serial.print(" || ");
    // Serial.println(morseMessage);
    return morseMessage;
}

void decodeMessage(String morseMessage) {
    // get morse letters (between spaces and/or bounds)
    String morseLetter = "";
    alphabetMessage = "";
    int letterStartIndex = 0;
    int letterEndIndex = 0;
    List<int> letterIndexList;
    List<int> spaceIndexList;
    
    // identify bounds (the start, spaces between letters, and the end)
    letterIndexList.add(0);
    for (int i = 0; i < morseMessage.length(); i++) {
        // if (i == 0)
        // if (i == morseMessage.length() - 1) { letterEndIndex = morseMessage.length() - 1; }
        if ((String)morseMessage[i] == "|") {  letterIndexList.add(i);}
        if ((String)morseMessage[i] == "/") {
            letterIndexList.add(i);
            spaceIndexList.add(i);
        }
    }
    letterIndexList.add(morseMessage.length() - 1);
    
    for (int i = 0; i < letterIndexList.getSize() - 1; i++) {
        if (letterIndexList[i] == 0) { letterStartIndex = 0; }
        else letterStartIndex = letterIndexList.get(i) + 1;
        // letterStartIndex = letterIndexList.get(i);
        if (letterIndexList[i] == letterIndexList.getSize() - 1) { letterEndIndex = letterIndexList.getSize() - 1; }
        else letterEndIndex = letterIndexList.get(i + 1) - 1;

        for (int j = letterStartIndex; j <= letterEndIndex; j++) {
            morseLetter += morseMessage[j];
            for (int k = 0; k < spaceIndexList.getSize(); k++) {
                if (j - 1 == spaceIndexList[k]) {
                alphabetMessage += " ";
                }
            }
        }

        

        if (checkInput(morseLetter)) { alphabetMessage += decodingMap[(String)morseLetter]; }
        else if (morseLetter.length() > 1) { alphabetMessage += "#"; }
        morseLetter = "";
    }
}

void outputAlphabet() {
    if (morseMessage.length() > 0) {
        Serial.print("Morse: ");
        Serial.print(morseMessage);
        Serial.print(" = Translated: ");
        Serial.println(alphabetMessage);
    }
    else Serial.println("Please input a message in morse code.");
}

bool checkInput(String input) {
    for (const auto& key : decodingMap) {
        if (input == key.first) { return true; }
    }
    return false;
}

// void changeButtonState(int pin) {
//     // check for button press
//     if (digitalRead(pin) == LOW) { 
//         currentButtonState = true; 
//     } else {    
//         currentButtonState = false;
//     }
//     // check if we transitioned from unpressed to pressed
//     if (currentButtonState && !previousButtonState) {
//         previousButtonState = currentButtonState;
//         if (morseInputState == false) { morseInputState = true; }
//         else if (morseInputState == true) { morseInputState = false; }
//     }
//     // check if we transitioned from pressed to unpressed
//     else if (!currentButtonState && previousButtonState) {
//         previousButtonState = currentButtonState;
//     }
    
// }
