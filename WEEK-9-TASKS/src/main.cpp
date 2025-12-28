
#include <WiFi.h>

const char* ssid = "Abdullah";
const char* password = "abdullah1005";

WiFiServer server(80);
const int LED_PIN = 2;    // Built-in LED

IPAddress local_IP(10,95,236, 155); // ESP32 IP
IPAddress gateway(10,95,236 ,255); // Router IP
IPAddress subnet(10,95,236,0);



void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // LED off at start
  WiFi.config(local_IP,gateway,subnet);


  // Connect WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;  // No client, exit

  Serial.println("New Client connected");
  String request = client.readStringUntil('\r');
  Serial.println(request);

  // ----- LED CONTROL -----
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(LED_PIN, HIGH);
  }
  if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(LED_PIN, LOW);
  }

  // ----- RESPONSE PAGE -----
  String htmlPage =
    "<!DOCTYPE html><html>"
    "<h1>ESP32 LED Control</h1>"
    "<p><a href=\"/LED=ON\"><button>LED ON</button></a></p>"
    "<p><a href=\"/LED=OFF\"><button>LED OFF</button></a></p>"
    "</html>";

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(htmlPage);

  delay(1);
  client.stop();
  Serial.println("Client disconnected");
}