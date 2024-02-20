#ifndef ENCODING_H
#define ENCODING_H

#include <Arduino.h>

void encode(int ledPin, int buzzerPin);
String detectAlphabet();
String encodeMessage(String message);
void outputMorse(int ledPin, int buzzerPin, String encodedMessage);
void blink(int ledPin, int buzzerPin, float beat);
void blinkDot(int ledPin, int buzzerPin);
void blinkDash(int ledPin, int buzzerPin);
void pauseLetter(int ledPin, int buzzerPin);
void pauseWord(int ledPin, int buzzerPin);

#endif