# OLED Code Explanation Documentation

## SSD1306 OLED with ESP32 — Smart Posture Detection Wearable

---

# 1. Purpose of the OLED Code

The OLED code is responsible for:

* establishing communication between ESP32 and OLED display,
* displaying text and graphics,
* showing posture status,
* and updating output in real time.

The OLED acts as the visual output unit of the project.

Example outputs:

```text id="jlwm4e"
GOOD
```

or

```text id="jlwmz2"
SLOUCH
```

---

# 2. Complete OLED Test Code

```cpp id="r5w1pd"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {

  Serial.begin(115200);

  Wire.begin(21,22);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {

    Serial.println("OLED Not Found");

    while(true);
  }

  display.clearDisplay();

  display.setTextSize(2);

  display.setTextColor(WHITE);

  display.setCursor(10,20);

  display.println("HELLO");

  display.display();
}

void loop() {

}
```

---

# 3. Understanding OLED Basics

The OLED used is:

```text id="jlwm3m"
SSD1306 I2C OLED Display
```

Typical module:

![Image](https://images.openai.com/static-rsc-4/s5adpE0WS1nWxMru498G26DP71B35kFyBJk9mj-MKZNqp3fH2ZOG090LtPLEPMu63-jUXQeFETCjsN02a7y9d8Js7BfCTEp_ra95qSviuEZ8EUM7rQ7iP56kOEQMHSsRq1E856EvMTbRLRhMCl3vPoSSZCAXEcb1ZNDSwh0C5bGa3h5-ZFzq-yFpU4O1sZsW?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/HKjrRuPz2HoSHkqSHEblUvVNp3yyYYkVu9XHm3Ks7FRvSf4yjrl7jVJdZlYkcsC4J2V6JqkRIeXoY2JVwfAnMeUF6WD6ijPq8QeGzyahkBXUDc_0g2Lz7wVuN6kpPlOX0o1NpibD886OZp5nB9N--w130vx7rhGV4i1dxDC1VTkqdUESjasxJmpzlBVm16pm?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/BEwnPn5aF0l9GpzvRc4xEmb1WrcTFQNWyWVWt_8fBFjg7FBVsvDsBrycNFJ5k1MnZWuma1JZwGhfyVEiujrhz2KpoXZidir2gw6pFBxjEmtZn88ppUtuneg3fBER84vRXAnK7no2JymMf7IkD-fE34rln_TIpBjJKW0ASjRBpDUXn2KLKQLZipmkHGNdcyCd?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/_z2h4EYnnZreD-jOKoZoT24P8a7cTOr1BqNeiy3a3Fu2PIMDD2PVss7p0a42VbtzQqeAmkdoSvUE5ChM0fXUV9Yhn9tEpS9RvxAjwX4S7s7AjdW8XWiPxUtEij7Z-Vit81aLxYv9VCblDG23H0zwW3gdNGLFIkSIwfglLddzHJ-GhZON0j6jVLTZ9ScEx0RK?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/CwE8t1pt6yO0q1L35BsuXlJGNIRE5fPOe-M4D9o4YnogbgY8u1Qz24GA21N1K8yuI_OJG3PYwnFP9fS1r1LVwXLjPxxU58ZyCszvEK-s8pl50cDJ55PTtyxSjd2yJEme2L7e4jyeNOSptz2rIb7uM7rBvzU7QJd0NtyjcKhzZFka-pgwHeQw8qmRDHkV7Keq?purpose=fullsize)

---

# OLED Communication Type

The OLED uses:

# I2C Communication

Only two communication wires are required:

| Signal | Purpose |
| ------ | ------- |
| SDA    | Data    |
| SCL    | Clock   |

---

# ESP32 I2C Pins

| Function | ESP32 GPIO |
| -------- | ---------- |
| SDA      | GPIO21     |
| SCL      | GPIO22     |

---

# 4. Including Libraries

```cpp id="jlwmm2"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
```

---

# 4.1 Wire.h

Enables:

# I2C communication

Required because OLED communicates through I2C.

---

# 4.2 Adafruit_GFX.h

Graphics library.

Provides functions for:

* drawing text,
* shapes,
* lines,
* graphics.

---

# 4.3 Adafruit_SSD1306.h

OLED driver library.

Controls:

* OLED initialization,
* communication,
* screen updates.

---

# 5. Screen Resolution Definitions

```cpp id="jlwmh4"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
```

Defines OLED resolution.

---

# Meaning

The OLED has:

| Dimension | Pixels     |
| --------- | ---------- |
| Width     | 128 pixels |
| Height    | 64 pixels  |

---

# WHY THIS IS IMPORTANT

The display library needs screen dimensions to:

* allocate memory,
* position text,
* manage graphics correctly.

---

# 6. Creating OLED Object

```cpp id="jlwmor"
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
```

Creates an OLED display object named:

```text id="jlwm34"
display
```

This object controls the physical OLED.

---

# Parameters Meaning

| Parameter     | Meaning               |
| ------------- | --------------------- |
| SCREEN_WIDTH  | Display width         |
| SCREEN_HEIGHT | Display height        |
| &Wire         | Use I2C communication |
| -1            | No reset pin used     |

---

# 7. Understanding setup()

```cpp id="jlwmij"
void setup()
```

Runs only once when ESP32 powers ON.

Used for:

* initializing OLED,
* starting communication,
* configuring display.

---

# 7.1 Starting Serial Communication

```cpp id="jlwmti"
Serial.begin(115200);
```

Starts Serial Monitor communication.

Used for debugging and error messages.

---

# 7.2 Starting I2C Communication

```cpp id="jlwmzw"
Wire.begin(21,22);
```

Starts I2C communication.

Defines:

| GPIO   | Function |
| ------ | -------- |
| GPIO21 | SDA      |
| GPIO22 | SCL      |

---

# IMPORTANT THINGS TO TAKE CARE OF

| Mistake         | Result             |
| --------------- | ------------------ |
| SDA/SCL swapped | OLED not detected  |
| Loose wires     | Flickering display |
| Wrong GPIO pins | No communication   |

---

# 7.3 Initializing OLED

```cpp id="jlwmm0"
display.begin(SSD1306_SWITCHCAPVCC, 0x3C)
```

Starts OLED communication.

---

# Parameters

---

## SSD1306_SWITCHCAPVCC

Enables internal voltage generation for OLED.

---

## 0x3C

This is the:

# I2C Address

of the OLED.

---

# IMPORTANT

Most OLEDs use:

```text id="jlwm83"
0x3C
```

Some use:

```text id="jlwmzx"
0x3D
```

If display does not work:
try changing address.

---

# 7.4 OLED Connection Failure Handling

```cpp id="jlwm9j"
if(!display.begin(...))
```

Checks whether OLED initialization failed.

---

# If OLED Not Found

```cpp id="jlwmhi"
Serial.println("OLED Not Found");
```

prints error.

---

# Then

```cpp id="jlwmn2"
while(true);
```

stops program forever.

---

# WHY THIS IS IMPORTANT

Without OLED connection:
continuing program execution makes no sense.

---

# 8. Clearing Display

```cpp id="jlwm4l"
display.clearDisplay();
```

Clears OLED memory buffer.

---

# IMPORTANT CONCEPT

OLED drawing first happens in:

# memory buffer

NOT directly on screen.

---

# 9. Setting Text Size

```cpp id="jlwm6o"
display.setTextSize(2);
```

Controls text scaling.

---

# Examples

| Size | Appearance |
| ---- | ---------- |
| 1    | Small      |
| 2    | Medium     |
| 3    | Large      |

---

# 10. Setting Text Color

```cpp id="jlwm5m"
display.setTextColor(WHITE);
```

Sets text color.

Since OLED is monochrome:
only:

* WHITE
* BLACK

exist.

---

# 11. Setting Cursor Position

```cpp id="jlwm1t"
display.setCursor(10,20);
```

Defines where text starts.

---

# Coordinate System

```text id="jlwmrf"
(0,0) → top-left corner
```

---

# Meaning

| Value | Purpose    |
| ----- | ---------- |
| 10    | X-position |
| 20    | Y-position |

---

# 12. Printing Text

```cpp id="jlwm7v"
display.println("HELLO");
```

Stores text inside OLED memory buffer.

---

# IMPORTANT

At this stage:
text is NOT yet visible physically.

---

# 13. Updating OLED Screen

```cpp id="jlwm5x"
display.display();
```

VERY IMPORTANT FUNCTION.

This transfers:

* memory buffer
  → actual OLED screen.

---

# WITHOUT THIS FUNCTION

Nothing appears on display.

This is one of the biggest beginner mistakes.

---

# 14. Understanding loop()

```cpp id="jlwm9m"
void loop()
```

In this simple test:
loop() is empty.

Reason:
the display only needs to show static text once.

---

# 15. Dynamic OLED Updates

In posture detection:

loop() continuously:

* clears screen,
* writes new values,
* updates posture status.

Example:

```cpp id="jlwm5d"
display.clearDisplay();

display.println("GOOD");

display.display();
```

---

# 16. How OLED Works Internally

Workflow:

```text id="jlwmju"
ESP32 writes text
       ↓
Stored in memory buffer
       ↓
display.display()
       ↓
OLED physically updates
```

---

# 17. Important Things to Take Care Of

---

# 17.1 Correct Power Supply

Use:

```text id="jlwm4x"
3.3V
```

for stable ESP32 communication.

---

# 17.2 Correct I2C Wiring

| ESP32  | OLED |
| ------ | ---- |
| GPIO21 | SDA  |
| GPIO22 | SCL  |

---

# 17.3 Common Ground

ESP32 GND and OLED GND must connect together.

---

# 17.4 OLED Address

Try:

* 0x3C
* 0x3D

if display not detected.

---

# 17.5 Stable Connections

Loose jumper wires cause:

* flickering,
* random shutdowns,
* missing display updates.

---

# 17.6 Always Use display.display()

Without it:
nothing becomes visible.

---

# 17.7 Clear Screen Before Rewriting

Without:

```cpp id="jlwm5y"
display.clearDisplay();
```

old text overlaps new text.

---

# 18. Final Working Principle

Overall OLED operation:

```text id="jlwmxf"
ESP32 processes posture data
        ↓
ESP32 writes text to OLED buffer
        ↓
display.display()
        ↓
OLED updates physically
```

---

# 19. Example in Smart Posture System

Workflow:

```text id="jlwm5q"
MPU6050 detects tilt
        ↓
ESP32 calculates angle
        ↓
if(angle > threshold)
        ↓
OLED shows "SLOUCH"
Else
OLED shows "GOOD"
```

---

# 20. Final Result

After successful execution:

* OLED initializes correctly,
* text appears on screen,
* posture information updates live,
* and the display subsystem becomes fully functional for the Smart Posture Detection Wearable project.




---
---
---
---
---
---



Yes, OLED code absolutely works inside `loop()` too — and in your posture project, MOST of the OLED work actually happens inside `loop()`.

The confusion happens because:

* in the basic OLED test program,
* you only displayed static text once,

so `loop()` stayed empty.

But in real projects:

```text id="jlwmca"
OLED updates continuously inside loop()
```

---

# VERY IMPORTANT CONCEPT

There are TWO TYPES of OLED usage:

| Type                  | Where OLED code goes |
| --------------------- | -------------------- |
| Static display        | setup()              |
| Live changing display | loop()               |

---

# 1. Static OLED Example

This is what you did earlier:

```cpp
void setup() {

  display.println("HELLO");

  display.display();
}

void loop() {

}
```

---

# WHY?

Because:

```text id="jlwm1c"
HELLO never changes
```

So:

* write once,
* display once,
* done.

No need for loop updates.

---

# 2. Dynamic OLED Example (YOUR PROJECT)

In your smart posture system:

* angle changes continuously,
* posture changes continuously,
* OLED must continuously refresh.

So OLED code goes inside:

```cpp
void loop()
```

---

# REAL FLOW OF YOUR PROJECT

```text id="jlwmc7"
Read MPU6050
      ↓
Calculate angle
      ↓
Decide GOOD or SLOUCH
      ↓
Update OLED
      ↓
Repeat forever
```

---

# THIS IS WHY OLED CODE GOES IN LOOP

Example:

```cpp
void loop() {

  display.clearDisplay();

  display.setCursor(0,0);

  display.println(angle);

  display.display();
}
```

This updates screen continuously.

---

# WHY clearDisplay() IS IMPORTANT

Suppose first frame shows:

```text id="jlwm4n"
Angle: 25
```

Then next frame becomes:

```text id="jlwm1q"
Angle: 5
```

Without clearing:

```text id="jlwm2y"
Angle: 255
```

or overlapping garbage may appear.

So every frame:

```cpp
display.clearDisplay();
```

clears previous contents.

---

# HOW OLED UPDATE SYSTEM WORKS

VERY IMPORTANT.

OLED does NOT instantly show text.

It works like this:

---

# STEP 1 — Write to Memory Buffer

```cpp
display.println("GOOD");
```

This only writes into RAM memory buffer.

NOT physical screen.

---

# STEP 2 — Send Buffer to OLED

```cpp
display.display();
```

This transfers memory buffer to physical OLED.

NOW the screen changes.

---

# THIS HAPPENS EVERY LOOP

So internally:

```text id="jlwm8q"
Loop starts
    ↓
Clear old frame
    ↓
Draw new frame in memory
    ↓
Send frame to OLED
    ↓
Repeat forever
```

---

# REAL POSTURE PROJECT EXAMPLE

```cpp
void loop() {

  // Read sensor
  mpu.getAcceleration(&ax, &ay, &az);

  // Calculate angle
  angleX = atan2(ay, az) * 180 / PI;

  // Clear old OLED frame
  display.clearDisplay();

  // Write new data
  display.setCursor(0,0);
  display.print("Angle: ");
  display.println(angleX);

  // Decision
  if(abs(angleX) > 20) {

    display.println("SLOUCH");

  } else {

    display.println("GOOD");
  }

  // Update physical OLED
  display.display();

  delay(200);
}
```

---

# THIS IS CALLED

# Real-Time Display Updating

Because:
the OLED updates continuously according to sensor values.

---

# WHAT HAPPENS IF YOU REMOVE display.display()

BIG beginner mistake.

Then:

```text id="jlwm6w"
Nothing updates physically
```

because:
you only changed memory buffer,
not actual screen.

---

# WHAT HAPPENS IF YOU REMOVE clearDisplay()

Then:
old text remains.

Result:

* overlapping text,
* ghosting,
* unreadable display.

---

# BEST PRACTICE FOR OLED LOOP

Typical OLED loop structure:

```cpp
void loop() {

  // Read sensors

  // Process logic

  // Clear screen
  display.clearDisplay();

  // Draw new frame

  // Update OLED
  display.display();

  // Small delay
}
```

---

# IN SHORT

| Function       | Purpose                   |
| -------------- | ------------------------- |
| clearDisplay() | Clears old frame          |
| println()      | Draws new content         |
| display()      | Shows content physically  |
| loop()         | Continuously updates OLED |

---

# FINAL UNDERSTANDING

Your OLED is basically behaving like:

```text id="jlwmup"
A tiny live monitor
```

The ESP32 continuously:

* calculates posture,
* redraws the screen,
* and refreshes the OLED

inside `loop()` forever.
