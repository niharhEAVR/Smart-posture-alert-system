Perfect. From your photo, you have a **PN2222A / 2222A** transistor.

Hold it exactly like in your photo:

```text
Flat side facing you
(letters visible)

  CPN
 2222A

  |  |  |
  1  2  3
```

For this PN2222A, use:

```text
1 = Emitter
2 = Base
3 = Collector
```

### Now wire it like this

```text
ESP32 GND
    |
    |
Leg 1 (left)

ESP32 GPIO25
    |
   1kΩ resistor
    |
Leg 2 (middle)

Leg 3 (right)
    |
Motor Blue Wire

Motor Red Wire
    |
ESP32 3.3V
```

### Diode (1N4007)

The diode has a **silver stripe** on one end.

Connect:

```text
Silver stripe side  -> Motor Red Wire (3.3V side)

Other side          -> Motor Blue Wire
```

### Super simple summary

```text
Motor Red  -> 3.3V

Motor Blue -> Right leg of transistor

Left leg of transistor -> GND

Middle leg of transistor -> 1k resistor -> GPIO25

Diode across motor
```

### Test code

```cpp
#define MOTOR 25

void setup() {
  pinMode(MOTOR, OUTPUT);
}

void loop() {
  digitalWrite(MOTOR, HIGH);
  delay(1000);

  digitalWrite(MOTOR, LOW);
  delay(1000);
}
```

If you want, send a photo of your **breadboard with the ESP32, transistor, motor, resistor, and diode placed on it**, and I'll check every connection before you power it up.



---
---
---
---
---


