#define BEAT_MULTIPLIER 10 // how fast to play the signals (1 = 1 sec signals/pauses)
#define DOT_DURATION 1000 // duration of dots in milliseconds 
#define DASH_DURATION 3000 // duration of dashes in milliseconds
#define SIGNAL_PAUSE 1000 // pause duration between signals
#define LETTER_PAUSE 3000 // pause duration between letters
#define WORD_PAUSE 7000 // pause duration between words

#include "encoding.h"
#include <ArxContainer.h>

// map to store encoding keys and values
arx::map<String, String, 47> encodingMap = {
    {"A", ".-"},
    {"B", "-..."},
    {"C", "-.-."},
    {"D", "-.."},
    {"E", "."},
    {"F", "..-."},
    {"G", "--."},
    {"H", "...."},
    {"I", ".."},
    {"J", ".---"},
    {"K", "-.-"},
    {"L", ".-.."},
    {"M", "--"},
    {"N", "-."},
    {"O", "---"},
    {"P", ".--."},
    {"Q", "--.-"},
    {"R", ".-."},
    {"S", "..."},
    {"T", "-"},
    {"U", "..-"},
    {"V", "...-"},
    {"W", ".--"},
    {"X", "-..-"},
    {"Y", "-.--"},
    {"Z", "--.."},
    {"1", ".----"},
    {"2", "..---"},
    {"3", "...--"},
    {"4", "....-"},
    {"5", "....."},
    {"6", "-...."},
    {"7", "--..."},
    {"8", "---.."},
    {"9", "----."},
    {"0", "-----"},
    {"?", "..--.."},
    {"!", "-.-.--"},
    {".", ".-.-.-"},
    {",", "--..--"},
    {";", "-.-.-."},
    {":", "---..."},
    {"+", ".-.-."},
    {"-", "-....-"},
    {"/", "-..-."},
    {"=", "-...-"}
};

String input = ""; // stores input from Serial
String message = ""; // stores inputted messages
String encodedMessage = ""; // stores encoded messages

bool blinkState; // either on (true) or off (false)
float blinkTime; // current time + beat

void encode(int ledPin, int buzzerPin) {
    input = "";
    message = "";
    encodedMessage = "";
    blinkTime = millis();
    // constantly be on the look out for new messages
    message = detectAlphabet();
    if (message.length() > 0) {
        Serial.print(message);
        Serial.print(": ");
        encodedMessage = encodeMessage(message);
        outputMorse(ledPin, buzzerPin, encodedMessage);
    }
}

String detectAlphabet() {
    input = "";
    
    // get input
    while (Serial.available()) {
        input = Serial.readString();
    }
    // remove the "\n" that is necessary for the Serial Monitor to submit input
    input.remove(input.length() - 1);
    // send capitalized input (Morse is not case sensitive)
    input.toUpperCase();
    return input;
}

String encodeMessage(String message) {
    // Example: 
    // "loki paw" --> 
    // ".-.. --- -.- .. / .--. .- .--"
    
    String _encodedMessage = "";
    for (auto letter : message) {
        // encode shorts spaces between letters
        if ((String)letter != " ") {
            _encodedMessage += (encodingMap[(String)letter] + " "); 
        }
        // encode long spaces between words
        else { _encodedMessage += "/ "; }
    }
    Serial.println(_encodedMessage);
    return _encodedMessage;
}

void outputMorse(int ledPin, int buzzerPin, String encodedMessage) {
    // remove spaces directly behind and in front of a "/" to accurately pause
    for (int i = 0; i < encodedMessage.length(); i++) {
        if ((String)encodedMessage[i] == (String)"/") {
            encodedMessage.remove(i + 1, 1);
            encodedMessage.remove(i - 1, 1);
        }
    }

    // iterate through each signal in the encoded message
    for (int i = 0; i < encodedMessage.length(); i++) {
        // handle dots
        if ((String)encodedMessage[i] == (String)".") { blinkDot(ledPin, buzzerPin); }
        // handle dashes
        else if ((String)encodedMessage[i] == (String)"-") { blinkDash(ledPin, buzzerPin); }
        // handle pauses between letters
        else if ((String)encodedMessage[i] == (String)" ") { pauseLetter(ledPin, buzzerPin); }
        // handle pauses between words
        else if ((String)encodedMessage[i] == (String)"/") { pauseWord(ledPin, buzzerPin); }
    }
}

void blink(int ledPin, int buzzerPin, float beat) {
    // change state when some time has passed
    blinkTime = millis() + beat;
    while (blinkTime >= millis()) {
        if (blinkState == true) {
            digitalWrite(ledPin, HIGH);
            digitalWrite(buzzerPin, HIGH);
        }
        else {
            digitalWrite(ledPin, LOW);
            digitalWrite(buzzerPin, LOW);
        }
    }
    blinkState = false;
}

void blinkDot(int ledPin, int buzzerPin) {
    blinkState = true;
    blink(ledPin, buzzerPin, DOT_DURATION / BEAT_MULTIPLIER); // duration of dot
    // pause in between signals
    blinkState = false;
    blink(ledPin, buzzerPin, SIGNAL_PAUSE / BEAT_MULTIPLIER); // pause in between signals
}

void blinkDash(int ledPin, int buzzerPin) {
    blinkState = true;
    blink(ledPin, buzzerPin, DASH_DURATION / BEAT_MULTIPLIER); // duration of dash: lasts 3x as long as a dot
    // pause in between signals
    blinkState = false;
    blink(ledPin, buzzerPin, SIGNAL_PAUSE / BEAT_MULTIPLIER);
}

void pauseLetter(int ledPin, int buzzerPin) {
    blinkState = false;
    blink(ledPin, buzzerPin, (LETTER_PAUSE - SIGNAL_PAUSE) / BEAT_MULTIPLIER);
}

void pauseWord(int ledPin, int buzzerPin) {
    blinkState = false;
            blink(ledPin, buzzerPin, (WORD_PAUSE - SIGNAL_PAUSE) / BEAT_MULTIPLIER);
}