# Video for Hardware connection: [click here](https://www.youtube.com/watch?v=5EwdwrRYUpE)

- [another setup](https://techlogics.net/display-text-on-a-128x64-oled-using-esp32/)




# ESP32 + OLED Setup

including:

* exact wiring
* how OLED works
* library installation
* upload code
* testing display
* debugging connection issues

step-by-step.

---

# STEP 1 — Understand the OLED Module

Your OLED is:

# 0.96" SSD1306 I2C OLED

Usually looks like this:

![Image](https://images.openai.com/static-rsc-4/s5adpE0WS1nWxMru498G26DP71B35kFyBJk9mj-MKZNqp3fH2ZOG090LtPLEPMu63-jUXQeFETCjsN02a7y9d8Js7BfCTEp_ra95qSviuEZ8EUM7rQ7iP56kOEQMHSsRq1E856EvMTbRLRhMCl3vPoSSZCAXEcb1ZNDSwh0C5bGa3h5-ZFzq-yFpU4O1sZsW?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/seze7ZFK4HFGhBw3pauOr-gSChJInw5NC7dMNHkWzrzcBagQit4xhwfwb4d4nrp71RV6YaQiEM1WGoueWQ6Ey2PBflX5gmOzHYFA6xu6nQ5MR759C7_Zc8td6UEUffZ1HYGVkDG6dRPMOdvVR0Jtv_lYKEynkeV25aZHo_S6zYo2t6k5VxVaXfFM2Sqq8anC?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/XyCzzbNBZ0XzQpKuqjbe0WUpMxF9Sxko6ddk69F2XpjU1Op6avThb_J9qSe5x4bkW9XXz69zMAGWLID9B_ifMKbR7wRGcqNKbhJbfpY4o1JuzLm4ykHtuWGik-xosmK4pTZE6h0zyQa7zZ7namBcgAtMaY6hFaHdIxS8578rjatmpSkk3NcHY4pg9ypranef?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/7dmLKcFIYzZyrv5TnLV5gtUYZ2Jv0IZZn7ybyrYCazTTQbvR2ehS3PVUBnZtmPN_Cq0veSTjd3Kq5duPWsyRxdkCJN49JJkkHQjQ830_vnqbqSczpS3y6vJ_HVQr5CGX8pwLzrl8R2ooL8JeWncJWKP-huyNyIHLFgNwq5Y3OEH2JdvEgzNf1YYfjmOBVMVP?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/_d5zEGVt9zZDKTqhqucLdo6q9C7z6FyV8LD6Ayt5yZcDyBLvjal07qVTWAloHyYDp43eUe7crYqwBtt4UqcKVd3MqFhpkQCbXnygb5xY0Y5fHNyONdYifcjOxxkVMrEqntfeADhjzFdjii_qENhmstfE270fcDb-xNiHoQSPLfNFVzfFh-pmUFOXcZH-0IUX?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/SMKv2T7l1OKE80ezPnw4WIoWsxOJ_KAbKys8o56y3VtLDpkWlNVbULax6Ki7yBGVLFFUMOwvj0o7d3axZzmLiIxZ_rql4mr7ZUVVdjivaVbVr422HGoTNAMHMxv6Iu09mMfmPGobpw2nGnTKTb0AXMOKHjRjVKwArEdbmu3_odMmv3jJix-VzUtICm7P-Mi7?purpose=fullsize)

---

# OLED PINS

Most I2C OLEDs have 4 pins:

| OLED Pin | Meaning |
| -------- | ------- |
| VCC      | Power   |
| GND      | Ground  |
| SCL      | Clock   |
| SDA      | Data    |

---

# STEP 2 — Understand OLED Communication

The OLED also uses:

# I2C Communication

Same as MPU6050.

So:

* OLED
* MPU6050

can share same:

* SDA
* SCL

lines.

---

# ESP32 I2C PINS

| Function | ESP32 Pin |
| -------- | --------- |
| SDA      | GPIO 21   |
| SCL      | GPIO 22   |

---

# STEP 3 — OLED Wiring

# CONNECTION TABLE

| OLED | ESP32   |
| ---- | ------- |
| VCC  | 3.3V    |
| GND  | GND     |
| SDA  | GPIO 21 |
| SCL  | GPIO 22 |

---

# ACTUAL CONNECTION FLOW

---

## Power

```text id="42c1mo"
ESP32 3.3V
   ↓
OLED VCC
```

---

## Ground

```text id="u5jv0f"
ESP32 GND
   ↓
OLED GND
```

---

## Communication

```text id="wqu2m9"
ESP32 GPIO21 → OLED SDA
ESP32 GPIO22 → OLED SCL
```

---

# IMPORTANT

If MPU6050 already connected:

DO NOT remove SDA/SCL.

Both devices share them.

Example:

```text id="q4f7kq"
GPIO21 → MPU6050 SDA + OLED SDA

GPIO22 → MPU6050 SCL + OLED SCL
```

That is completely normal.

---

# STEP 4 — CHECK HARDWARE CONNECTION

After wiring:

Connect ESP32 to laptop.

---

# EXPECTED RESULT

Usually OLED:

* briefly flashes
* or faintly glows

when powered.

Some OLEDs stay black until code uploaded.

That’s normal.

---

# STEP 5 — Install OLED Libraries

Open Arduino IDE.

Go:

```text id="y03cn9"
Sketch → Include Library → Manage Libraries
```

Install BOTH:

---

# 1. Adafruit SSD1306

Search:

```text id="8o7mto"
Adafruit SSD1306
```

Install it.

---

# 2. Adafruit GFX Library

Search:

```text id="n7ib6u"
Adafruit GFX
```

Install it.

---

# WHY THESE LIBRARIES ARE NEEDED

| Library      | Purpose             |
| ------------ | ------------------- |
| Adafruit GFX | drawing text/shapes |
| SSD1306      | controlling OLED    |

---

# STEP 6 — Upload OLED Test Code

Now paste this complete code:

```cpp
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

    Serial.println("OLED not found");
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

# STEP 7 — Understand This Code Properly

---

# 1.

```cpp
#include <Wire.h>
```

Enables I2C communication.

---

# 2.

```cpp
#include <Adafruit_GFX.h>
```

Graphics library.

Handles:

* text
* shapes
* drawing

---

# 3.

```cpp
#include <Adafruit_SSD1306.h>
```

OLED control library.

---

# 4.

```cpp
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
```

Defines OLED resolution.

Most common OLED:

```text id="pkol98"
128 × 64
```

---

# 5.

```cpp
Wire.begin(21,22);
```

Defines:

* SDA = GPIO21
* SCL = GPIO22

---

# 6.

```cpp
display.begin(...)
```

Starts OLED communication.

---

# 7.

```cpp
0x3C
```

This is OLED I2C address.

Most OLEDs use:

```text id="t0km8x"
0x3C
```

Some use:

```text id="9f89q4"
0x3D
```

---

# 8.

```cpp
display.clearDisplay();
```

Clears screen memory.

---

# 9.

```cpp
display.setTextSize(2);
```

Makes text bigger.

---

# 10.

```cpp
display.setCursor(10,20);
```

Sets text position.

---

# 11.

```cpp
display.println("HELLO");
```

Prints text.

---

# 12.

```cpp
display.display();
```

VERY IMPORTANT.

Actually updates OLED physically.

Without this:
nothing appears.

---

# STEP 8 — Verify Code

Click:

```text id="gw6xkk"
✔ Verify
```

Expected:

```text id="e9d2d7"
Done compiling
```

---

# STEP 9 — Upload Code

Click:

```text id="lfiv5p"
→ Upload
```

---

# IF UPLOAD FAILS

Press and hold:

```text id="3v4h0d"
BOOT
```

button while uploading.

Release after:

```text id="04z1aq"
Connecting...
```

appears.

---

# STEP 10 — EXPECTED RESULT

OLED should show:

```text id="95jvr8"
HELLO
```

on screen.

If yes:

✅ OLED working
✅ I2C communication working
✅ libraries correct
✅ ESP32 communication working

---

# STEP 11 — IF OLED SHOWS NOTHING

Most common issue.

Do this step-by-step.

---

# CHECK 1 — Wiring

Correct:

| OLED | ESP32  |
| ---- | ------ |
| VCC  | 3.3V   |
| GND  | GND    |
| SDA  | GPIO21 |
| SCL  | GPIO22 |

---

# CHECK 2 — SDA/SCL Swapped?

Very common mistake.

Correct:

```text id="5gt1wp"
GPIO21 → SDA
GPIO22 → SCL
```

---

# CHECK 3 — OLED Address Wrong?

Try replacing:

```cpp
0x3C
```

with:

```cpp
0x3D
```

Some displays use different address.

---

# CHECK 4 — Loose Breadboard Wires

Push wires firmly.

Breadboards often make weak contact.

---

# CHECK 5 — Power Issue

Some OLEDs dimly glow if powered.

If fully dead:
power may not be reaching.

---

# STEP 12 — HOW TO TEST CONNECTION STABILITY

Now the practical testing.

---

# Wiggle Test

Gently move wires.

Observe OLED.

If:

* flickering
* restarting
* disappearing

then wire loose.

---

# STEP 13 — FINAL OLED TEST

Try changing text:

```cpp
display.println("POSTURE");
```

Upload again.

If display updates:

✅ OLED fully controllable.

---

# STEP 14 — COMBINING OLED + MPU6050

Now both can run together.

Architecture becomes:

```text id="r70j8u"
MPU6050 → ESP32 → OLED
```

Sensor sends posture data.

ESP32 processes it.

OLED displays result.

---

# NEXT REAL STEP

After OLED works:

you will display:

```text id="fyjwm4"
GOOD POSTURE
```

or

```text id="6cv0fu"
SLOUCHING
```

based on MPU6050 angle data.

That’s when your actual smart posture system starts becoming real.
