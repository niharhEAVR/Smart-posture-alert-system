#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>

// -------------------- MPU6050 --------------------
#define MPU_ADDR 0x68

int16_t ax, ay, az;
int16_t gx, gy, gz;

float ax_g, ay_g, az_g;

float pitch_raw = 0;
float pitch_filtered = 0;

// -------------------- Timing --------------------
unsigned long lastTime = 0;
float dt = 0;

// -------------------- Calibration --------------------
float baseline = 0;
bool calibrated = false;
float slouch_threshold = 0;

// -------------------- Slouch Detection --------------------
float slouchTime = 0;
bool isSlouching = false;

// -------------------- WiFi --------------------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

const char* serverURL = "http://YOUR_SERVER_IP:3000/data";

// -------------------- FUNCTION: Read MPU --------------------
void readMPU() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);

  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();

  Wire.read(); Wire.read(); // skip temp

  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();
}

// -------------------- FUNCTION: Send Data --------------------
void sendData(float pitch, bool slouch) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    String json = "{";
    json += "\"pitch\":" + String(pitch) + ",";
    json += "\"slouch\":" + String(slouch ? "true" : "false");
    json += "}";

    int httpResponseCode = http.POST(json);

    Serial.print("HTTP Response: ");
    Serial.println(httpResponseCode);

    http.end();
  }
}

// -------------------- SETUP --------------------
void setup() {
  Serial.begin(115200);

  // I2C init
  Wire.begin(21, 22);

  // Wake MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.println("MPU6050 Initialized");

  // WiFi connect
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.println(WiFi.localIP());
}

// -------------------- LOOP --------------------
void loop() {

  // ---- Time ----
  unsigned long now = millis();
  dt = (now - lastTime) / 1000.0;
  lastTime = now;

  // ---- Read Sensor ----
  readMPU();

  // ---- Convert to g ----
  ax_g = ax / 16384.0;
  ay_g = ay / 16384.0;
  az_g = az / 16384.0;

  // ---- Calculate Pitch ----
  pitch_raw = atan2(ax_g, sqrt(ay_g * ay_g + az_g * az_g)) * 180 / PI;

  // ---- Filter ----
  pitch_filtered = 0.9 * pitch_filtered + 0.1 * pitch_raw;

  // ---- Stability Check ----
  float total_acc = sqrt(ax_g * ax_g + ay_g * ay_g + az_g * az_g);
  bool stable = abs(total_acc - 1.0) < 0.1;

  // ---- Calibration ----
  if (!calibrated) {
    Serial.println("Sit straight for calibration...");
    delay(3000);

    baseline = pitch_filtered;
    slouch_threshold = baseline + 15;

    calibrated = true;

    Serial.print("Baseline: ");
    Serial.println(baseline);
  }

  // ---- Slouch Detection ----
  if (calibrated && stable) {

    if (pitch_filtered > slouch_threshold) {
      slouchTime += dt;
    } else {
      slouchTime = 0;
    }

    // Slouch detected
    if (slouchTime > 5 && !isSlouching) {
      Serial.println("SLOUCHING DETECTED");
      isSlouching = true;

      sendData(pitch_filtered, true);
    }

    // Corrected
    if (isSlouching && pitch_filtered <= baseline + 5) {
      Serial.println("POSTURE CORRECTED");
      isSlouching = false;

      sendData(pitch_filtered, false);
    }
  }

  // ---- Debug Output ----
  Serial.print("Pitch: ");
  Serial.print(pitch_filtered);

  Serial.print(" | Baseline: ");
  Serial.print(baseline);

  Serial.print(" | Threshold: ");
  Serial.print(slouch_threshold);

  Serial.print(" | Time: ");
  Serial.print(slouchTime);

  Serial.print(" | State: ");
  Serial.println(isSlouching ? "SLOUCH" : "OK");

  delay(100);
}