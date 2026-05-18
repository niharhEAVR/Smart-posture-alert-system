#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <math.h>

// ===== WIFI CONFIG =====
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ===== WEB SERVER =====
WebServer server(80);

// ===== MPU6050 CONFIG =====
const int MPU_ADDR = 0x68;

// Raw sensor data
float ax, ay, az;
float gx, gy, gz;

// ===== SENSOR FUSION =====
float pitch = 0;
float roll = 0;

float alpha = 0.98;
unsigned long prevTime = 0;

// ===== CALIBRATION =====
float pitchOffset = 0;
float rollOffset = 0;

// ===== POSTURE =====
String postureState = "UNKNOWN";

// ===== SETUP =====
void setup() {
  Serial.begin(115200);

  // Initialize I2C
  Wire.begin();
  
  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());

  // Web routes
  server.on("/", handleRoot);
  server.on("/calibrate", handleCalibrate);
  server.on("/data", handleData);

  server.begin();

  prevTime = millis();
}

// ===== LOOP =====
void loop() {
  readMPU();
  updateFusion();
  detectPosture();

  server.handleClient();
}

// ===== READ MPU6050 =====
void readMPU() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);

  ax = (Wire.read() << 8 | Wire.read()) / 16384.0;
  ay = (Wire.read() << 8 | Wire.read()) / 16384.0;
  az = (Wire.read() << 8 | Wire.read()) / 16384.0;

  Wire.read(); Wire.read(); // skip temp

  gx = (Wire.read() << 8 | Wire.read()) / 131.0;
  gy = (Wire.read() << 8 | Wire.read()) / 131.0;
  gz = (Wire.read() << 8 | Wire.read()) / 131.0;
}

// ===== SENSOR FUSION =====
void updateFusion() {
  unsigned long currentTime = millis();
  float dt = (currentTime - prevTime) / 1000.0;
  prevTime = currentTime;

  float accelPitch = atan2(ay, az) * 180 / PI;
  float accelRoll  = atan2(-ax, sqrt(ay * ay + az * az)) * 180 / PI;

  pitch = alpha * (pitch + gx * dt) + (1 - alpha) * accelPitch;
  roll  = alpha * (roll  + gy * dt) + (1 - alpha) * accelRoll;
}

// ===== POSTURE DETECTION =====
void detectPosture() {
  float adjustedPitch = pitch - pitchOffset;

  if (abs(adjustedPitch) > 15) {
    postureState = "SLOUCHING";
  } else {
    postureState = "CORRECT";
  }

  Serial.print("Pitch: ");
  Serial.print(pitch);
  Serial.print(" | Posture: ");
  Serial.println(postureState);
}

// ===== CALIBRATION =====
void calibratePosture() {
  pitchOffset = pitch;
  rollOffset = roll;
}

// ===== WEB HANDLERS =====
void handleRoot() {
  String html = "<html><body>";
  html += "<h1>ESP32 Posture Monitor</h1>";
  html += "<p>Posture: " + postureState + "</p>";
  html += "<button onclick=\"fetch('/calibrate')\">Calibrate</button>";
  html += "<br><br>";
  html += "<button onclick=\"location.reload()\">Refresh</button>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleCalibrate() {
  calibratePosture();
  server.send(200, "text/plain", "Calibrated!");
}

void handleData() {
  String json = "{";
  json += "\"pitch\":" + String(pitch) + ",";
  json += "\"roll\":" + String(roll) + ",";
  json += "\"posture\":\"" + postureState + "\"";
  json += "}";

  server.send(200, "application/json", json);
}