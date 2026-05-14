# EXTRA THINGS YOU NEED FOR PHASE 1

# 1. USB Cable (VERY IMPORTANT)

This is the #1 issue beginners face.

Your ESP32 needs:

# USB DATA CABLE

NOT just charging cable.

---

## Usually ESP32 uses:

### Micro USB

OR

### USB Type-C

depending on board version.

Most ESP32 DevKit V1 boards use:

```text id="f3aq0c"
Micro USB
```

Check before buying.

---

# BIG WARNING

Many phone cables are:

```text id="l7np1x"
Charge only
```

These cannot upload code.

Symptoms:

* ESP32 not detected
* no COM port
* upload failed

---

# Solution

Use:

* good quality Android data cable
* preferably short cable

---

# 2. Install USB Drivers

ESP32 boards use USB chips like:

* CP2102
* CH340

Without drivers:
your laptop may not detect ESP32.

---

# How to know?

When connected:

If COM port does NOT appear:
you need drivers.

---

# CP2102 Driver

[CP210x USB Driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?utm_source=chatgpt.com)

---

# CH340 Driver

[CH340 Driver](https://sparks.gogo.co.nz/ch340.html?utm_source=chatgpt.com)

Install whichever your board uses.

---

# 3. Breadboard Power Rails Understanding

Your breadboard has:

```text id="c8miyv"
+ rail
- rail
```

on sides.

Use them properly.

---

# Recommended Setup

Connect:

| ESP32 | Breadboard Rail |
| ----- | --------------- |
| 3.3V  | + rail          |
| GND   | - rail          |

Now every module can take power from rails.

This makes wiring cleaner.

---

# 4. Jumper Wire Types

You bought:

```text id="pw67z6"
Male-to-Male
```

Good.

That is enough because:

* ESP32 pins are female
* breadboard holes accept male pins
* modules usually have male headers

---

# 5. VERY IMPORTANT — COMMON GROUND

Every module MUST share same GND.

This is one of the biggest beginner mistakes.

Correct:

```text id="xtdk1o"
ESP32 GND
   ↓
Breadboard GND rail
   ↓
MPU6050 GND
OLED GND
Motor GND
```

Without common ground:
system behaves randomly.

---

# 6. HOW TO PLACE ESP32 ON BREADBOARD

Place ESP32 in middle gap.

Like this:

```text id="84t3ah"
| | | ESP32 | | |
```

so both sides of pins remain accessible.

---

# 7. I2C Wiring Layout (IMPORTANT)

Since both OLED and MPU6050 use I2C:

You will connect:

| ESP32  | MPU6050 | OLED |
| ------ | ------- | ---- |
| GPIO21 | SDA     | SDA  |
| GPIO22 | SCL     | SCL  |

Meaning:
same SDA/SCL shared.

This is NORMAL.

Do not think:
“2 devices on same wire = short circuit.”

That is exactly how I2C works.

---

# 8. OLED ADDRESS ISSUE

Some OLEDs use:

```text id="kvmj9j"
0x3C
```

Some use:

```text id="1ntvqs"
0x3D
```

If display not working:
this is usually the reason.

---

# Solution

Run:

# I2C Scanner Code

This finds device addresses automatically.

VERY useful.

---

# 9. KEEP SENSOR STILL DURING TESTING

MPU6050 is motion sensitive.

If sensor shakes:
values fluctuate heavily.

During initial calibration:
keep it flat and stable.

---

# 10. Serial Monitor Baud Rate

Your code may use:

```cpp id="5g1zvj"
Serial.begin(115200);
```

Then Serial Monitor MUST also be:

```text id="r4km9g"
115200
```

If not:
you see garbage symbols.

---

# 11. ESP32 Upload Button Issue

Sometimes upload fails with:

```text id="z7fcnm"
Connecting........_____.....
```

This is common.

---

# Fix

When uploading:

Press and hold:

```text id="zbtt0m"
BOOT
```

button on ESP32.

Release after:
“Connecting…”

appears.

---

# 12. Wire Length Matters

Keep jumper wires:

* short
* neat

Messy long wires:

* create loose connections
* increase debugging pain

---

# 13. DO NOT POWER EVERYTHING FROM LAPTOP USB FOREVER

For Phase 1:
USB power is fine.

Later:
you will use battery.

---

# 14. You DON'T Need Soldering Yet

For tomorrow:

```text id="d4qbaf"
NO soldering required
```

Breadboard is enough.

---

# 15. Future Important Thing — Vibration Motor

DO NOT directly connect bare motor to GPIO.

But you bought:

# vibration motor module

So you're safe.

The module already includes driver circuitry.

---

# 16. Recommended Wiring Order

DO NOT connect everything randomly.

Best order:

---

## First

ONLY:

```text id="ol9ebx"
ESP32
```

test blink.

---

## Then add:

```text id="qofvnf"
MPU6050
```

test sensor.

---

## Then add:

```text id="1rf46n"
OLED
```

test display.

---

## Then combine all.

This avoids confusion.

---

# 17. Keep One Spare MPU6050

Good decision.

These cheap modules sometimes:

* arrive faulty
* burn accidentally
* have loose soldering

---

# 18. Actual Wiring Diagram You’ll Follow

Your final Phase 1 wiring basically becomes:

```text id="z4l2b8"
ESP32 3.3V  → Breadboard +
ESP32 GND   → Breadboard -

MPU6050:
VCC → +
GND → -
SDA → GPIO21
SCL → GPIO22

OLED:
VCC → +
GND → -
SDA → GPIO21
SCL → GPIO22
```

That’s the core setup.

---

# 19. MOST IMPORTANT DEBUGGING RULE

If something fails:

DO NOT change 10 things together.

Check:

* power
* wiring
* COM port
* libraries
* addresses

ONE BY ONE.

---

# 20. What You ACTUALLY Need Tomorrow

# Essential Items Checklist

## Hardware

✅ ESP32
✅ MPU6050
✅ OLED
✅ Breadboard
✅ Jumper wires
✅ USB data cable

---

## Software

✅ Arduino IDE
✅ ESP32 board package
✅ Libraries installed
✅ USB drivers

---

## Goal

By end:

```text id="5e24jg"
Tilt sensor → ESP32 → OLED output
```

That means your project has officially started working.
