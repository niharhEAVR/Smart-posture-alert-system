
# 🎯 STEP 10: Calibration + Slouch Detection Logic

Right now you only have:

```text
angle → printed
```

We upgrade it to:

```text
angle → baseline → threshold → time → event
```

---

# 🧠 1. Add State Variables (Global Section)

Put these at the top of your code:

```cpp
float baseline = 0;
bool calibrated = false;

float slouch_threshold = 0;

float slouchTime = 0;
bool isSlouching = false;
```

---

# 🪑 2. Calibration (Define “Good Posture”)

We’ll capture baseline when user is sitting straight.

### Add this inside `loop()`:

```cpp
if (!calibrated) {
  Serial.println("Sit straight for calibration...");
  delay(3000); // give time to sit properly

  baseline = pitch_filtered;
  slouch_threshold = baseline + 15; // adjustable

  calibrated = true;

  Serial.print("Baseline set to: ");
  Serial.println(baseline);
}
```

---

# 🎯 3. Slouch Detection Logic

Add this **after your filter + stability check**:

```cpp
if (calibrated && stable) {

  if (pitch_filtered > slouch_threshold) {
    slouchTime += dt;
  } else {
    slouchTime = 0;
  }

}
```

---

# ⏱️ 4. Trigger Events (THIS is your core feature)

```cpp
// Detect slouch start
if (slouchTime > 5 && !isSlouching) {
  Serial.println("SLOUCHING DETECTED");
  isSlouching = true;
}

// Detect correction
if (isSlouching && pitch_filtered <= baseline + 5) {
  Serial.println("POSTURE CORRECTED");
  isSlouching = false;
}
```

---

# 🔍 5. Debug Output (Don’t Skip This)

Replace your print with:

```cpp
Serial.print("Pitch: ");
Serial.print(pitch_filtered);

Serial.print(" | Baseline: ");
Serial.print(baseline);

Serial.print(" | Threshold: ");
Serial.print(slouch_threshold);

Serial.print(" | Time: ");
Serial.print(slouchTime);

Serial.print(" | State: ");
Serial.println(isSlouching ? "SLOUCH" : "OK");
```

---

# 🧪 6. How to Test Properly

### Step-by-step:

1. Upload code
2. Sit straight → wait 3 sec (calibration)
3. Slowly slouch forward

👉 You should see:

* Time increasing
* After ~5 sec → **SLOUCHING DETECTED**

4. Sit straight again

👉 You should see:

* **POSTURE CORRECTED**

---

# ⚠️ Tuning (This Matters A LOT)

### Threshold:

```cpp
baseline + 10  → sensitive  
baseline + 20  → less sensitive
```

### Time:

```cpp
3 sec  → fast detection  
5–8 sec → realistic posture correction
```