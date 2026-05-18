# 1. What the MPU6050 Actually Is (Core Understanding)

The **MPU6050** is a **6-DoF IMU (Inertial Measurement Unit)**:

* **Accelerometer (3-axis)** → measures linear acceleration (gravity included)
* **Gyroscope (3-axis)** → measures angular velocity (rotation)

### Internal Blocks

* MEMS sensors (tiny mechanical structures)
* ADC (converts analog → digital)
* DMP (Digital Motion Processor) → does sensor fusion internally
* I2C interface → communicates with microcontrollers like **ESP32**

---

# 2. Why Use MPU6050 with ESP32?

ESP32 advantages:

* Fast dual-core CPU
* Built-in WiFi + BLE
* Hardware I2C
* Good for real-time sensor fusion

MPU6050 advantages:

* Cheap
* Reliable
* Widely supported
* Good enough for most motion tracking

# 3. Wiring (Hardware Layer)

### MPU6050 Pins

| MPU6050 | ESP32                    |
| ------- | ------------------------ |
| VCC     | 3.3V                     |
| GND     | GND                      |
| SDA     | GPIO 21                  |
| SCL     | GPIO 22                  |
| AD0     | GND (0x68) / VCC (0x69)  |
| INT     | Optional (interrupt pin) |

⚠️ Important:

* ESP32 is **3.3V logic** → safe for MPU6050
* Use pull-up resistors (often already on module)

---

# 4. Communication Protocol (I2C Deep Dive)

MPU6050 uses **I2C**

### Key Concepts:

* Master = ESP32
* Slave = MPU6050
* Address = `0x68` or `0x69`

### Registers

MPU6050 is register-based:

* `0x6B` → Power management
* `0x3B` → Accelerometer data
* `0x43` → Gyroscope data

---

# 5. First Principle: Raw Data Format

Each axis = **16-bit signed integer**

### Accelerometer

* Range: ±2g, ±4g, ±8g, ±16g
* Default: ±2g
* Scale:

  ```
  accel_g = raw / 16384.0
  ```

### Gyroscope

* Range: ±250°/s, ±500°/s, ±1000°/s, ±2000°/s
* Default: ±250
* Scale:

  ```
  gyro_dps = raw / 131.0
  ```

# 6. ESP32 Code (Minimal but Real)

Using Arduino framework:

```cpp
#include <Wire.h>

#define MPU_ADDR 0x68

int16_t accelX, accelY, accelZ;
int16_t gyroX, gyroY, gyroZ;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);

  accelX = Wire.read() << 8 | Wire.read();
  accelY = Wire.read() << 8 | Wire.read();
  accelZ = Wire.read() << 8 | Wire.read();

  Wire.read(); Wire.read(); // skip temp

  gyroX = Wire.read() << 8 | Wire.read();
  gyroY = Wire.read() << 8 | Wire.read();
  gyroZ = Wire.read() << 8 | Wire.read();

  Serial.println(accelX);
  delay(500);
}
```

# 7. The Real Problem: Raw Data is Useless Alone

### Issues:

* Accelerometer → noisy
* Gyroscope → drifts over time

👉 You need **sensor fusion**

# 8. Sensor Fusion (Core Skill)

### Options:

#### 1. Complementary Filter (Best to Start)

```
angle = 0.98 * (angle + gyro * dt) + 0.02 * accel_angle
```

#### 2. Kalman Filter (Advanced)

* More accurate
* More complex

#### 3. DMP (Built-in processor)

* Offloads computation
* Gives quaternions


# 9. Orientation Calculation

### From Accelerometer:

```
pitch = atan2(accelY, accelZ)
roll  = atan2(-accelX, sqrt(accelY^2 + accelZ^2))
```

### From Gyroscope:

```
angle += gyro * dt
```

Combine both → stable orientation

---

# 10. Calibration (CRITICAL)

If you skip this → garbage data.

### Gyro Calibration

* Keep sensor still
* Average 1000 readings
* Subtract offset

### Accelerometer Calibration

* Ensure Z ≈ 1g when flat
* Adjust offsets

---

# 11. Noise & Filtering

Techniques:

* Moving average
* Low-pass filter
* Complementary filter

---

# 12. Interrupts (Advanced)

MPU6050 can:

* Detect motion
* Trigger interrupt pin

Useful for:

* Power saving
* Event-based systems

---

# 13. Using Libraries (Production Approach)

Instead of raw I2C:

### Popular libraries:

* `Wire.h` (basic)
* `MPU6050.h` (Jeff Rowberg)
* DMP-enabled libraries

# 15. Performance Tips (ESP32 Specific)

* Use **hardware I2C**
* Increase I2C clock:

  ```cpp
  Wire.setClock(400000);
  ```
* Use **FreeRTOS tasks** for real-time loops
* Avoid delay → use timers

---

# 16. Common Mistakes (Avoid These)

* ❌ Not waking MPU6050 (`0x6B`)
* ❌ No calibration
* ❌ Using only accelerometer
* ❌ Ignoring drift
* ❌ Wrong scaling factors
* ❌ Loose wiring (causes noise)
