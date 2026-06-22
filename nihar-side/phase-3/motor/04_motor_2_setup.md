Bro, the second motor is exactly the same circuit, just use a different GPIO pin and a different transistor.

### Motor 1 (already working)

```text
ESP32 GND
    |
Leg 1 (left) of Transistor #1

ESP32 GPIO25
    |
   1kΩ
    |
Leg 2 (middle) of Transistor #1

Leg 3 (right) of Transistor #1
    |
Motor 1 Blue

Motor 1 Red
    |
ESP32 3.3V
```

---

### Motor 2 (new)

```text
ESP32 GND
    |
Leg 1 (left) of Transistor #2

ESP32 GPIO26
    |
   1kΩ
    |
Leg 2 (middle) of Transistor #2

Leg 3 (right) of Transistor #2
    |
Motor 2 Blue

Motor 2 Red
    |
ESP32 3.3V
```

### Diodes

Motor 1 gets its own diode:

```text
Stripe side     -> Motor 1 Red (3.3V side)
Non-stripe side -> Motor 1 Blue
```

Motor 2 gets its own diode:

```text
Stripe side     -> Motor 2 Red (3.3V side)
Non-stripe side -> Motor 2 Blue
```

### Shared connections

Both motors can share:

```text
ESP32 3.3V
ESP32 GND
Battery
TP4056
```

### Test code

```cpp
#define MOTOR1 25
#define MOTOR2 26

void setup() {
  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR2, OUTPUT);
}

void loop() {

  digitalWrite(MOTOR1, HIGH);
  delay(500);
  digitalWrite(MOTOR1, LOW);

  delay(500);

  digitalWrite(MOTOR2, HIGH);
  delay(500);
  digitalWrite(MOTOR2, LOW);

  delay(500);
}
```

This will make Motor 1 vibrate, then Motor 2 vibrate.

For your posture project, GPIO25 could be the **left shoulder motor** and GPIO26 the **right shoulder motor**.
