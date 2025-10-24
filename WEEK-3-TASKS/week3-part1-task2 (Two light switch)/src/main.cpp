// Ali Hassan 
//23-NTU-CS-1011

// Program to Turn both lights on when the button clicks
#include <Arduino.h>

const int buttonPin = 35;
const int ledPin1 = 18;
const int ledPin2 = 21;
volatile bool ledState = LOW;

void IRAM_ATTR handleButton() {
  ledState = !ledState;
  digitalWrite(ledPin1, ledState);
  digitalWrite(ledPin2, ledState);
}

void setup() {
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButton, FALLING);
}

void loop() {
  // main loop free for other tasks
}