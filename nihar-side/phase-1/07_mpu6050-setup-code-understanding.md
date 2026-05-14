# MPU6050 Code Explanation Documentation

## Smart Posture Detection Wearable — Phase 1

---

# 1. Purpose of the MPU6050 Code

The MPU6050 code is responsible for:

* establishing communication between ESP32 and MPU6050,
* reading accelerometer values,
* processing motion data,
* and sending tilt information to the system.

The sensor continuously measures movement and orientation changes.

These values are later used to determine posture status.

---

# 2. Complete MPU6050 Test Code

```cpp
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int16_t ax, ay, az;

void setup() {

  Serial.begin(115200);

  Wire.begin(21,22);

  mpu.initialize();
}

void loop() {

  mpu.getAcceleration(&ax, &ay, &az);

  Serial.print("X: ");
  Serial.print(ax);

  Serial.print(" Y: ");
  Serial.print(ay);

  Serial.print(" Z: ");
  Serial.println(az);

  delay(500);
}
```

---

# 3. Understanding the Code Step-by-Step

---

# 3.1 Including Required Libraries

```cpp
#include <Wire.h>
#include <MPU6050.h>
```

---

## Wire.h

This library enables:

# I2C communication

The MPU6050 communicates with ESP32 using I2C protocol.

Without this library:
ESP32 cannot talk to the sensor.

---

## MPU6050.h

This is the sensor library.

It provides built-in functions like:

| Function          | Purpose                    |
| ----------------- | -------------------------- |
| initialize()      | Starts sensor              |
| getAcceleration() | Reads accelerometer values |
| testConnection()  | Checks sensor connection   |

This simplifies communication with the MPU6050.

---

# 3.2 Creating MPU6050 Object

```cpp
MPU6050 mpu;
```

This creates a sensor object named:

```text id="jlwmv6"
mpu
```

The object acts as the software representation of the physical MPU6050 module.

All sensor functions are accessed through this object.

Example:

```cpp
mpu.initialize();
```

---

# 3.3 Creating Accelerometer Variables

```cpp
int16_t ax, ay, az;
```

These variables store acceleration values.

| Variable | Axis                |
| -------- | ------------------- |
| ax       | X-axis acceleration |
| ay       | Y-axis acceleration |
| az       | Z-axis acceleration |

---

# WHY int16_t?

The MPU6050 returns:

# 16-bit signed integer values

Range:

```text id="jlwmzu"
-32768 to +32767
```

This allows both:

* positive movement,
* and negative movement.

---

# 4. Understanding setup()

```cpp
void setup()
```

The setup() function runs:

# only once

when ESP32 powers ON or resets.

It is used for:

* initialization,
* communication setup,
* sensor startup.

---

# 4.1 Serial Communication

```cpp
Serial.begin(115200);
```

This starts serial communication between:

```text id="jlwm09"
ESP32 ↔ Laptop
```

The baud rate is:

```text id="jlwmzm"
115200
```

---

# Purpose

Used for:

* debugging,
* viewing sensor values,
* monitoring outputs.

The data appears inside:

```text id="jlwmwo"
Serial Monitor
```

in Arduino IDE.

---

# IMPORTANT

Serial Monitor baud rate MUST match:

```cpp
Serial.begin(115200);
```

Otherwise:
random unreadable symbols appear.

---

# 4.2 Starting I2C Communication

```cpp
Wire.begin(21,22);
```

This initializes I2C communication.

---

# Pin Meaning

| Parameter | GPIO |
| --------- | ---- |
| 21        | SDA  |
| 22        | SCL  |

---

# SDA (Data Line)

Transfers actual sensor data.

---

# SCL (Clock Line)

Synchronizes communication timing.

---

# Communication Flow

```text id="jlwmwe"
ESP32 GPIO21 → MPU6050 SDA
ESP32 GPIO22 → MPU6050 SCL
```

---

# IMPORTANT THINGS TO TAKE CARE OF

| Mistake         | Result              |
| --------------- | ------------------- |
| SDA/SCL swapped | Sensor not detected |
| Loose wires     | Random failures     |
| Wrong GPIO pins | No communication    |

---

# 4.3 Initializing MPU6050

```cpp
mpu.initialize();
```

This powers up and configures the MPU6050 internally.

The sensor becomes ready to send data.

Without this:
sensor remains inactive.

---

# 5. Understanding loop()

```cpp
void loop()
```

The loop() function runs:

# continuously forever

after setup() finishes.

This creates continuous live sensor monitoring.

---

# 5.1 Reading Acceleration Data

```cpp
mpu.getAcceleration(&ax, &ay, &az);
```

This reads acceleration values from the sensor.

---

# IMPORTANT CONCEPT — "&" Symbol

The "&" symbol means:

# memory address

The function directly fills values into:

* ax
* ay
* az

variables.

---

# HOW SENSOR VALUES WORK

The MPU6050 detects gravity direction.

When sensor tilts:
gravity distribution changes.

This changes:

* X acceleration,
* Y acceleration,
* Z acceleration.

---

# Example

Flat sensor:

```text id="jlwmhl"
X ≈ 0
Y ≈ 0
Z ≈ 16000
```

Tilted sensor:

```text id="jlwmng"
X ≈ 7000
Y ≈ -3000
Z ≈ 12000
```

---

# 5.2 Printing Values

```cpp
Serial.print("X: ");
Serial.print(ax);
```

Prints X-axis value.

---

# Then:

```cpp
Serial.print(" Y: ");
Serial.print(ay);
```

Prints Y-axis value.

---

# Finally:

```cpp
Serial.print(" Z: ");
Serial.println(az);
```

Prints Z-axis value.

---

# Difference Between print() and println()

| Function  | Behavior  |
| --------- | --------- |
| print()   | Same line |
| println() | Next line |

---

# Example Output

```text id="jlwm3w"
X: 1200 Y: -300 Z: 16000
```

---

# 5.3 Delay

```cpp
delay(500);
```

Pauses program for:

```text id="jlwm5r"
500 milliseconds
```

or:

```text id="jlwmw4"
0.5 seconds
```

---

# WHY DELAY IS USED

Without delay:
Serial Monitor floods too quickly.

Delay makes readings human-readable.

---

# 6. How Posture Detection Works

The MPU6050 measures orientation changes.

When body bends:

* acceleration distribution changes,
* tilt angle changes.

ESP32 uses these values to estimate posture.

---

# Example Logic

```cpp
if(angle > 20)
```

then:

```text id="jlwm6l"
SLOUCH
```

Else:

```text id="jlwmf0"
GOOD
```

---

# 7. Major Things to Take Care Of

---

# 7.1 Correct Power Supply

Use:

```text id="jlwmrt"
3.3V
```

NOT 5V.

Wrong voltage may cause unstable behavior.

---

# 7.2 Common Ground

ESP32 GND and MPU6050 GND must connect together.

Without common ground:
communication fails.

---

# 7.3 Correct I2C Wiring

| ESP32  | MPU6050 |
| ------ | ------- |
| GPIO21 | SDA     |
| GPIO22 | SCL     |

---

# 7.4 Stable Connections

Loose jumper wires cause:

* random disconnects,
* corrupted readings,
* upload issues.

---

# 7.5 Sensor Stability

The MPU6050 is highly sensitive.

Keep it:

* steady,
* flat,
* vibration-free

during testing.

---

# 7.6 Avoid Wire Confusion

Always:

* use organized wiring,
* avoid crossing wires excessively,
* use short jumper wires.

---

# 7.7 USB Cable Quality

Poor USB cables cause:

* random disconnections,
* failed uploads,
* unstable power.

Use proper data cable.

---

# 8. Final Working Principle

Overall system operation:

```text id="jlwmxm"
Body movement
      ↓
MPU6050 senses tilt
      ↓
Acceleration values generated
      ↓
ESP32 reads values using I2C
      ↓
Data processed
      ↓
Posture determined
```

---

# 9. Final Result

After successful execution:

* ESP32 continuously receives MPU6050 data,
* acceleration values update in real time,
* posture movement becomes measurable,
* and the system becomes ready for posture analysis and OLED output display.
