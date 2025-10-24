// #include <Arduino.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include <DHT.h>

// #define MAX_POINTS 64
// float tempHistory[MAX_POINTS] = {0};  // initialize array with zeros
// int tempindex = 0;

// // --- Pin configuration ---
// #define DHTPIN 14        // DHT22 data pin
// #define DHTTYPE DHT22    // DHT22 sensor

// #define SDA_PIN 21       // I2C SDA
// #define SCL_PIN 22       // I2C SCL

// // --- OLED setup ---
// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// // --- DHT sensor setup ---
// DHT dht(DHTPIN, DHTTYPE);

// // Map temperature (0-50°C) to OLED Y coordinate (63 to 0)
// int mapTempToY(float temp) {
//   if (temp < 0) temp = 0;
//   if (temp > 50) temp = 50;
//   return 63 - (int)(temp * (63.0 / 50.0)); // invert Y axis: 0 is top
// }

// // --- Setup function ---
// void setup() {
//   Serial.begin(115200);
//   Serial.println("Hello, ESP32!");

//   // Initialize I2C on custom pins
//   Wire.begin(SDA_PIN, SCL_PIN);

//   // Initialize OLED
//   if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
//     Serial.println("SSD1306 allocation failed");
//     for (;;);
//   }
//   display.clearDisplay();
//   display.setTextColor(SSD1306_WHITE);
//   display.setTextSize(1);
//   display.setCursor(0, 0);
//   display.println("Initializing...");
//   display.display();

//   // Initialize DHT sensor
//   dht.begin();
//   delay(1000);
// }

// // --- Main loop ---
// void loop() {
//   float temperature = dht.readTemperature();
//   float humidity = dht.readHumidity();

//   // Check if read failed
//   if (isnan(temperature) || isnan(humidity)) {
//     Serial.println("Error reading DHT22 sensor!");
//     return;
//   }

//   // Store temperature in history buffer
//   tempHistory[tempindex++] = temperature;
//   if (tempindex >= MAX_POINTS) tempindex = 0;

//   // Print values on Serial Monitor
//   Serial.print("Temperature: ");
//   Serial.print(temperature);
//   Serial.print(" °C  |  Humidity: ");
//   Serial.print(humidity);
//   Serial.println(" %");

//   // Display temperature graph
//   display.clearDisplay();
//   display.setTextSize(1);
//   display.setCursor(0, 0);
//   display.println("Temp Graph:");

//   for (int i = 1; i < MAX_POINTS; i++) {
//     int x1 = i - 1;
//     int y1 = mapTempToY(tempHistory[(tempindex + i - 1) % MAX_POINTS]);
//     int x2 = i;
//     int y2 = mapTempToY(tempHistory[(tempindex + i) % MAX_POINTS]);
//     display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
//   }

//   display.display();

//   delay(2000); // update every 2 seconds
// }
