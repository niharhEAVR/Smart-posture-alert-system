# 🔹 What changes with Sensor Fusion?

Right now, your ESP32 likely uses:

* Accelerometer → gives tilt (but noisy when moving)
* Gyroscope → gives rotation speed (but drifts over time)

👉 Individually:

* Accelerometer = stable but jittery
* Gyroscope = smooth but drifts

👉 Sensor fusion combines them to get:

* Stable + smooth + accurate orientation


## 🔧 Simplest Fusion: Complementary Filter

This is the best balance of:

* Easy to implement
* Good enough for posture detection
* Runs fast on ESP32

### Formula:

```cpp
angle = α * (angle + gyro * dt) + (1 - α) * accel_angle;
```

Where:

* `α ≈ 0.98` (trust gyro more)
* `dt = time between readings`


# 🔹 Code Changes (Core Logic Only)

### 1. Add variables (top of file)

```cpp
float pitch = 0;
float roll = 0;

float alpha = 0.98;
unsigned long prevTime = 0;
```


### 2. Convert raw sensor → angles

Inside `loop()`:

```cpp
unsigned long currentTime = millis();
float dt = (currentTime - prevTime) / 1000.0;
prevTime = currentTime;
```


### 3. Read sensor (example MPU6050-style)

```cpp
float accX = ax;
float accY = ay;
float accZ = az;

float gyroX = gx;
float gyroY = gy;
```


### 4. Calculate accelerometer angles

```cpp
float accelPitch = atan2(accY, accZ) * 180 / PI;
float accelRoll  = atan2(-accX, sqrt(accY * accY + accZ * accZ)) * 180 / PI;
```


### 5. Apply complementary filter

```cpp
pitch = alpha * (pitch + gyroX * dt) + (1 - alpha) * accelPitch;
roll  = alpha * (roll  + gyroY * dt) + (1 - alpha) * accelRoll;
```


### 6. Use this for posture detection

```cpp
if (abs(pitch) > 20) {
  Serial.println("SLOUCHING");
} else {
  Serial.println("CORRECT");
}
```


# 🔹 Web Button for Calibration (Very Smart Idea)

Yes — this is exactly how real IoT systems work.

We’ll:

* Host a web page on ESP32
* Add a **"Calibrate" button**
* Store current posture as baseline


## 🔧 Add calibration variables

```cpp
float pitchOffset = 0;
float rollOffset = 0;
```


## 🔧 Calibration function

```cpp
void calibratePosture() {
  pitchOffset = pitch;
  rollOffset = roll;
}
```


## 🔧 Adjust posture logic

```cpp
float adjustedPitch = pitch - pitchOffset;

if (abs(adjustedPitch) > 15) {
  Serial.println("SLOUCHING");
} else {
  Serial.println("CORRECT");
}
```


# 🔹 Add Web Server Button

### Include:

```cpp
#include <WebServer.h>
WebServer server(80);
```


### Route for calibration

```cpp
void handleCalibrate() {
  calibratePosture();
  server.send(200, "text/plain", "Calibrated!");
}
```


### Simple Web Page

```cpp
void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Posture Device</h1>";
  html += "<button onclick=\"fetch('/calibrate')\">Calibrate</button>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}
```


### Setup server

Inside `setup()`:

```cpp
server.on("/", handleRoot);
server.on("/calibrate", handleCalibrate);
server.begin();
```


### Loop

```cpp
server.handleClient();
```



# 🔹 Next Level

If you want to push this toward something serious:

1. Add:

   * Data logging to server (history tracking)
2. Add:

   * Threshold learning (basic AI)
3. Add:

   * BLE app instead of web UI (mobile friendly)
4. Upgrade filter:

   * Kalman Filter (more advanced than complementary)