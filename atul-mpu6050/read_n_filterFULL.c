#include <Wire.h>

// MPU6050 address
#define MPU_ADDR 0x68

// Raw data
int16_t ax, ay, az;
int16_t gx, gy, gz;

// Processed data
float ax_g, ay_g, az_g;
float pitch_raw = 0;
float pitch_filtered = 0;

// Timing
unsigned long lastTime = 0;
float dt = 0;

// ----------- FUNCTION: Read MPU6050 -----------
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

// ----------- SETUP -----------
void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22); // SDA, SCL

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.println("MPU6050 Initialized");
}

// ----------- LOOP -----------
void loop() {

  // --- Time calculation ---
  unsigned long now = millis();
  dt = (now - lastTime) / 1000.0;
  lastTime = now;

  // --- Read sensor ---
  readMPU();

  // --- Convert to g ---
  ax_g = ax / 16384.0;
  ay_g = ay / 16384.0;
  az_g = az / 16384.0;

  // --- Calculate pitch ---
  pitch_raw = atan2(ax_g, sqrt(ay_g * ay_g + az_g * az_g)) * 180 / PI;

  // --- Filter ---
  pitch_filtered = 0.9 * pitch_filtered + 0.1 * pitch_raw;

  // --- Stability check ---
  float total_acc = sqrt(ax_g * ax_g + ay_g * ay_g + az_g * az_g);
  bool stable = abs(total_acc - 1.0) < 0.1;

  // --- Debug output ---
  Serial.print("Pitch: ");
  Serial.print(pitch_filtered);
  Serial.print(" | Stable: ");
  Serial.println(stable);

  delay(100);
}