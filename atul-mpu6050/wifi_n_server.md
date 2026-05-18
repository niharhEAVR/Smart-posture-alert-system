# 🚀 STEP 11: Add WiFi + Send Data (ESP32)

We’ll extend your existing code.

---

## 📡 1. Add WiFi + HTTP Libraries

```cpp
#include <WiFi.h>
#include <HTTPClient.h>
```

---

## 🌐 2. WiFi Credentials

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

---

## 🔗 3. Your Server Endpoint

For now, assume:

```cpp
const char* serverURL = "http://YOUR_SERVER_IP:3000/data";
```

(We’ll build this server next)

---

## ⚙️ 4. Connect WiFi (in `setup()`)

```cpp
WiFi.begin(ssid, password);

Serial.print("Connecting to WiFi");
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}

Serial.println("\nConnected!");
Serial.println(WiFi.localIP());
```

---

## 📤 5. Function to Send Data

```cpp
void sendData(float pitch, bool slouch) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    String json = "{";
    json += "\"pitch\":" + String(pitch) + ",";
    json += "\"slouch\":" + String(slouch ? "true" : "false");
    json += "}";

    int httpResponseCode = http.POST(json);

    Serial.print("HTTP Response: ");
    Serial.println(httpResponseCode);

    http.end();
  }
}
```

---

## 🎯 6. Trigger Sending (inside loop)

Modify your event logic:

```cpp
if (slouchTime > 5 && !isSlouching) {
  Serial.println("SLOUCHING DETECTED");
  isSlouching = true;

  sendData(pitch_filtered, true);
}

if (isSlouching && pitch_filtered <= baseline + 5) {
  Serial.println("POSTURE CORRECTED");
  isSlouching = false;

  sendData(pitch_filtered, false);
}
```

# 🌐 STEP 12: Build a Simple Backend (Node.js)


## 📦 Install Node.js + Express

```bash
npm init -y
npm install express
```


## 🧾 `server.js`

```js
const express = require("express");
const app = express();

app.use(express.json());

let history = [];

app.post("/data", (req, res) => {
  const entry = {
    pitch: req.body.pitch,
    slouch: req.body.slouch,
    time: new Date()
  };

  history.push(entry);

  console.log("Received:", entry);

  res.send({ status: "ok" });
});

app.get("/data", (req, res) => {
  res.json(history);
});

app.listen(3000, () => {
  console.log("Server running on port 3000");
});
```



# 📊 STEP 13: View Data (Basic Dashboard)

Open browser:

```
http://YOUR_SERVER_IP:3000/data
```

👉 You’ll see JSON like:

```json
[
  {
    "pitch": 22.3,
    "slouch": true,
    "time": "2026-05-18T..."
  }
]
```