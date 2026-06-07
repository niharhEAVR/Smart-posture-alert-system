Perfect bro. This is the **good TP4056 version with protection**.

I can see:

```text
B+
B-
OUT+
OUT-
```

So here's exactly how it works.

## Battery Connection

Your LiPo battery goes here:

```text
Battery Red   -> B+
Battery Black -> B-
```

That's all.

---

## Charging the Battery

Plug a USB-C cable into the TP4056.

```text
USB-C
  ↓
TP4056
  ↓
Battery charges
```

You don't connect the ESP32 for charging. The TP4056 handles it.

---

## Taking Power Out

The battery power comes out from:

```text
OUT+
OUT-
```

Think of these as:

```text
OUT+ = battery positive
OUT- = battery negative
```

Anything you want to power connects here.

---

## If you only want to test

Take a multimeter.

Measure:

```text
OUT+
OUT-
```

You should see around:

```text
3.7V to 4.2V
```

depending on battery charge.

---

## Complete battery setup

```text
LiPo Battery
    |
    +---- Red ---- B+
    |
    +---- Black -- B-

TP4056

OUT+ ---- Power Output +
OUT- ---- Power Output -
```

That's literally the whole battery system.

---

## Next step

Now the important question is:

**What exact ESP32 board do you have?**

Send a photo of the ESP32 board.

Then I'll tell you:

```text
OUT+ -> which ESP32 pin
OUT- -> which ESP32 pin
```

and whether you need a boost converter or can run directly from the battery.

For now, you've already understood 90% of the battery setup:

**Battery → B+/B-**
**Power comes out from OUT+/OUT-**
**USB-C charges the battery.**
