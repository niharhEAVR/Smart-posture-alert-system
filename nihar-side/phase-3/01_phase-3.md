# PHASE 3 — Alert System (Full Explanation)

Now your project is entering the **“real wearable device”** stage.

Until now:

* ESP32 reads sensor data
* MPU6050 detects tilt/posture
* OLED shows data
* Logic decides GOOD/BAD posture

But currently the system only *knows* posture.

Now in Phase 3, the system must:

1. **Inform the user**
2. **Warn the user**
3. **Allow recalibration**
4. Make the device behave like an actual smart wearable

---

# MAIN GOALS OF PHASE 3

You will add:

| Feature              | Purpose                            |
| -------------------- | ---------------------------------- |
| Vibration Motor      | Physical alert when posture is bad |
| OLED Status Messages | Show GOOD/BAD/CALIBRATING          |
| Calibration Button   | Save new straight posture          |
| Alert Timing Logic   | Prevent constant vibration spam    |
| Stability Logic      | Avoid false alerts                 |

---

# BIG PICTURE FLOW

Your device will now behave like this:

```text
User wears device
        ↓
Press calibration button
        ↓
Device stores "straight posture"
        ↓
Continuously compares current angle
        ↓
If posture becomes bad for few seconds:
        ↓
OLED shows warning
        ↓
Vibration motor buzzes
        ↓
User corrects posture
        ↓
Alert stops
```

---

# HARDWARE REQUIRED FOR PHASE 3

---

## 1. Vibration Motor

Usually called:

* Coin vibration motor
* Mini vibration motor
* 3V vibration motor

Purpose:

* Gives silent physical feedback
* Better than sound/buzzer for wearable device

---

## 2. Push Button

Purpose:

* Recalibration
* User presses while sitting straight

---

## 3. Transistor (IMPORTANT)

ESP32 GPIO pins cannot safely power motors directly.

You SHOULD use:

* 2N2222 transistor
  OR
* S8050 transistor

This acts like a switch.

---

## 4. Diode (Recommended)

Like:

* 1N4007

Protects ESP32 from motor reverse current.

---

# PHASE 3 MODULE BREAKDOWN

---

# MODULE 1 — CALIBRATION SYSTEM

---

# Purpose

When user sits correctly:

* press button
* device stores current angle as reference posture

---

# WHY THIS IS IMPORTANT

Every person's body is different.

Example:

Person A straight posture:

```text
10°
```

Person B straight posture:

```text
-3°
```

So you cannot hardcode:

```cpp
0° = good posture
```

Instead:

```cpp
referenceAngle = currentAngle
```

---

# HOW IT WORKS

---

## Step 1

User sits properly.

---

## Step 2

User presses button.

---

## Step 3

ESP32 stores:

```cpp
referenceAngle = currentAngle;
```

---

## Step 4

Future posture checks compare with reference:

```cpp
difference = abs(currentAngle - referenceAngle);
```

---

# POSTURE THRESHOLD

Example:

```cpp
if(difference < 10)
    GOOD
else
    BAD
```

This means:

* within 10° → acceptable
* above 10° → bad posture

---

# MODULE 2 — OLED STATUS SYSTEM

Now OLED becomes your user interface.

---

# WHAT TO DISPLAY

---

## During Calibration

```text
CALIBRATING...
Sit Straight
```

---

## Good Posture

```text
POSTURE GOOD
Angle: 4°
```

---

## Bad Posture

```text
BAD POSTURE!
Straighten Back
```

---

## Alert Active

```text
WARNING!
VIBRATING...
```

---

# IMPORTANT UI IDEA

Do NOT constantly redraw entire OLED every loop unnecessarily.

Why?

Because:

* screen flickers
* slower performance
* ugly UI

Better:

Update only when state changes.

Example:

```cpp
if(stateChanged)
{
   updateOLED();
}
```

---

# MODULE 3 — VIBRATION ALERT SYSTEM

This is the most important feature.

---

# BASIC IDEA

If posture becomes bad:

```text
motor vibrates
```

If posture becomes good again:

```text
motor stops
```

---

# BUT THERE IS A PROBLEM

If you instantly vibrate:

Small movement → vibration

That becomes annoying.

---

# SOLUTION → DELAY LOGIC

Only alert if posture remains bad for some time.

Example:

```text
Bad posture for:
0.5 sec → ignore
1 sec → ignore
3 sec → ALERT
```

This makes system intelligent.

---

# IMPLEMENTATION IDEA

---

## Step 1

Detect bad posture.

---

## Step 2

Start timer.

Example:

```cpp
badPostureStartTime = millis();
```

---

## Step 3

Check duration:

```cpp
if(millis() - badPostureStartTime > 3000)
{
    activate vibration
}
```

---

# WHY THIS IS IMPORTANT

Without this:

* every tiny movement causes buzzing
* device becomes unusable

---

# MODULE 4 — ALERT COOLDOWN SYSTEM

Another important improvement.

---

# PROBLEM

Without cooldown:

```text
BAD POSTURE
BUZZZZZZZZZZ
BUZZZZZZZZZZ
BUZZZZZZZZZZ
```

continuously forever.

Very irritating.

---

# SOLUTION

Buzz only periodically.

Example:

```text
vibrate 1 second
wait 5 seconds
vibrate again if still bad
```

---

# LOGIC

```cpp
if(stillBad && cooldownFinished)
{
   vibrate();
}
```

---

# MODULE 5 — STABILITY FILTERING

MPU6050 data is noisy.

Angles may jump:

```text
5°
6°
4°
8°
3°
```

even while sitting still.

---

# SOLUTION OPTIONS

---

## OPTION 1 — Averaging

Take multiple readings.

Example:

```text
(4 + 5 + 6 + 5 + 4)/5
```

More stable.

---

## OPTION 2 — Threshold Buffer

Instead of:

```cpp
bad if > 10°
```

Use:

```cpp
bad if > 12°
good if < 8°
```

This avoids rapid switching.

This is called:

# Hysteresis

Very useful in embedded systems.

---

# RECOMMENDED FINAL SYSTEM FLOW

```text
START
  ↓
Initialize ESP32
  ↓
Initialize MPU6050
  ↓
Initialize OLED
  ↓
Initialize vibration motor
  ↓
Initialize button
  ↓
Wait for calibration
  ↓
Save reference posture
  ↓
Loop forever:
    Read angle
    Compare with reference
    Determine GOOD/BAD
    Update OLED
    Handle timers
    Trigger vibration if needed
```

---

# RECOMMENDED PIN CONNECTIONS

Example only:

| Component               | ESP32 Pin |
| ----------------------- | --------- |
| MPU6050 SDA             | GPIO 21   |
| MPU6050 SCL             | GPIO 22   |
| OLED SDA                | GPIO 21   |
| OLED SCL                | GPIO 22   |
| Button                  | GPIO 4    |
| Vibration Motor Control | GPIO 18   |

---

# IMPORTANT SOFTWARE CONCEPTS YOU WILL USE

| Concept             | Why                 |
| ------------------- | ------------------- |
| millis()            | Non-blocking timers |
| digitalRead()       | Read button         |
| digitalWrite()      | Motor control       |
| state variables     | GOOD/BAD states     |
| debounce            | Stable button press |
| threshold logic     | Posture detection   |
| averaging/filtering | Stable sensor data  |

---

# VERY IMPORTANT

DO NOT USE:

```cpp
delay(3000);
```

for posture timing.

Why?

Because:

* system freezes
* OLED freezes
* sensor reading pauses
* button stops responding

Use:

```cpp
millis()
```

instead.

---

# WHAT YOUR PROJECT BECOMES AFTER PHASE 3

After this phase your system becomes:

## A complete smart posture wearable prototype.

Because now it can:

✅ Detect posture
✅ Remember calibration
✅ Alert user physically
✅ Show live status
✅ Work automatically
✅ Behave like real IoT wearable

---

# AFTER PHASE 3 (Future Improvements)

Later you can add:

* Bluetooth app
* Data logging
* Firebase/cloud sync
* Battery charging module
* Machine learning posture detection
* Sitting analytics
* Daily posture score
* Mobile notifications
* Web dashboard

Those are advanced stages later.
