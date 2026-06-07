Let's go through the code line by line like you're explaining it in a viva.

```cpp
#define MOTOR 25
```

### What it does

Creates a name called `MOTOR`.

Instead of writing `25` everywhere, we can write `MOTOR`.

So:

```cpp
digitalWrite(MOTOR, HIGH);
```

means

```cpp
digitalWrite(25, HIGH);
```

---

```cpp
void setup() {
  pinMode(MOTOR, OUTPUT);
}
```

### What happens here?

`setup()` runs **only once** when the ESP32 starts.

```cpp
pinMode(MOTOR, OUTPUT);
```

tells the ESP32:

> "GPIO25 will send signals OUT to other devices."

Without this, GPIO25 doesn't know whether it's an input or output pin.

---

```cpp
void loop() {
```

`loop()` runs forever.

Think:

```text
Start
 ↓
loop()
 ↓
loop()
 ↓
loop()
 ↓
Again and again...
```

---

```cpp
digitalWrite(MOTOR, HIGH);
```

This sends **3.3V** to GPIO25.

GPIO25 becomes HIGH.

Current flows:

```text
GPIO25
  ↓
1k resistor
  ↓
Transistor base
```

The transistor turns ON.

Motor gets power.

✅ Motor vibrates.

---

```cpp
delay(1000);
```

Waits for 1000 milliseconds.

```text
1000 ms = 1 second
```

So the motor keeps vibrating for 1 second.

---

```cpp
digitalWrite(MOTOR, LOW);
```

GPIO25 becomes 0V.

No current enters the transistor base.

Transistor turns OFF.

Motor loses power.

❌ Motor stops.

---

```cpp
delay(1000);
```

Wait another 1 second.

Motor stays OFF.

---

Then the loop repeats:

```text
Motor ON  → 1 second
Motor OFF → 1 second
Motor ON  → 1 second
Motor OFF → 1 second
...
```

---

## Flow of the entire program

```text
ESP32 starts
      ↓
Configure GPIO25 as OUTPUT
      ↓
Turn motor ON
      ↓
Wait 1 second
      ↓
Turn motor OFF
      ↓
Wait 1 second
      ↓
Repeat forever
```

---

## Viva Question: Why does `HIGH` turn the motor ON?

Because:

```text
GPIO25 HIGH
      ↓
Current enters transistor base
      ↓
Transistor acts as a closed switch
      ↓
Current flows through motor
      ↓
Motor vibrates
```

And:

```text
GPIO25 LOW
      ↓
No base current
      ↓
Transistor acts as an open switch
      ↓
No motor current
      ↓
Motor stops
```

### Exam/Viva one-liner

> The program configures GPIO25 as an output pin and repeatedly sends HIGH and LOW signals. HIGH turns the transistor ON, allowing current to flow through the vibration motor, while LOW turns the transistor OFF, stopping the motor. The `delay(1000)` function keeps each state active for one second.
