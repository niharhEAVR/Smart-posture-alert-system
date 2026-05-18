# 🧩 STEP 1: Hardware Connection (MPU6050 ↔ ESP32)

### Wiring

| MPU6050 | ESP32                |
| ------- | -------------------- |
| VCC     | 3.3V                 |
| GND     | GND                  |
| SDA     | GPIO 21              |
| SCL     | GPIO 22              |
| AD0     | GND (address = 0x68) |

👉 Keep it simple for now:

* Leave INT pin unconnected
* Use short wires (noise matters)

# ⚙️ STEP 2: Arduino IDE Setup

### Install ESP32 support

1. Go to Preferences
2. Add:

```
https://dl.espressif.com/dl/package_esp32_index.json
```

3. Board Manager → install **ESP32**

### Select board:

* “ESP32 Dev Module”

# 🧪 STEP 3: First Test — Is Device Detected?

Confirm I2C works.

```cpp
#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin(); // SDA=21, SCL=22

  Serial.println("Scanning...");
  
  for (byte i = 1; i < 127; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at: 0x");
      Serial.println(i, HEX);
    }
  }
}

void loop() {}
```

### Expected output:

```
Found device at: 0x68
```

👉 If not:

* Check wiring
* Try `Wire.begin(21, 22);`

# 🔌 STEP 4: Wake Up the MPU6050

By default, it is **asleep**.

```cpp
void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Wake up MPU6050
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);  // Power management register
  Wire.write(0);     // Wake up
  Wire.endTransmission(true);

  Serial.println("MPU6050 Ready");
}
```


# 📥 STEP 5: Read Raw Sensor Data

Now we read all 6 axes.

```cpp
int16_t ax, ay, az;
int16_t gx, gy, gz;

void readMPU() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B); // starting register
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 14, true);

  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();

  Wire.read(); Wire.read(); // skip temp

  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();
}
```


# 📊 STEP 6: Print Raw Values

```cpp
void loop() {
  readMPU();

  Serial.print("AX: "); Serial.print(ax);
  Serial.print(" AY: "); Serial.print(ay);
  Serial.print(" AZ: "); Serial.print(az);

  Serial.print(" | GX: "); Serial.print(gx);
  Serial.print(" GY: "); Serial.print(gy);
  Serial.print(" GZ: "); Serial.println(gz);

  delay(500);
}
```


# 🔍 What You Should See

When sensor is flat:

* `az ≈ +16384`
* `ax ≈ 0`
* `ay ≈ 0`

Tilt it:

* Values shift depending on orientation

👉 This confirms:

* Sensor works
* Data is real

# 🧠 STEP 7: Convert to Meaningful Values

Add this inside loop:

```cpp
float ax_g = ax / 16384.0;
float ay_g = ay / 16384.0;
float az_g = az / 16384.0;

Serial.print(" | ax_g: "); Serial.print(ax_g);
Serial.print(" ay_g: "); Serial.print(ay_g);
Serial.print(" az_g: "); Serial.println(az_g);
```

# 🎯 STEP 8: Get Your First Angle (Pitch)

Now the important part:

```cpp
float pitch = atan2(ax_g, sqrt(ay_g * ay_g + az_g * az_g)) * 180 / PI;

Serial.print("Pitch: ");
Serial.println(pitch);
```

# 🧪 What You Should Observe

| Position      | Pitch        |
| ------------- | ------------ |
| Upright       | ~0°          |
| Lean forward  | +10° to +40° |
| Lean backward | negative     |

👉 THIS is your posture signal.


# ⚠️ Common Beginner Problems

### ❌ Garbage values

* Forgot wake-up step

### ❌ No device found

* Wrong wiring / wrong pins

### ❌ Constant zero

* I2C not initialized properly

### ❌ Flipping angles

* Sensor orientation mismatch (normal)