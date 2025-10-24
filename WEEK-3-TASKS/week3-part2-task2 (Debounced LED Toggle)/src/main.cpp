#include <Arduino.h>

#define LED_PIN     5     // On-board LED
#define BUTTON_PIN  34     // Button to GND
#define DEBOUNCE_MS 50

hw_timer_t *My_timer = nullptr;
volatile bool ledEnabled = true;        // flag toggled by button
volatile uint32_t lastButtonMs = 0;     // for debounce

// Timer ISR: blink LED only if enabled
void ARDUINO_ISR_ATTR onTimer() {
  if (ledEnabled) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }
}

// Button ISR: toggle enable flag (with debounce)
void ARDUINO_ISR_ATTR onButton() {
  uint32_t now = millis();
  if (now - lastButtonMs > DEBOUNCE_MS) {
    lastButtonMs = now;
    ledEnabled = !ledEnabled;   // toggle flag
    digitalWrite(LED_PIN, LOW); // reset LED when disabled
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Button interrupt (FALLING = pressed)
  attachInterrupt(BUTTON_PIN, onButton, FALLING);

  // Timer: 1 MHz tick
  My_timer = timerBegin(1000000);
  timerAttachInterrupt(My_timer, &onTimer);
  timerAlarm(My_timer, 500000, true, 0); // 0.5s period
}

void loop() {
  // nothing needed, all handled by interrupts
}