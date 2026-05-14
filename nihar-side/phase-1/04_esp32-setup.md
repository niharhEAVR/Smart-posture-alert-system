# Video for Hardware connection: [click here](https://www.youtube.com/watch?v=CD8VJl27n94)


# ESP32 DevKit V1 Setup Documentation

## Smart Posture Detection Wearable Project

---

# 1. Introduction

The ESP32 DevKit V1 is the main controller used in the Smart Posture Detection Wearable system.

It acts as the “brain” of the device and is responsible for:

* reading sensor data,
* processing posture angle,
* controlling the OLED display,
* handling alerts,
* and managing future Bluetooth/WiFi features.

The ESP32 was selected because it provides:

* built-in WiFi,
* built-in Bluetooth,
* multiple GPIO pins,
* fast processing,
* low power consumption,
* and excellent compatibility with IoT projects.

---

# 2. ESP32 DevKit V1 Hardware Overview

Typical ESP32 DevKit V1 board:

![Image](https://images.openai.com/static-rsc-4/YIYJJUyVLOSYNM9xniRV7RkOXQCJZPFhNrbRH4FDCBfoD4eYuwZH5_QSwskbImsXSfv6WWwAWT5ghnTaeyu3gPGFZNacjd_IOht8EDv2VlcF3ZD_nliGSdbg1HHiylzWiqJhu4xl9hVkPBvbky_znQ8ZCYci_Em5ybmj2EbpHsYU3zZBEAGY9TwPr8KoJDtn?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/y9Qz5zHPwBP33BnUZYaIzGXmopqL8YY1nVCM6odQs2zLF6hj_Ut8fiiQNOsGa8bovRZv9XU3yl9BYncQvMf7J4GZTwCgm5-YnAEJFdK_-DVGvXFnCbSkJZIUKrpGG6PUa_98XtI5y-0FATpHKpo9AMbPKnS6zuTdMIFJwPPAQucGPgdjxKMS89Snsxmnj9NL?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/1VqTsQLgNuKS4EKGK87U1O3voGjPFcQm7K1zTanxEEf-Ow74MBMx60zgkPm5c4pYFP0kj-CwVTLsjQB8eTryCRYYmVGb9DVTHWEfyG2-OlQI8K4Di04DrAmQUTL9bf30LqAkaTklco5KuMorofjwW3a25XVzOJSXiaLsgVDyKTkJiMGTGg41B0pwXkFnpecU?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/YVZOhYljVay3XsrrGV61wRUk0GOkTO_sIlzJD8H_Lel0OafYWN2uGweU7Mzs_roqLMMdCkQqo_u2lohcvQK5zyPar8COTEklPmFuKD-_oZnT4BiK9pt0riYAwfuXOqrWcR2pYv_NrHGYUafRecnTcRMziYffhXtMhGtl32qy5zBlPB09G2nAXuSoVS8KGhTO?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/fLitRfLFiLceJMoinAHU3s0jAefDhohTvkxyfKkwPjD4K_oU1xVFXb5LNrNJLdHjMR_xXgzax7Xxe47e4tOyNVqWBU5shtf2fgvwMTm7-yynet-rwEq9o2cqlU-WR_d7ZG12HGYE0PKS8kcby3k8wvCAeZJgIAZXh3UfByL0BBhKAkNX99MDLXD30WBIIvtd?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/pxfKtuC0sRFxm2arH_H31PmPxHkDL0akwewHEegsXyf1PjMzvO4zrym3YQsZaXpYAY9TMMxTYocahw6khhKYdg32VCGcuQKWTji4X_lp5Fg4jzfcliHd11Tv9GELjtVed-v_Jq90To3G-Bo4-_C25Bkm56f8bgqnuAvH8DyleleQ4rybRFFMZL5RCqXXgVXf?purpose=fullsize)

---

# 3. Important ESP32 Parts

| Part           | Function                 |
| -------------- | ------------------------ |
| Micro USB Port | Power and code uploading |
| GPIO Pins      | Input/output connections |
| 3.3V Pin       | Supplies 3.3V power      |
| GND Pin        | Ground connection        |
| EN Button      | Reset button             |
| BOOT Button    | Upload/flash mode        |

---

# 4. USB Cable Requirement

The ESP32 is connected to the laptop using a USB cable.

IMPORTANT:

The cable must support:

```text id="f58e6f"
Data Transfer
```

and not only charging.

---

# Problem with Charge-Only Cables

If a charging-only cable is used:

* ESP32 will receive power,
* LEDs may glow,
* but laptop will not detect the board.

This causes:

* COM port missing,
* upload failure,
* connection errors.

---

# Recommended Cable

Most ESP32 DevKit V1 boards use:

```text id="ut5yl5"
Micro USB Data Cable
```

A short and good-quality cable is preferred for stable communication.

---

# 5. Connecting ESP32 to Laptop

Connection flow:

```text id="2vq1lh"
ESP32 → USB Data Cable → Laptop
```

After connecting:

Expected signs:

* power LED turns ON,
* laptop detects device,
* COM port appears in Arduino IDE.

---

# 6. Installing Arduino IDE

The Arduino IDE is required to write and upload code to the ESP32.

Download from:

[Arduino IDE Official Website](https://www.arduino.cc/en/software?utm_source=chatgpt.com)

After installation:
open Arduino IDE.

---

# 7. Installing ESP32 Board Package

By default, Arduino IDE does not support ESP32.

The ESP32 board package must be installed manually.

---

# Step 1 — Open Preferences

Go to:

```text id="4h4bm5"
File → Preferences
```

---

# Step 2 — Add Board URL

Inside:

```text id="0l9l4r"
Additional Boards Manager URLs
```

paste:

```text id="85i7w2"
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

Click:

```text id="w8l93q"
OK
```

---

# Step 3 — Install ESP32 Boards

Go to:

```text id="tm64ak"
Tools → Board → Boards Manager
```

Search:

```text id="zjlwmk"
ESP32
```

Install:

```text id="jlwm5x"
ESP32 by Espressif Systems
```

This enables Arduino IDE to compile and upload ESP32 programs.

---

# 8. Selecting Correct ESP32 Board

After installation:

Go to:

```text id="jlwm85"
Tools → Board
```

Select:

```text id="7ljx3f"
ESP32 Dev Module
```

This configuration matches the ESP32 DevKit V1 board.

---

# 9. Selecting COM Port

After connecting ESP32:

Go to:

```text id="jlwm9w"
Tools → Port
```

A COM port such as:

```text id="h7iw3j"
COM3
COM5
COM7
```

will appear.

Select the newly detected port.

---

# Identifying Correct COM Port

Method:

1. Disconnect ESP32.
2. Observe available ports.
3. Reconnect ESP32.
4. The newly appearing port is the ESP32 port.

---

# 10. USB Driver Installation

Some ESP32 boards require USB drivers.

Common USB chips used:

* CP2102
* CH340

Without drivers:
the laptop may fail to recognize the board.

---

# CP2102 Driver

[CP210x USB Driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?utm_source=chatgpt.com)

---

# CH340 Driver

[CH340 Driver](https://sparks.gogo.co.nz/ch340.html?utm_source=chatgpt.com)

---

# 11. First ESP32 Test Program

Before connecting sensors, the ESP32 board itself should be tested.

The onboard LED blink test is commonly used.

---

# Blink Test Code

```cpp
void setup() {

  pinMode(2, OUTPUT);
}

void loop() {

  digitalWrite(2, HIGH);
  delay(1000);

  digitalWrite(2, LOW);
  delay(1000);
}
```

---

# Purpose of Blink Test

This code checks:

* successful code compilation,
* successful upload,
* GPIO functionality,
* ESP32 operation,
* USB communication.

---

# 12. Uploading Code to ESP32

Steps:

1. Click:

```text id="jlwm3d"
✔ Verify
```

to compile code.

2. Click:

```text id="jlwmvh"
→ Upload
```

to upload program.

---

# Successful Upload Output

Arduino IDE usually shows:

```text id="jlwmr8"
Done uploading
```

The onboard LED then starts blinking.

---

# 13. BOOT Button Issue

Sometimes upload fails with:

```text id="jlwmf9"
Connecting........
```

This happens because ESP32 failed to enter flashing mode.

---

# Solution

During upload:

1. Press and hold:

```text id="jlwm8f"
BOOT
```

button.

2. Release after upload begins.

This manually enables flashing mode.

---

# 14. Common ESP32 Setup Problems

| Problem                     | Cause                | Solution                     |
| --------------------------- | -------------------- | ---------------------------- |
| No COM Port                 | Bad cable            | Use data cable               |
| Upload failed               | Wrong board selected | Select ESP32 Dev Module      |
| Device not detected         | Missing drivers      | Install CP2102/CH340 drivers |
| Continuous connecting error | Flash mode issue     | Hold BOOT button             |
| Random disconnects          | Loose cable          | Reconnect properly           |

---

# 15. Precautions During Setup

| Precaution                 | Reason                     |
| -------------------------- | -------------------------- |
| Use only data cable        | Required for uploading     |
| Avoid loose USB connection | Prevents disconnects       |
| Select correct board       | Ensures compatibility      |
| Install drivers properly   | Enables detection          |
| Do not short GPIO pins     | Prevents damage            |
| Use stable USB port        | Avoid upload interruptions |

---

# 16. Result of ESP32 Setup

After completing setup successfully:

* ESP32 powers on,
* laptop recognizes the board,
* Arduino IDE uploads code,
* onboard LED blinks correctly.

This confirms that the ESP32 development environment is properly configured and ready for IoT project development.
