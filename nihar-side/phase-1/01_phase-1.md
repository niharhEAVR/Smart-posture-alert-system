# PHASE 1 = Hardware + Basic Firmware (Code)

This phase is basically:

> “Can our device successfully detect posture?”

If yes → your project foundation is complete.

---

# WHAT YOUR FINAL PHASE 1 SHOULD DO

By tomorrow evening, ideally your system should:

```text
MPU6050 senses tilt
        ↓
ESP32 reads values
        ↓
ESP32 calculates posture angle
        ↓
OLED shows:
GOOD POSTURE
or
SLOUCHING
```

That alone is already a huge achievement.

---

# FULL ROADMAP OF PHASE 1

# STEP 0 — Understand the System Architecture

Before touching wires, understand the flow.

```text
MPU6050  →  ESP32  →  OLED Display
               ↓
         Future:
      Vibration Motor
      Calibration Button
      Bluetooth/WiFi
```

For tomorrow:

ONLY THESE THREE MATTER:

* ESP32
* MPU6050
* OLED

Ignore:

* battery
* charging module
* enclosure
* straps
* vibration motor

for now.

---

# STEP 1 — Install Required Software

You need:

## 1. Arduino IDE

Download:
[Arduino IDE](https://www.arduino.cc/en/software?utm_source=chatgpt.com)

Install it.

---

# STEP 2 — Add ESP32 Board in Arduino IDE

This is VERY IMPORTANT.

Without this:
Arduino IDE cannot upload code to ESP32.

---

## In Arduino IDE:

### Go to:

```text
File → Preferences
```

In:

```text
Additional Board Manager URLs
```

paste:

```text
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

Then:

```text
Tools → Board → Boards Manager
```

Search:

```text
ESP32
```

Install:

```text
ESP32 by Espressif Systems
```

---

# STEP 3 — Connect ESP32 to Laptop

Use USB cable.

IMPORTANT:

Some USB cables are charging-only.

If ESP32 does not appear:

* try another cable.

---

# STEP 4 — Select Correct Board and COM Port

Go to:

```text
Tools → Board
```

Select:

```text
ESP32 Dev Module
```

Then:

```text
Tools → Port
```

Choose COM port.

Example:

```text
COM5
```

---

# STEP 5 — TEST ESP32 FIRST

Before connecting sensors.

Upload basic blink code.

```cpp
void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(1000);

  digitalWrite(2, LOW);
  delay(1000);
}
```

If onboard LED blinks:

✅ ESP32 working.

---

# STEP 6 — Understand I2C Communication

VERY IMPORTANT CONCEPT.

Both:

* MPU6050
* OLED

use:

# I2C Communication

Meaning:
they communicate using only 2 wires:

```text
SDA → Data
SCL → Clock
```

Good news:

ESP32 can connect BOTH devices on SAME SDA/SCL lines.

---

# STEP 7 — ESP32 Pin Understanding

For ESP32:

Default I2C pins are:

```text
SDA → GPIO 21
SCL → GPIO 22
```

Remember this forever.

---

# STEP 8 — Connect MPU6050

# MPU6050 Pins

Usually:

```text
VCC
GND
SCL
SDA
```

---

# Wiring

| MPU6050 | ESP32   |
| ------- | ------- |
| VCC     | 3.3V    |
| GND     | GND     |
| SDA     | GPIO 21 |
| SCL     | GPIO 22 |

---

# IMPORTANT WARNING

DO NOT connect MPU6050 VCC to 5V.

Use:

```text
3.3V
```

because ESP32 logic is 3.3V.

---

# STEP 9 — Install MPU6050 Library

Go to:

```text
Sketch → Include Library → Manage Libraries
```

Search:

```text
MPU6050
```

Install:

* MPU6050 by Electronic Cats
  OR
* Adafruit MPU6050

Either works.

---

# STEP 10 — Test MPU6050 Sensor

Upload test code.

Example:

```cpp
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);

  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 Connected");
  } else {
    Serial.println("Connection Failed");
  }
}

void loop() {
}
```

---

# STEP 11 — Open Serial Monitor

Go to:

```text
Tools → Serial Monitor
```

Set baud rate:

```text
115200
```

You should see:

```text
MPU6050 Connected
```

If yes:

✅ sensor working.

---

# STEP 12 — Read Real Sensor Values

Now upload code to read accelerometer data.

Example output:

```text
X: 1200
Y: -340
Z: 16000
```

When you tilt sensor:
values change.

That means:

✅ posture sensing is possible.

---

# STEP 13 — Connect OLED Display

Now connect OLED.

---

# OLED Pins

Usually:

```text
VCC
GND
SCL
SDA
```

---

# Wiring

| OLED | ESP32   |
| ---- | ------- |
| VCC  | 3.3V    |
| GND  | GND     |
| SDA  | GPIO 21 |
| SCL  | GPIO 22 |

---

# IMPORTANT THING

You can connect BOTH:

* MPU6050
* OLED

to SAME:

* SDA
* SCL

because I2C supports multiple devices.

---

# STEP 14 — Install OLED Libraries

Install:

## Adafruit SSD1306

## Adafruit GFX

from library manager.

---

# STEP 15 — OLED Test

Upload OLED test code.

Display:

```text
HELLO
POSTURE SYSTEM
```

If screen shows text:

✅ OLED working.

---

# STEP 16 — Basic Posture Detection Logic

NOW THE REAL PROJECT STARTS.

You will calculate tilt angle.

The MPU6050 gives:

* acceleration values.

Using math,
you estimate body tilt.

---

# Simple Logic

If body bends too much:

```text
SLOUCHING
```

Else:

```text
GOOD POSTURE
```

---

# Basic Beginner Logic

You can initially use:

```cpp
if(accelX > threshold)
```

or

```cpp
if(angle > 20 degrees)
```

then:

```text
SLOUCHING
```

---

# WHAT YOU SHOULD COMPLETE TOMORROW

# MINIMUM SUCCESS TARGET

## Hardware

✅ ESP32 powers on
✅ MPU6050 connected
✅ OLED connected

---

## Software

✅ Arduino IDE setup
✅ ESP32 code upload works
✅ Sensor values visible
✅ OLED text visible
✅ Simple posture detection working

---

# WHAT TO IGNORE TOMORROW

DO NOT waste time on:

❌ battery
❌ enclosure
❌ straps
❌ TP4056
❌ wearable design
❌ mobile app
❌ Bluetooth
❌ WiFi dashboard

Those are later phases.

---

# PHASE 1 FINAL DEMO

By end of Phase 1:

When you bend:

```text
OLED → SLOUCHING
```

When straight:

```text
OLED → GOOD POSTURE
```

That is your first milestone.

---

# WHAT COMES AFTER PHASE 1

# PHASE 2

Add:

* vibration motor
* calibration button

---

# PHASE 3

Make it wearable:

* battery
* charging
* enclosure

---

# PHASE 4

Advanced features:

* Bluetooth
* mobile app
* posture history
* analytics

---

# MOST IMPORTANT ADVICE

Tomorrow:
DO NOT try to build the whole final product.

Your ONLY goal:

```text
Sensor reading + OLED output
```

If that works,
your entire project foundation becomes stable.
