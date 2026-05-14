# ESP32 Programming Basics Documentation

## Understanding How ESP32 Code Works

---

# 1. What is ESP32 Programming?

Programming the ESP32 means:

```text id="6lttn9"
Giving instructions to the ESP32
```

so it can:

* read sensors,
* control devices,
* process data,
* and perform actions automatically.

The code you write is uploaded from the laptop into the ESP32 memory.

After uploading:
the ESP32 runs that program independently.

---

# 2. ESP32 Program Structure

Almost every ESP32 Arduino program follows this structure:

```cpp id="r0n8g8"
void setup() {

}

void loop() {

}
```

These are the two most important parts of ESP32 programming.

---

# 3. Understanding setup()

```cpp id="0xyb5h"
void setup()
```

The setup() function runs:

# ONLY ONCE

when:

* ESP32 powers ON,
* or resets.

---

# Purpose of setup()

Used for:

* starting communication,
* initializing sensors,
* setting pin modes,
* starting displays,
* configuring hardware.

---

# Example

```cpp id="lxan9t"
void setup() {

  Serial.begin(115200);

  pinMode(2, OUTPUT);
}
```

---

# What Happens Here?

---

## 1.

```cpp id="wo2fjg"
Serial.begin(115200);
```

Starts communication between:

```text id="z26s84"
ESP32 ↔ Laptop
```

Used for:

* debugging,
* printing values,
* monitoring outputs.

---

## 2.

```cpp id="o5r5jo"
pinMode(2, OUTPUT);
```

Configures GPIO 2 as:

```text id="u9t0v2"
OUTPUT
```

Meaning:
ESP32 can send voltage through this pin.

---

# 4. Understanding loop()

```cpp id="6h6d97"
void loop()
```

The loop() function runs:

# FOREVER

continuously.

---

# Purpose of loop()

Used for:

* reading sensors repeatedly,
* updating displays,
* checking conditions,
* controlling outputs continuously.

---

# Example

```cpp id="30v75l"
void loop() {

  digitalWrite(2, HIGH);

  delay(1000);

  digitalWrite(2, LOW);

  delay(1000);
}
```

---

# What Happens?

---

## Step 1

```cpp id="9tt1qb"
digitalWrite(2, HIGH);
```

Turns GPIO 2 ON.

Voltage becomes:

```text id="ol4v3w"
3.3V
```

---

## Step 2

```cpp id="vq7kx6"
delay(1000);
```

Waits:

```text id="cy4xkn"
1 second
```

---

## Step 3

```cpp id="trh4gp"
digitalWrite(2, LOW);
```

Turns GPIO 2 OFF.

Voltage becomes:

```text id="72jq3q"
0V
```

---

## Result

LED connected to GPIO 2 blinks continuously.

---

# 5. Understanding GPIO Pins

GPIO means:

# General Purpose Input Output

These are programmable pins on ESP32.

---

# GPIO Can Work As

| Mode   | Purpose      |
| ------ | ------------ |
| INPUT  | Read signals |
| OUTPUT | Send signals |

---

# Examples

| Device | GPIO Usage |
| ------ | ---------- |
| LED    | OUTPUT     |
| Button | INPUT      |
| Sensor | INPUT      |
| Motor  | OUTPUT     |

---

# 6. pinMode()

```cpp id="72jj8g"
pinMode(pin, mode);
```

Defines how a pin behaves.

---

# Examples

## Output Pin

```cpp id="sowz8e"
pinMode(2, OUTPUT);
```

ESP32 sends signals.

---

## Input Pin

```cpp id="cs2dj2"
pinMode(4, INPUT);
```

ESP32 reads signals.

---

# 7. digitalWrite()

```cpp id="wzpxaj"
digitalWrite(pin, state);
```

Controls output voltage.

---

# States

| State | Meaning |
| ----- | ------- |
| HIGH  | 3.3V    |
| LOW   | 0V      |

---

# Example

```cpp id="7p3wrd"
digitalWrite(2, HIGH);
```

Turns ON connected device.

---

# 8. digitalRead()

```cpp id="p96v84"
digitalRead(pin);
```

Reads digital input value.

---

# Example

```cpp id="j3k9j5"
int button = digitalRead(4);
```

Reads button state.

---

# 9. delay()

```cpp id="55d7py"
delay(time);
```

Pauses program execution.

Unit:

```text id="g26sli"
milliseconds
```

---

# Examples

| Delay       | Meaning    |
| ----------- | ---------- |
| delay(1000) | 1 second   |
| delay(500)  | 0.5 second |

---

# 10. Serial Communication

Serial Monitor is extremely important for debugging.

---

# Starting Serial Communication

```cpp id="4sj1wm"
Serial.begin(115200);
```

---

# Printing Data

```cpp id="3fgv7n"
Serial.println("Hello");
```

Displays:

```text id="g1o4fa"
Hello
```

inside Serial Monitor.

---

# Difference Between print() and println()

| Function  | Behavior  |
| --------- | --------- |
| print()   | Same line |
| println() | New line  |

---

# Example

```cpp id="o1e5yn"
Serial.print("X:");
Serial.println(100);
```

Output:

```text id="68lq12"
X:100
```

---

# 11. Variables in ESP32 Programming

Variables store data.

---

# Example

```cpp id="n7m7s7"
int sensorValue = 100;
```

---

# Common Variable Types

| Type  | Purpose          |
| ----- | ---------------- |
| int   | Integer values   |
| float | Decimal values   |
| bool  | true/false       |
| char  | Single character |

---

# Example

```cpp id="7mvtqz"
float angle = 25.6;
```

---

# 12. Conditions (if Statements)

Used for decision making.

---

# Example

```cpp id="3g3g40"
if(angle > 20) {

  Serial.println("SLOUCH");
}
```

---

# Meaning

If angle exceeds 20:
display:

```text id="v3mxj8"
SLOUCH
```

---

# 13. Loops

ESP32 repeatedly executes loop() forever.

This enables:

* live sensor monitoring,
* real-time systems,
* continuous updates.

---

# Example Workflow

```text id="4c6lmk"
Read sensor
    ↓
Process data
    ↓
Take decision
    ↓
Update display
    ↓
Repeat forever
```

---

# 14. Libraries

Libraries add ready-made functionality.

---

# Example

```cpp id="3g7d2q"
#include <Wire.h>
```

Adds I2C communication support.

---

# Example

```cpp id="u8hslv"
#include <MPU6050.h>
```

Adds MPU6050 control functions.

---

# Why Libraries Matter

Without libraries:
you must manually write complex low-level hardware code.

Libraries simplify development.

---

# 15. How ESP32 Executes Code

Process flow:

```text id="o9gs5k"
Write code on laptop
        ↓
Compile code
        ↓
Upload to ESP32
        ↓
ESP32 stores program
        ↓
ESP32 executes instructions
```

---

# 16. Upload Process

When Upload button is pressed:

Arduino IDE:

1. compiles code,
2. converts into machine code,
3. transfers to ESP32 memory.

ESP32 then restarts and runs the uploaded program.

---

# 17. Important Things to Take Care Of

| Precaution            | Reason                        |
| --------------------- | ----------------------------- |
| Select correct board  | Prevent upload issues         |
| Use data cable        | Required for communication    |
| Install drivers       | COM port detection            |
| Match baud rate       | Proper Serial Monitor output  |
| Avoid loose wires     | Stable operation              |
| Use correct GPIO pins | Proper hardware communication |

---

# 18. Basic ESP32 Programming Workflow

Typical workflow:

```text id="pn6iie"
Initialize hardware
        ↓
Read inputs
        ↓
Process logic
        ↓
Control outputs
        ↓
Repeat continuously
```

---

# 19. Example — Smart Posture System Workflow

```text id="rm5ovw"
MPU6050 detects tilt
        ↓
ESP32 reads acceleration
        ↓
ESP32 calculates angle
        ↓
if(angle > threshold)
        ↓
Display SLOUCH
Else
Display GOOD
```

---

# 20. Final Understanding

The ESP32 acts like a mini computer.

Your code becomes:

* instructions,
* logic,
* and behavior

for the hardware system.

The ESP32 continuously:

* reads data,
* processes information,
* and controls outputs

according to the program you write.
