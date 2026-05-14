# PHASE 2 — POSTURE LOGIC (CORE BRAIN OF THE PROJECT)

This phase is the MOST IMPORTANT part of your whole project.

In Phase 1:

* You connected hardware
* Read MPU6050 values
* Displayed data

But in Phase 2:

* Your device starts **thinking**
* It starts deciding:

  * posture is correct
  * posture is bad
  * when to alert user

This is where your wearable becomes an actual **smart posture detection system**.

---

# MAIN GOAL OF PHASE 2

Convert raw MPU6050 sensor values into:

```text
GOOD POSTURE
BAD POSTURE
```

reliably and stably.

---

# FULL FLOW OF PHASE 2

```text
User wears device
        ↓
User sits straight
        ↓
ESP32 stores this as REFERENCE posture
        ↓
MPU6050 continuously reads angles
        ↓
Current angle compared with reference angle
        ↓
Difference calculated
        ↓
If difference small:
    GOOD POSTURE
Else:
    BAD POSTURE
        ↓
Trigger OLED + vibration
```

---

# PHASE 2 ROADMAP

You should divide this into smaller tasks:

---

# STEP 1 — Understand What MPU6050 Actually Gives

The MPU6050 gives:

* Accelerometer data
* Gyroscope data

But posture projects mainly use:

```text
Tilt angle
```

because posture is basically:

```text
body leaning forward/backward
```

---

# VERY IMPORTANT CONCEPT

You DO NOT directly detect:

```text
slouching
```

You detect:

```text
change in body angle
```

Example:

| Position         | Angle |
| ---------------- | ----- |
| Sitting straight | 5°    |
| Slight bend      | 15°   |
| Heavy slouch     | 30°   |

So your project becomes:

```text
Measure angle difference from normal posture
```

---

# STEP 2 — Decide Device Orientation

This is EXTREMELY important.

Before coding anything:

You must finalize:

```text
HOW the device will be worn
```

Example:

* vertical on upper back
* horizontal on shoulder
* inside t-shirt
* attached with strap

---

# WHY THIS IS IMPORTANT

Because MPU6050 axes depend on orientation.

The sensor has:

```text
X-axis
Y-axis
Z-axis
```

If you rotate the module:

* angle readings completely change

So the device orientation must NEVER change after calibration.

---

# THINGS TO CAREFUL ABOUT

## ❌ Bad Practice

Changing sensor direction during testing.

Example:

* testing flat on table
* then vertical on body

This ruins calibration.

---

## ✅ Correct Practice

Always test in the exact wearable orientation.

---

# STEP 3 — Identify Which Axis Changes During Slouching

Now you test:

```text
Which angle changes most when user bends?
```

Usually:

* Pitch angle changes

But you must verify.

---

# WHAT TO DO

## Test Positions

### Position 1

Sit straight.

Write angle values.

---

### Position 2

Slightly bend.

Write angle values.

---

### Position 3

Heavy slouch.

Write angle values.

---

# GOAL

Find:

```text
Which axis gives the clearest difference?
```

Example:

| Position    | Pitch |
| ----------- | ----- |
| Straight    | 2     |
| Slight bend | 10    |
| Slouch      | 25    |

Perfect.

---

# THINGS TO CAREFUL ABOUT

## ❌ Do NOT use noisy axis

Sometimes:

* one axis fluctuates too much

Avoid unstable readings.

---

# STEP 4 — Create Reference Posture System

This is the REAL calibration system.

---

# IDEA

When user presses button:

```text
Current angle becomes NORMAL posture
```

Store it in a variable.

Example:

```cpp
referenceAngle = currentAngle;
```

Now every future reading compares against this.

---

# FLOW

```text
User sits straight
        ↓
Press calibration button
        ↓
ESP32 saves current angle
        ↓
This becomes "ideal posture"
```

---

# WHY THIS IS IMPORTANT

Different people sit differently.

Example:

| Person   | Natural posture |
| -------- | --------------- |
| Person A | 3°              |
| Person B | 9°              |

So fixed angle systems are bad.

Dynamic calibration is better.

---

# THINGS TO CAREFUL ABOUT

## ❌ DO NOT calibrate while bending

If user calibrates during bad posture:

```text
bad posture becomes normal posture
```

Project fails.

---

## ✅ Solution

Display:

```text
SIT STRAIGHT
PRESS BUTTON
```

during calibration.

---

# STEP 5 — Calculate Angle Difference

Now compute:

```cpp
difference = abs(currentAngle - referenceAngle);
```

This is the MOST IMPORTANT line of Phase 2.

Because this determines posture quality.

---

# EXAMPLE

Reference:

```text
5°
```

Current:

```text
18°
```

Difference:

```text
13°
```

Now compare with threshold.

---

# STEP 6 — Create Threshold Logic

Threshold means:

```text
How much bending is acceptable?
```

---

# EXAMPLE

| Difference | Result  |
| ---------- | ------- |
| 0–7°       | GOOD    |
| 8–15°      | WARNING |
| 16°+       | BAD     |

---

# WHY THRESHOLD IS IMPORTANT

Humans naturally move slightly.

Without threshold:

* device vibrates constantly
* terrible user experience

---

# THINGS TO CAREFUL ABOUT

## ❌ Too sensitive

Example:

```text
Threshold = 2°
```

Result:

* false alerts
* constant vibration

---

## ❌ Too loose

Example:

```text
Threshold = 40°
```

Result:

* detects nothing

---

## ✅ Best Practice

Start around:

```text
10°–15°
```

then tune experimentally.

---

# STEP 7 — Add Stability Delay

VERY IMPORTANT.

Without this:

* one sudden movement triggers vibration

Bad experience.

---

# SOLUTION

Only alert if bad posture continues for some time.

Example:

```text
bad posture for 3 seconds
```

then vibrate.

---

# LOGIC

```text
Bad posture detected
        ↓
Start timer
        ↓
If posture still bad after 3 sec:
    trigger alert
Else:
    ignore
```

---

# WHY THIS IS IMPORTANT

Prevents:

* false positives
* random alerts
* temporary movement detection

---

# THINGS TO CAREFUL ABOUT

## ❌ Avoid blocking delays

Do NOT use huge:

```cpp
delay(3000);
```

This freezes ESP32.

---

## ✅ Use millis()

Use non-blocking timers.

---

# STEP 8 — Add State Management

Now create posture states.

Example:

```cpp
enum PostureState {
    GOOD,
    WARNING,
    BAD
};
```

---

# WHY THIS IS IMPORTANT

Makes logic cleaner.

Instead of:

```text
random if else chaos
```

you get:

```text
organized system behavior
```

---

# STEP 9 — OLED Logic

Now connect posture state with display.

---

# EXAMPLE

## GOOD

```text
POSTURE GOOD
```

---

## BAD

```text
SLOUCHING
STRAIGHTEN BACK
```

---

## CALIBRATION

```text
CALIBRATING...
SIT STRAIGHT
```

---

# THINGS TO CAREFUL ABOUT

## ❌ Avoid screen flickering

Do not fully redraw screen too rapidly.

---

## ✅ Update only when state changes

Much smoother.

---

# STEP 10 — Vibration Logic

Now connect bad posture with motor.

---

# BEST PRACTICE

Use:

* short pulses
* not continuous vibration

Example:

```text
vibrate
pause
vibrate
```

---

# WHY?

Continuous vibration:

* annoys user
* drains battery
* heats motor

---

# GOOD PATTERN

```text
200ms ON
300ms OFF
200ms ON
```

---

# STEP 11 — Add Sensor Smoothing

MPU6050 data is noisy.

Without smoothing:

* posture rapidly changes GOOD/BAD

---

# SOLUTION

Use filtering.

Simplest:

```text
Moving average
```

or

```text
Low-pass filter
```

---

# EXAMPLE

Instead of:

```text
5 7 6 25 8 7
```

Filtered:

```text
6 6 7 8 7 7
```

---

# THINGS TO CAREFUL ABOUT

## ❌ Over smoothing

Too much filtering:

* slow response

---

## ✅ Balanced filtering

Enough to reduce noise but still responsive.

---

# STEP 12 — Real Body Testing

THIS IS MANDATORY.

Desk testing is not enough.

---

# TEST THESE CASES

## Test 1

Straight sitting.

---

## Test 2

Slow slouch.

---

## Test 3

Fast bend.

---

## Test 4

Walking.

---

## Test 5

Turning body.

---

## Test 6

Standing.

---

# GOAL

Find:

* false alerts
* unstable readings
* wrong thresholds

---

# STEP 13 — Tune Thresholds

Real-world tuning is EVERYTHING.

You will likely change:

* threshold angles
* smoothing strength
* alert delay

many times.

This is normal.

---

# STEP 14 — Optimize Power Usage (Optional in Phase 2)

Not critical now, but keep in mind:

* OLED consumes power
* vibration motor consumes power
* WiFi/Bluetooth drains ESP32 battery

Later:

* deep sleep
* dim display
* lower refresh rate

---

# FINAL EXPECTED OUTPUT OF PHASE 2

By the end of Phase 2:

Your device should:

✅ detect posture angle
✅ save reference posture
✅ compare angles
✅ identify slouching
✅ avoid false alerts
✅ vibrate intelligently
✅ display posture status properly
✅ work reliably on real body movement

---

# BIGGEST MISTAKES THAT DESTROY THESE PROJECTS

## ❌ No calibration system

Everyone has different posture.

---

## ❌ No filtering

Results become unstable.

---

## ❌ Threshold too sensitive

Constant false alerts.

---

## ❌ Using delay()

Freezes device.

---

## ❌ Testing only on desk

Real body motion is completely different.

---

# WHAT YOUR TEAM SHOULD DO NOW

## Team Task Breakdown

| Member   | Task                         |
| -------- | ---------------------------- |
| Person 1 | Sensor angle testing         |
| Person 2 | Calibration button logic     |
| Person 3 | OLED posture display         |
| Person 4 | Vibration logic              |
| Person 5 | Threshold + smoothing tuning |

Then combine everything.

---

# AFTER PHASE 2

Once this phase works properly:

Your project becomes:

```text
ACTUAL WORKING SMART WEARABLE
```

Then next phases become:

* better UX
* mobile app
* posture analytics
* battery optimization
* cloud connectivity
* ML improvements (optional later)
