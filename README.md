# Smart Posture Detection Wearable

An IoT-based wearable posture correction system using ESP32 and MPU6050.

The device detects bad posture in real time and alerts the user using a vibration motor while also displaying posture status on an OLED display.

---

# Project Objective

The goal of this project is to create a wearable smart posture monitoring system that:

- Detects slouching posture
- Alerts the user through vibration
- Displays posture status on OLED
- Works on battery power
- Can later be expanded with IoT features like Bluetooth/WiFi monitoring

---

# Hardware Components

| Component | Purpose |
|---|---|
| ESP32 DevKit V1 | Main microcontroller |
| MPU6050 (GY-521) | Motion + tilt sensing |
| OLED SSD1306 Display | Display posture status |
| Vibration Motor Module | Haptic feedback alert |
| Push Button | Posture calibration |
| Breadboard | Prototyping |
| Jumper Wires | Connections |
| LiPo Battery | Portable power |
| TP4056 Module | Battery charging |
| Enclosure Box | Device housing |
| Velcro/Elastic Strap | Wearable mounting |

---

# System Architecture

```text
        MPU6050
            ↓
         ESP32
      ↙    ↓    ↘
 OLED   Logic   Vibration
            ↓
      Battery System
            ↓
      Wearable Device
```

---

# Project Workflow

```text
User wears device
        ↓
MPU6050 reads body angle
        ↓
ESP32 processes posture
        ↓
If posture is correct:
    OLED shows GOOD
Else:
    OLED shows SLOUCHING
    Motor vibrates
        ↓
Button recalibrates posture
```

---

# Hardware Connections

## MPU6050 → ESP32

| MPU6050 | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

## OLED → ESP32

| OLED | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

## Vibration Motor → ESP32

| Motor Module | ESP32 |
|---|---|
| VCC | 3.3V / 5V |
| GND | GND |
| IN | GPIO 18 |

---

## Push Button → ESP32

| Button | ESP32 |
|---|---|
| One Side | GPIO 19 |
| Other Side | GND |

Use:
```cpp
INPUT_PULLUP
```

---

# Development Roadmap

# Phase 1 — Hardware Setup

## Goal
Get all core components working.

## Checklist

- [x] Install Arduino IDE
- [x] Install ESP32 board package
- [x] Install USB drivers
- [x] Test ESP32 with Blink code
- [ ] Connect MPU6050
- [ ] Read sensor values in Serial Monitor
- [ ] Connect OLED display
- [ ] Display test message on OLED
- [ ] Verify sensor values change with movement

---

# Phase 2 — Posture Detection Logic

## Goal
Detect slouching posture using angle calculations.

## Checklist

- [ ] Understand accelerometer readings
- [ ] Calculate tilt angle
- [ ] Define posture threshold
- [ ] Detect GOOD posture
- [ ] Detect BAD posture
- [ ] Test posture accuracy

---

# Phase 3 — Alert System

## Goal
Alert the user during bad posture.

## Checklist

- [x] Connect vibration motor
- [ ] Vibrate during bad posture
- [ ] Display posture status on OLED
- [ ] Add calibration button
- [ ] Save reference posture angle

---

# Phase 4 — Portable Power System

## Goal
Make the device battery powered.

## Checklist

- [x] Connect LiPo battery
- [x] Connect TP4056 charging module
- [x] Test battery charging
- [x] Test portable operation
- [ ] Verify safe voltage levels

---

# Phase 5 — Wearable Design

## Goal
Convert prototype into wearable form.

## Checklist

- [ ] Arrange components compactly
- [ ] Fit components into enclosure
- [ ] Cut holes for USB/display/button
- [ ] Attach straps
- [ ] Test wearable comfort

---

# Phase 6 — Final Features & Improvements

## Goal
Add advanced features and polish.

## Checklist

- [ ] Improve posture accuracy
- [ ] Add Bluetooth support
- [ ] Add mobile app support
- [ ] Add posture history tracking
- [ ] Add WiFi dashboard
- [ ] Optimize battery usage

---

## Must Complete

- [x] ESP32 setup
- [x] Arduino IDE setup
- [x] MPU6050 connected
- [x] Sensor values printing
- [x] OLED working
- [ ] Basic posture logic

If these are completed, the project foundation is successfully built.

---

# Required Libraries

Install these libraries in Arduino IDE:

```text
Adafruit GFX
Adafruit SSD1306
MPU6050 Library
Wire Library
```

---

# Important Notes

## Do NOT:
- Start with battery power first
- Solder immediately
- Make messy wiring
- Build final enclosure too early

---

## Always:
- Test one component at a time
- Keep wiring organized
- Use USB power during development
- Debug step by step

---

# Team Division Suggestion

| Team Member | Responsibility |
|---|---|
| Member 1 | ESP32 setup |
| Member 2 | MPU6050 integration |
| Member 3 | OLED display |
| Member 4 | Power + enclosure |
| Team Leader | Integration + debugging |

---

# Future Scope

Possible future improvements:

- Mobile app integration
- Cloud posture monitoring
- AI posture analysis
- Exercise recommendations
- Health analytics dashboard
- Smart posture reminders

---

# Expected Output

## GOOD POSTURE

```text
OLED: GOOD POSTURE
Motor: OFF
```

## BAD POSTURE

```text
OLED: SLOUCHING
Motor: VIBRATION ON
```

---

# Final Goal

Build a fully functional wearable posture correction device capable of:

- Real-time posture monitoring
- User alerts
- Portable battery operation
- Expandable IoT functionality