#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// --- Pin configuration ---
#define DHTPIN 14         // DHT sensor data pin
#define DHTTYPE DHT11     // Change to DHT22 if needed
#define LDR_PIN 36        // LDR analog input pin
#define SDA_PIN 21        // I2C SDA
#define SCL_PIN 22        // I2C SCL

// --- OLED setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- DHT sensor setup ---
DHT dht(DHTPIN, DHTTYPE);

// --- Setup ---
void setup() {
  Serial.begin(115200);
  Serial.println("Starting IoT Environment Monitor...");

  // Initialize I2C on custom pins
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed!");
    for (;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Initializing Sensors...");
  display.display();

  // Initialize DHT sensor
  dht.begin();
  delay(1500);

  Serial.println("Setup complete!");
}

// --- Main Loop ---
void loop() {
  // Read sensors
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int adcValue = analogRead(LDR_PIN);
  float voltage = (adcValue / 4095.0) * 3.3;

  // Check for sensor read errors
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error reading DHT sensor!");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Sensor Error!");
    display.display();
    delay(2000);
    return;
  }

  // --- Print to Serial Monitor ---
  Serial.printf("Temp: %.2f °C  |  Humidity: %.2f %%  |  LDR ADC: %d (%.2f V)\n", 
                temperature, humidity, adcValue, voltage);

  // --- Display on OLED ---
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("AI Lab Monitor");

  display.setCursor(0, 12);
  display.print("Temp: ");
  display.print(temperature, 1);
  display.println(" C");

  display.setCursor(0, 24);
  display.print("Humidity: ");
  display.print(humidity, 1);
  display.println(" %");

  display.setCursor(0, 36);
  display.print("LDR: ");
  display.print(adcValue);
  
  display.setCursor(0, 48);
  display.print("Volt: ");
  display.print(voltage, 2);
  display.println(" V");

  display.display();

  delay(2000);
}
