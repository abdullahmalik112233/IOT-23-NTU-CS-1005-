#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- Pin setup ---
#define BUTTON1 34
#define BUTTON2 35
#define LED_RED 23
#define LED_GREEN 4
#define LED_BLUE 5

// --- OLED setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Mode Variables ---
int mode = 0;
bool lastButton1 = HIGH;
bool lastButton2 = HIGH;

// --- PWM Setup (ESP32 specific) ---
const int CH_RED = 0;
const int CH_GREEN = 1;
const int CH_BLUE = 2;
const int PWM_FREQ = 5000;
const int PWM_RES = 8; // 0–255

// --- Timing variables ---
unsigned long prevMillis = 0;
int fadeValue = 0;
int fadeStep = 5;
bool toggle = false;

// --- OLED Display Function ---
void showMode(const char* text) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 25);
  display.println(text);
  display.display();
}

// --- Helper Functions ---
void allOff() {
  ledcWrite(CH_RED, 0);
  ledcWrite(CH_GREEN, 0);
  ledcWrite(CH_BLUE, 0);
}

void allOn() {
  ledcWrite(CH_RED, 255);
  ledcWrite(CH_GREEN, 255);
  ledcWrite(CH_BLUE, 255);
}

void alternateBlink() {
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis >= 400) {
    prevMillis = currentMillis;
    toggle = !toggle;
    if (toggle) {
      ledcWrite(CH_RED, 255);
      ledcWrite(CH_GREEN, 0);
      ledcWrite(CH_BLUE, 0);
    } else {
      ledcWrite(CH_RED, 0);
      ledcWrite(CH_GREEN, 255);
      ledcWrite(CH_BLUE, 255);
    }
  }
}

void pwmFade() {
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis >= 20) {
    prevMillis = currentMillis;
    fadeValue += fadeStep;
    if (fadeValue <= 0 || fadeValue >= 255) fadeStep = -fadeStep;
    ledcWrite(CH_RED, fadeValue);
    ledcWrite(CH_GREEN, fadeValue);
    ledcWrite(CH_BLUE, fadeValue);
  }
}

// --- Setup ---
void setup() {
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);

  // --- OLED init ---
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  // --- LED PWM setup ---
  ledcSetup(CH_RED, PWM_FREQ, PWM_RES);
  ledcSetup(CH_GREEN, PWM_FREQ, PWM_RES);
  ledcSetup(CH_BLUE, PWM_FREQ, PWM_RES);

  ledcAttachPin(LED_RED, CH_RED);
  ledcAttachPin(LED_GREEN, CH_GREEN);
  ledcAttachPin(LED_BLUE, CH_BLUE);

  allOff();
  showMode("Both OFF");
}

// --- Main Loop ---
void loop() {
  bool btn1 = digitalRead(BUTTON1);
  bool btn2 = digitalRead(BUTTON2);

  // --- Button 1: Cycle Mode ---
  if (btn1 == LOW && lastButton1 == HIGH) {
    mode++;
    if (mode > 3) mode = 0;
    switch (mode) {
      case 0: showMode("Both OFF"); allOff(); break;
      case 1: showMode("Alt Blink"); break;
      case 2: showMode("Both ON"); allOn(); break;
      case 3: showMode("PWM Fade"); break;
    }
    delay(250); // debounce
  }

  // --- Button 2: Reset ---
  if (btn2 == LOW && lastButton2 == HIGH) {
    mode = 0;
    allOff();
    showMode("Both OFF");
    delay(250);
  }

  lastButton1 = btn1;
  lastButton2 = btn2;

  // --- Mode Execution ---
  switch (mode) {
    case 0: allOff(); break;
    case 1: alternateBlink(); break;
    case 2: allOn(); break;
    case 3: pwmFade(); break;
  }
}
