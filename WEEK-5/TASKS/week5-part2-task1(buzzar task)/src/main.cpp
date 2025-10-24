#include <Arduino.h>

// --- Buzzer configuration ---
#define BUZZER_PIN  27
#define BUZZER_CH   0
#define BUZZER_FREQ 2000
#define BUZZER_RES  10

// --- LED configuration ---
#define LED1_PIN 18
#define LED2_PIN 19
#define LED1_CH  1
#define LED2_CH  2
#define LED_FREQ 5000
#define LED_RES  8   // 8-bit = 0–255 brightness

void setup() {
  Serial.begin(115200);

  // Setup buzzer
  ledcSetup(BUZZER_CH, BUZZER_FREQ, BUZZER_RES);
  ledcAttachPin(BUZZER_PIN, BUZZER_CH);

  // Setup LEDs (each with its own channel)
  ledcSetup(LED1_CH, LED_FREQ, LED_RES);
  ledcAttachPin(LED1_PIN, LED1_CH);

  ledcSetup(LED2_CH, LED_FREQ, LED_RES);
  ledcAttachPin(LED2_PIN, LED2_CH);

  // Test LEDs at full brightness
  ledcWrite(LED1_CH, 255);
  ledcWrite(LED2_CH, 255);
  Serial.println("LEDs should both be ON at full brightness");
  delay(2000);

  // Turn off before animation
  ledcWrite(LED1_CH, 0);
  ledcWrite(LED2_CH, 0);

  // --- Buzzer quick test ---
  ledcWriteTone(BUZZER_CH, 2000);
  delay(300);
  ledcWrite(BUZZER_CH, 0);
}

void loop() {
  // Fade both LEDs up and down in opposite pattern
  for (int d = 0; d <= 255; d += 5) {
    ledcWrite(LED1_CH, d);
    ledcWrite(LED2_CH, 255 - d);
    delay(10);
  }
  for (int d = 255; d >= 0; d -= 5) {
    ledcWrite(LED1_CH, d);
    ledcWrite(LED2_CH, 255 - d);
    delay(10);
  }

  // Short buzzer melody
  int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};
  for (int i = 0; i < 8; i++) {
    ledcWriteTone(BUZZER_CH, melody[i]);
    delay(200);
  }
  ledcWrite(BUZZER_CH, 0);
}