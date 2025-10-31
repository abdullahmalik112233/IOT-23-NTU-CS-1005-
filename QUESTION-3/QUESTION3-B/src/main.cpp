// M. Hamza
// 23-NTU-CS-1186

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Pin configuration ---
#define BUTTON_PIN 34
#define LED_PIN 18
#define BUZZER_PIN 12

// --- Buzzer PWM configuration ---
#define BUZZER_CHANNEL 0
#define BUZZER_FREQ 2000
#define BUZZER_RESOLUTION 8

// --- Variables ---
bool ledState = false;
bool buttonPressed = false;
unsigned long pressStart = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; // ms
int lastButtonState = HIGH;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  ledcSetup(BUZZER_CHANNEL, BUZZER_FREQ, BUZZER_RESOLUTION);
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.println("System Ready");
  display.display();
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  // Debounce check
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Button pressed
    if (reading == LOW && !buttonPressed) {
      buttonPressed = true;
      pressStart = millis();
    }

    // Button released
    if (reading == HIGH && buttonPressed) {
      unsigned long pressDuration = millis() - pressStart;
      buttonPressed = false;

      if (pressDuration < 1500) {
        // Short press → toggle LED
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState ? HIGH : LOW);

        display.clearDisplay();
        display.setCursor(10, 20);
        display.print("LED ");
        display.println(ledState ? "ON" : "OFF");
        display.display();
      } 
      else {
        // Long press → buzzer
        ledcWriteTone(BUZZER_CHANNEL, BUZZER_FREQ);
        display.clearDisplay();
        display.setCursor(10, 20);
        display.println("Long Press Detected");
        display.display();
        delay(1000);
        ledcWrite(BUZZER_CHANNEL, 0);
      }
    }
  }

  lastButtonState = reading;
}