# Video for Hardware connection: [click here](https://www.youtube.com/watch?v=-rpoWodHIfU)

- [another setup](https://www.youtube.com/watch?v=H9e1Up7xHjc&t=116s)


# MPU6050 with ESP32 Setup Documentation

## Smart Posture Detection Wearable — Phase 1

---

# 1. Introduction

The MPU6050 is the motion sensing unit used in the Smart Posture Detection Wearable system.

It is responsible for detecting:

* tilt,
* movement,
* orientation,
* and posture angle.

The MPU6050 communicates with the ESP32 using the I2C protocol and continuously sends acceleration data to the ESP32 for posture analysis.

---

# 2. About MPU6050

The MPU6050 is a 6-axis motion tracking sensor containing:

| Sensor Type   | Function                       |
| ------------- | ------------------------------ |
| Accelerometer | Measures tilt and acceleration |
| Gyroscope     | Measures rotational motion     |

For the initial posture detection prototype, only accelerometer data is primarily used.

---

# 3. MPU6050 Module Used

The module commonly used is:

```text id="jlwmpr"
GY-521 MPU6050 Module
```

Typical module:

![Image](https://images.openai.com/static-rsc-4/7Qb7W5QvufCytb36Kz2oRbLnBkL4M2cQ5bdWLAstldgi5tNsDuQ5Gsn-p2q-Kb2gUf3kWgwSUDpHygQ-WvMRq_y1l62eP6g6knKfPH-rB-8gFYzZllpKEUcD7y5wHLkM4dj0fMrP_SHBgN1b6RBFZR8H_beM4rF-Y27NaegZ2_ozQOW-TaxeMoMNAYAL55ib?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/DfUUk03sN22u8bV8i8vZ3Mz7Sv6GpiuhTPr0iT1mNLjPgYNYQq5gqAD2Kj6CmdkPvYm8xLOTafaH4WIJudIKKA7ELPqKQVsihl-y4bhJPRRNVvSqFNL3whJc_WlU37Q1KObEdsw61olAxZTXVQvFD2R08heRmOd5GErNYNrcW4WQHlrjefDTDM6Ou-ZAAzJd?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/xeBetT9MWqykjNPCN5qo1TKCk5hZxlxUXQ3USjVALrou5ugIZXdVlBzjrrIZvrYtMF8eEZBGnepITzlEP1w2GLzmpjOzekYaFiM79bDrk-ZCyMMFQmPwffhS4uuFi5zDllL0ML7F8Tqyac-pKmeXSQyj2-GKPkQKLY8oTtw-AMmjT4uA3VNECIZj3oKTCB_k?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/pZp5PYpVg3M1IQFHjmig1RriScIK_L8kGzUD3jHSuIBfVedz8OpQAgQht78zWz7sAdkwwM368RoUS_L1ivG6g6i6UkwaAFsQDB402vv6lHolT6NRC__Mqjk_PYRafS03pZBGAFARccaqI7DzANd-qbDGc9ji3HmWF2KQg2DVPQXTyasjEmx8o1T0217LfHva?purpose=fullsize)

---

# 4. Required Components

| Component       | Purpose                 |
| --------------- | ----------------------- |
| ESP32 DevKit V1 | Main controller         |
| MPU6050 Module  | Motion sensing          |
| Breadboard      | Temporary circuit setup |
| Jumper Wires    | Connections             |
| USB Data Cable  | Power and programming   |
| Laptop          | Coding and monitoring   |

---

# 5. MPU6050 Pin Description

| MPU6050 Pin | Function       |
| ----------- | -------------- |
| VCC         | Power supply   |
| GND         | Ground         |
| SDA         | I2C Data line  |
| SCL         | I2C Clock line |

Additional pins such as:

* XDA
* XCL
* AD0
* INT

are not used in this phase.

---

# 6. Understanding I2C Communication

The MPU6050 communicates with ESP32 using I2C.

I2C uses only two communication lines:

| Signal | Function              |
| ------ | --------------------- |
| SDA    | Data communication    |
| SCL    | Clock synchronization |

---

# ESP32 Default I2C Pins

| Function | ESP32 GPIO |
| -------- | ---------- |
| SDA      | GPIO 21    |
| SCL      | GPIO 22    |

These pins are used to communicate with the MPU6050.

---

# 7. Hardware Connection Setup

---

# Step 1 — Place ESP32 on Breadboard

The ESP32 should be placed across the center gap of the breadboard.

This keeps both sides of GPIO pins accessible.

---

# Step 2 — Create Power Rails

Connect ESP32 power pins to breadboard rails.

| ESP32 Pin | Breadboard Rail   |
| --------- | ----------------- |
| 3.3V      | Positive (+) rail |
| GND       | Negative (-) rail |

This distributes power to connected modules.

---

# Step 3 — Connect MPU6050 to ESP32

# Connection Table

| MPU6050 | ESP32   |
| ------- | ------- |
| VCC     | 3.3V    |
| GND     | GND     |
| SDA     | GPIO 21 |
| SCL     | GPIO 22 |

---

# Actual Wiring Flow

## Power Connection

```text id="jlwm0v"
ESP32 3.3V
   ↓
Breadboard + Rail
   ↓
MPU6050 VCC
```

---

## Ground Connection

```text id="jlwmx5"
ESP32 GND
   ↓
Breadboard - Rail
   ↓
MPU6050 GND
```

---

## Communication Connection

```text id="jlwm1j"
ESP32 GPIO21 → MPU6050 SDA
ESP32 GPIO22 → MPU6050 SCL
```

---

# Important Precautions

| Precaution             | Reason                                   |
| ---------------------- | ---------------------------------------- |
| Use 3.3V power         | ESP32 logic operates at 3.3V             |
| Maintain common ground | Required for stable communication        |
| Avoid loose wires      | Prevents connection failure              |
| Verify SDA/SCL wiring  | Wrong wiring causes communication errors |

---

# 8. Connecting ESP32 to Laptop

The ESP32 is connected to the laptop using a USB data cable.

Connection structure:

```text id="jlwmx3"
Laptop
   ↓
USB Data Cable
   ↓
ESP32
```

The USB connection provides:

* power supply,
* serial communication,
* and program uploading.

---

# Important USB Requirement

The USB cable must support:

```text id="jlwmgg"
Data Transfer
```

and not only charging.

Charge-only cables may power the ESP32 but prevent code uploading.

---

# 9. Installing Arduino IDE

The Arduino IDE is required to upload programs to ESP32.

Download:

[Arduino IDE Official Website](https://www.arduino.cc/en/software?utm_source=chatgpt.com)

Install and open the IDE.

---

# 10. Installing ESP32 Board Package

---

# Step 1 — Open Preferences

Go to:

```text id="jlwm0f"
File → Preferences
```

---

# Step 2 — Add ESP32 Board URL

Inside:

```text id="jlwmrz"
Additional Boards Manager URLs
```

paste:

```text id="jlwmad"
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

Click:

```text id="jlwm6p"
OK
```

---

# Step 3 — Install ESP32 Boards

Go to:

```text id="jlwmf6"
Tools → Board → Boards Manager
```

Search:

```text id="jlwmr4"
ESP32
```

Install:

```text id="jlwmqv"
ESP32 by Espressif Systems
```

---

# 11. Selecting Correct ESP32 Board

Go to:

```text id="jlwmw7"
Tools → Board
```

Select:

```text id="jlwm8l"
ESP32 Dev Module
```

---

# 12. Selecting COM Port

Go to:

```text id="jlwmqt"
Tools → Port
```

Select the COM port detected after connecting ESP32.

Example:

```text id="jlwm6v"
COM5
```

---

# 13. Installing MPU6050 Library

Open Arduino IDE.

Go to:

```text id="jlwmk5"
Sketch → Include Library → Manage Libraries
```

Search:

```text id="jlwm9u"
MPU6050
```

Install:

```text id="jlwmc4"
MPU6050 by Electronic Cats
```

or equivalent compatible library.

---

# 14. MPU6050 Connection Test Program

The following program checks whether the MPU6050 is successfully communicating with the ESP32.

```cpp
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {

  Serial.begin(115200);

  Wire.begin(21,22);

  mpu.initialize();

  if (mpu.testConnection()) {

    Serial.println("MPU6050 Connected");
  }
  else {

    Serial.println("Connection Failed");
  }
}

void loop() {

}
```

---

# 15. Code Explanation

| Code                 | Purpose                  |
| -------------------- | ------------------------ |
| Wire.begin(21,22)    | Starts I2C communication |
| mpu.initialize()     | Initializes sensor       |
| mpu.testConnection() | Verifies communication   |
| Serial.begin(115200) | Starts serial monitor    |

---

# 16. Uploading Code to ESP32

Steps:

1. Click:

```text id="jlwm8r"
✔ Verify
```

to compile.

2. Click:

```text id="jlwmm7"
→ Upload
```

to upload code.

---

# BOOT Button Issue

If upload fails:

1. Hold:

```text id="jlwm01"
BOOT
```

button on ESP32.

2. Release after upload starts.

This forces ESP32 into flashing mode.

---

# 17. Opening Serial Monitor

Go to:

```text id="jlwmv8"
Tools → Serial Monitor
```

Set baud rate to:

```text id="jlwmkk"
115200
```

---

# Expected Output

```text id="jlwm4g"
MPU6050 Connected
```

This confirms:

* correct wiring,
* successful I2C communication,
* proper sensor operation.

---

# 18. Reading Live Sensor Values

The MPU6050 can now send live acceleration values.

Example program:

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

# 19. Sensor Testing Procedure

After uploading:

1. Open Serial Monitor.
2. Observe acceleration values.
3. Tilt the MPU6050 physically.

Expected behavior:

* X, Y, and Z values change continuously with movement.

This confirms successful motion sensing.

---

# 20. Common Problems and Solutions

| Problem            | Cause                    | Solution                 |
| ------------------ | ------------------------ | ------------------------ |
| Connection Failed  | Wrong SDA/SCL wiring     | Verify GPIO21 and GPIO22 |
| No sensor response | Loose wires              | Reconnect properly       |
| Upload failed      | Flash mode issue         | Hold BOOT button         |
| No COM port        | Bad USB cable            | Use data cable           |
| Random values      | Unstable sensor movement | Keep sensor steady       |

---

# 21. Final Result

After successful setup:

* ESP32 reads MPU6050 data,
* acceleration values appear in Serial Monitor,
* tilt and motion can be detected in real time.

This confirms that the motion sensing subsystem of the Smart Posture Detection Wearable is functioning correctly.
