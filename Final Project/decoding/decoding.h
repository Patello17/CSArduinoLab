#ifndef DECODING_H
#define DECODING_H

#include <Arduino.h>

void decode(int ledPin, int buzzerPin, int morsePin);
String detectMorse(int ledPin, int buzzerPin, int morsePin);
void decodeMessage(String message);
void outputAlphabet();
bool checkInput(String input);

#endif