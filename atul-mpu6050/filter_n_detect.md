# 🎯 STEP 9: Stabilize the Angle (Filtering + Timing)

Right now your system is:

```text
Sensor → Angle → (noisy, unreliable)
```

We convert it into:

```text
Sensor → Filter → Stable Angle → (usable)
```

---

# ⏱️ 1. Add Proper Timing (`dt`)

You need time difference between readings.

```cpp
unsigned long lastTime = 0;
float dt = 0;

void loop() {
  unsigned long now = millis();
  dt = (now - lastTime) / 1000.0;
  lastTime = now;

  readMPU();
```

👉 This becomes important later (even if not fully used yet)

---

# 🧼 2. Low-Pass Filter (Smooth the Noise)

This removes jitter.

Add a global variable:

```cpp
float pitch_filtered = 0;
```

Then update:

```cpp
float pitch_raw = atan2(ax_g, sqrt(ay_g * ay_g + az_g * az_g)) * 180 / PI;

// Low-pass filter
pitch_filtered = 0.9 * pitch_filtered + 0.1 * pitch_raw;
```

---

# 🔍 3. Detect Movement (Critical Insight)

We only trust posture when user is relatively still.

```cpp
float total_acc = sqrt(ax_g * ax_g + ay_g * ay_g + az_g * az_g);
```

Check stability:

```cpp
bool stable = abs(total_acc - 1.0) < 0.1;
```

👉 Why?

* Gravity = ~1g
* If it deviates → user is moving

---

# 🧪 4. Print Debug Info (Very Important)

```cpp
Serial.print("Pitch Raw: "); Serial.print(pitch_raw);
Serial.print(" | Filtered: "); Serial.print(pitch_filtered);
Serial.print(" | Stable: "); Serial.println(stable);
```

---

# 🧠 What You Should Observe

### When sitting still:

* `stable = true`
* `pitch_filtered` smooth and steady

### When moving:

* `stable = false`
* values fluctuate → ignored later

---

# ⚠️ Why This Step Matters More Than It Looks

Without this:

* You’ll detect slouch when someone scratches their head
* Or shifts slightly
* Or breathes deeply

With this:

* You detect **only sustained posture changes**

---

# 🧱 Your System Now

You’ve built:

```text
MPU6050 → Raw Data → Angle → Filter → Stability Check
```

This is already **real embedded signal processing**.

---

# ▶️ NEXT STEP (Now it gets interesting)

Now we add **intelligence**:

👉 Calibration (what is “good posture”?)
👉 Threshold (what is “bad posture”?)
👉 Time logic (when is it actually slouching?)
