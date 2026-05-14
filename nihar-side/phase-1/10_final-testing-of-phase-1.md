```cpp
#include <Wire.h>
#include <MPU6050.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ================= OLED SETTINGS =================

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ================= MPU6050 =================

MPU6050 mpu;

int16_t ax, ay, az;

// ================= VARIABLES =================

float angleX;

void setup() {

  // Serial Monitor
  Serial.begin(115200);

  // I2C Pins for ESP32
  Wire.begin(21, 22);

  // Initialize MPU6050
  mpu.initialize();

  // Check MPU6050 connection
  if (mpu.testConnection()) {
    Serial.println("MPU6050 Connected");
  } else {
    Serial.println("MPU6050 Connection Failed");
    while (1);
  }

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {

    Serial.println("OLED Not Found");

    while (1);
  }

  // Clear OLED
  display.clearDisplay();
  display.display();

  // Startup Message
  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(10, 20);
  display.println("START");

  display.display();

  delay(2000);
}

void loop() {

  // Read Accelerometer Values
  mpu.getAcceleration(&ax, &ay, &az);

  // Calculate Tilt Angle
  angleX = atan2(ay, az) * 180 / PI;

  // Print on Serial Monitor
  Serial.print("Angle X: ");
  Serial.println(angleX);

  // Clear OLED
  display.clearDisplay();

  // Title
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("SMART POSTURE");

  // Angle Display
  display.setCursor(0, 15);
  display.print("Angle: ");
  display.print(angleX);

  // Posture Logic
  if (abs(angleX) > 20) {

    display.setTextSize(2);

    display.setCursor(0, 40);
    display.println("SLOUCH");

  } else {

    display.setTextSize(2);

    display.setCursor(0, 40);
    display.println("GOOD");
  }

  // Update OLED
  display.display();

  delay(300);
}
```

# WHAT THIS CODE DOES

Your setup now becomes:

```text id="jlwm0k"
MPU6050 → detects tilt
       ↓
ESP32 → calculates angle
       ↓
OLED → shows posture status
```

---

# EXPECTED OLED OUTPUT

When board is straight:

```text id="jlwm2l"
SMART POSTURE

Angle: 5

GOOD
```

---

When tilted/slouched:

```text id="jlwmow"
SMART POSTURE

Angle: 32

SLOUCH
```

---

# HOW TO TEST IT

After uploading:

## Keep breadboard straight

OLED should show:

```text id="jlwmzc"
GOOD
```

---

## Tilt the whole breadboard slightly

Angle changes.

If angle crosses threshold:

```text id="jlwmjm"
20 degrees
```

OLED changes to:

```text id="jlwm0t"
SLOUCH
```

---

# IMPORTANT

Move slowly.

MPU6050 is sensitive.

Even small tilt changes values.

---

# IF OLED SHOWS NOTHING

Check:

| Problem              | Fix                      |
| -------------------- | ------------------------ |
| Wrong OLED address   | Try 0x3D instead of 0x3C |
| SDA/SCL swapped      | GPIO21=SDA, GPIO22=SCL   |
| Loose wires          | Push firmly              |
| Missing library      | Install SSD1306 + GFX    |
| Wrong board selected | ESP32 Dev Module         |

---

# IF MPU6050 DOESN'T RESPOND

Check:

| Problem            | Fix                  |
| ------------------ | -------------------- |
| Wrong power        | Use 3.3V             |
| No common ground   | Connect GND properly |
| Wrong SDA/SCL      | Verify wiring        |
| Loose jumper wires | Reconnect            |

---

# VERY IMPORTANT THING ABOUT THIS CODE

This is:

# Beginner posture logic

Not medically accurate posture analysis yet.

Currently:

* it only checks tilt angle.

Later you can improve:

* filtering
* calibration
* gyroscope fusion
* adaptive posture learning

But for Phase 1:

THIS IS PERFECT.

---

# WHAT YOU ACHIEVED AFTER THIS

If this works:

✅ ESP32 working
✅ MPU6050 working
✅ OLED working
✅ I2C communication working
✅ posture angle calculation working
✅ live posture monitoring working

That means your smart posture wearable prototype has officially started functioning.
