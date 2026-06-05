# PHASE 4 — Portable Power System

This phase converts your project from:

```text
Prototype connected to laptop
```

into:

```text
Actual wearable standalone device
```

Until now your ESP32 is probably powered through:

* USB cable
* Laptop
* Power bank

But wearable devices must:

* run independently
* be rechargeable
* be compact
* be portable

That is exactly what Phase 4 does.

---

# MAIN GOALS OF PHASE 4

You will add:

| Component       | Purpose                      |
| --------------- | ---------------------------- |
| LiPo Battery    | Portable power source        |
| TP4056 Module   | Safe charging circuit        |
| Power Switch    | Turn device ON/OFF           |
| Voltage Routing | Proper power distribution    |
| Battery Safety  | Prevent overcharge/discharge |

---

# BIG PICTURE

Final power system becomes:

```text
USB Charger
     ↓
TP4056 Charging Module
     ↓
LiPo Battery
     ↓
ESP32
     ↓
MPU6050 + OLED + Motor
```

---

# WHAT IS A LiPo BATTERY?

LiPo = Lithium Polymer battery.

Used in:

* smartwatches
* wireless earbuds
* drones
* fitness bands
* IoT devices

---

# WHY LiPo?

Because it is:

✅ Rechargeable
✅ Small
✅ Lightweight
✅ High energy density
✅ Perfect for wearables

---

# COMMON LiPo SPECIFICATIONS

You will usually use:

| Specification       | Typical Value  |
| ------------------- | -------------- |
| Voltage             | 3.7V           |
| Full charge voltage | 4.2V           |
| Capacity            | 500mAh–2000mAh |

---

# RECOMMENDED BATTERY

For your posture device:

```text
3.7V 1000mAh LiPo
```

is ideal.

Why?

Because:

* compact
* enough backup
* safe current range
* lightweight wearable

---

# UNDERSTANDING BATTERY VOLTAGE

This is VERY IMPORTANT.

---

# LiPo Voltage Reality

People say:

```text
3.7V battery
```

But actual voltage changes:

| Battery State | Voltage |
| ------------- | ------- |
| Empty         | ~3.0V   |
| Normal        | ~3.7V   |
| Fully Charged | 4.2V    |

---

# IMPORTANT QUESTION

Can ESP32 run directly from LiPo?

Answer:

# YES — but depends on board.

Most ESP32 DevKit boards have:

* onboard voltage regulator

Meaning:

You can power through:

```text
VIN / 5V pin
```

OR sometimes directly through:

```text
3V3 pin
```

But there are important details.

---

# WHAT IS TP4056?

This is the charging module.

Without it:

```text
Directly charging LiPo = dangerous
```

because lithium batteries need controlled charging.

---

# TP4056 DOES:

| Feature                  | Purpose                 |
| ------------------------ | ----------------------- |
| Charging control         | Charges battery safely  |
| Overcharge protection    | Stops at 4.2V           |
| Overdischarge protection | Prevents battery damage |
| Short-circuit protection | Safety                  |
| USB charging             | Easy charging           |

---

# VERY IMPORTANT

Buy:

# TP4056 WITH PROTECTION

Not the cheap unprotected one.

---

# HOW TO IDENTIFY PROTECTED VERSION

Protected TP4056 usually has:

```text
6 pins
```

instead of:

```text
4 pins
```

---

# PINS OF TP4056

| Pin  | Purpose           |
| ---- | ----------------- |
| IN+  | USB power input + |
| IN-  | USB power input - |
| B+   | Battery positive  |
| B-   | Battery negative  |
| OUT+ | Output positive   |
| OUT- | Output negative   |

---

# BIG CONNECTION DIAGRAM

```text
USB Cable
    ↓
TP4056 IN+ IN-
    ↓
LiPo connected to B+ B-
    ↓
ESP32 connected to OUT+ OUT-
```

---

# VERY IMPORTANT CONCEPT

# NEVER POWER ESP32 DIRECTLY FROM BATTERY WHILE BYPASSING TP4056

Wrong:

```text
Battery → ESP32 directly
```

Correct:

```text
Battery → TP4056 → ESP32
```

Why?

Because TP4056 protection circuitry matters.

---

# POWERING ESP32

Now comes an important hardware decision.

---

# OPTION 1 — Through 5V/VIN Pin

If using boost converter.

Flow:

```text
Battery (3.7V)
    ↓
Boost converter to 5V
    ↓
ESP32 VIN
```

More stable.

---

# OPTION 2 — Direct 3.7V

Some ESP32 boards can run directly from LiPo.

But:

* unstable sometimes
* depends on regulator
* brownout issues possible

---

# RECOMMENDED FOR BEGINNERS

Use:

# BOOST CONVERTER

Example:

```text
MT3608 boost converter
```

---

# FINAL SAFE POWER FLOW

```text
LiPo Battery
      ↓
TP4056
      ↓
Boost Converter (3.7V → 5V)
      ↓
ESP32 VIN
```

This is the safest professional setup.

---

# WHY BOOST CONVERTER?

Because ESP32 sometimes needs:

```text
High current bursts
```

especially during:

* WiFi
* Bluetooth
* vibration motor activation

Battery voltage may drop suddenly.

Boost converter gives stable 5V.

---

# POWER SWITCH

VERY IMPORTANT.

Without switch:

* device always ON
* battery drains continuously

---

# CONNECTION

Switch is placed between:

```text
TP4056 OUT+ → SWITCH → Boost converter
```

---

# FINAL REALISTIC CIRCUIT

```text
USB Charging
      ↓
TP4056
      ↓
LiPo Battery
      ↓
Power Switch
      ↓
Boost Converter
      ↓
ESP32
      ↓
Sensors + OLED + Motor
```

---

# BATTERY BACKUP ESTIMATION

Example:

Suppose:

| Component        | Current |
| ---------------- | ------- |
| ESP32            | 80mA    |
| OLED             | 20mA    |
| MPU6050          | 5mA     |
| Motor occasional | 100mA   |

Average:

```text
~150mA
```

If battery is:

```text
1000mAh
```

Approx backup:

\text{Battery Life} = \frac{1000\text{mAh}}{150\text{mA}} \approx 6.7\text{ hours}

Realistically:

```text
5–6 hours
```

after losses.

---

# IMPORTANT SAFETY RULES

---

# NEVER:

❌ puncture LiPo battery
❌ short battery terminals
❌ overcharge battery
❌ reverse polarity
❌ use damaged/swollen battery
❌ solder directly on bare battery unless experienced

---

# ALWAYS:

✅ use TP4056 protection
✅ insulate connections
✅ use proper polarity
✅ test with multimeter
✅ keep battery cool

---

# TESTING PHASE 4

---

# TEST 1 — Charging

Plug USB into TP4056.

Check LEDs:

| LED        | Meaning       |
| ---------- | ------------- |
| Red        | Charging      |
| Blue/Green | Fully charged |

---

# TEST 2 — Portable Power

Disconnect laptop USB.

Device should still run.

That means:

```text
Battery power successful
```

---

# TEST 3 — Motor Stability

When vibration motor activates:

* ESP32 should NOT restart
* OLED should NOT flicker

If it does:

* insufficient current
* weak battery
* no capacitor
* poor wiring

---

# COMMON PROBLEMS

---

# Problem 1 — ESP32 Restarting

Cause:

```text
Voltage drop
```

Solution:

* better battery
* boost converter
* capacitor near ESP32

---

# Problem 2 — Motor Noise

Cause:

```text
Motor electrical noise
```

Solution:

* diode
* capacitor
* separate grounding care

---

# Problem 3 — TP4056 Heating

Cause:

* high charging current
* bad wiring
* short circuit

---

# PHASE 4 SUCCESS CONDITION

Your project is successful when:

✅ Runs without laptop
✅ Charges via USB
✅ Battery safely powers system
✅ Portable wearable operation works
✅ Stable posture detection continues
✅ Alerts still function correctly

---

# WHAT YOUR PROJECT BECOMES NOW

After Phase 4, your project becomes:

# A real standalone wearable IoT device.

Not just a breadboard prototype anymore.

Now it behaves like:

* fitness tracker
* smart wearable
* posture correction band

---

# NEXT POSSIBLE PHASES

After this you can move into:

| Future Phase | Upgrade                   |
| ------------ | ------------------------- |
| Phase 5      | Bluetooth App             |
| Phase 6      | Cloud/Firebase            |
| Phase 7      | AI posture analytics      |
| Phase 8      | PCB design                |
| Phase 9      | 3D printed enclosure      |
| Phase 10     | Production-ready wearable |
