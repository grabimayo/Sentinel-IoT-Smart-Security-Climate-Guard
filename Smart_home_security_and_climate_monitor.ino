#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// --- WiFi Credentials ---
const char *ssid = "Jes";
const char *password = "Jesy1291";

// --- Hardware Pins ---
#define DHTPIN 26      
#define DHTTYPE DHT11
#define PIR_PIN 34     
#define BUZZER_PIN 27  
#define LED_PIN 25     

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

// Global Variables for Status
bool manualOverride = false; 
String alarmStatus = "SYSTEM SECURE";

void handleRoot() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int motion = digitalRead(PIR_PIN);

  // --- AUTOMATIC LOGIC (The "Brain") ---
  if (motion == HIGH) {
    // 1. Automatic Trigger
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    alarmStatus = "!!! MOTION DETECTED - ALARM ON !!!";
  } else {
    // 2. Automatic Turn-off (unless manual button is ON)
    digitalWrite(LED_PIN, LOW);
    if (manualOverride == false) {
      digitalWrite(BUZZER_PIN, LOW);
    }
    alarmStatus = "SYSTEM SECURE - MONITORING";
  }

  // --- HTML INTERFACE ---
  String html = "<html><head><meta http-equiv='refresh' content='2'>";
  html += "<style>body{font-family:Arial; text-align:center; background:#f4f4f4;}";
  html += ".status{font-size:24px; color:red; font-weight:bold;}";
  html += ".btn{padding:15px; background:#3498db; color:white; text-decoration:none; border-radius:5px;}</style></head><body>";
  
  html += "<h1>IoT Assignment 1: Two-Way System</h1>";
  
  html += "<h3>Live Telemetry</h3>";
  html += "<p>Temp: " + String(isnan(temp) ? 0 : temp) + " C | Hum: " + String(isnan(hum) ? 0 : hum) + " %</p>";
  html += "<p>PIR Sensor: <b>" + String(motion == HIGH ? "MOTION!!" : "QUIET") + "</b></p>";
  
  html += "<hr><div class='status'>" + alarmStatus + "</div>";
  
  html += "<h3>Actuator Control</h3>";
  html += "<p>Manual Buzzer Test: " + String(manualOverride ? "ON" : "OFF") + "</p>";
  html += "<a class='btn' href='/toggle'>TOGGLE MANUAL TEST</a>";
  
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleToggle() {
  manualOverride = !manualOverride;
  // If manual test is ON, turn buzzer ON. If OFF, let the PIR sensor decide.
  digitalWrite(BUZZER_PIN, manualOverride ? HIGH : LOW);
  server.sendHeader("Location", "/"); 
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  dht.begin();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nIP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.begin();
}

void loop() {
  server.handleClient();
  
  // Extra safety: Constant check for PIR motion in loop
  if (digitalRead(PIR_PIN) == HIGH) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
  }
}