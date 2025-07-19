# 📡 Wireless Water Tank Level Monitoring System — Algorithm

This document outlines the complete algorithm for the Wireless Water Tank Level Monitoring System using **Arduino Uno**, **ESP8266 modules**, and an **OLED Display**.

---

## 🔧 1. System Initialization

### Arduino Uno
- Initializes ultrasonic distance sensor (HC-SR04 or DYP-A02YYUW).
- Sets up serial communication with ESP8266 (transmitter).

### ESP8266 (Transmitter Side)
- Connects to Wi-Fi network using SSID and password.
- Starts a UDP client to send distance data to the receiver ESP.

### ESP8266 (Receiver Side)
- Connects to same Wi-Fi network.
- Starts a UDP server to listen for incoming data packets.
- Initializes the 0.96" OLED display using the SSD1306 driver.

---

## 📏 2. Distance Measurement (Arduino Uno)

- Triggers ultrasonic pulse via the sensor.
- Measures duration of echo pulse.
- Calculates the distance using the speed of sound:

  \[
  \text{Distance} = \frac{\text{Duration} \times \text{Speed of Sound}}{2}
  \]

- Applies filtering:
  - Averages readings (e.g., 10 readings).
  - Rejects any out-of-range values (e.g., > 120 cm).

---

## 🔁 3. Send Data to ESP8266 via Serial

- Converts distance (float) to string format.
- Sends the distance to the ESP8266 using `Serial.println()`.

---

## 🌐 4. Transmit Distance via Wi-Fi (ESP8266 Transmitter)

- Reads distance from serial input.
- Formats and sends the distance using UDP protocol.
- Specifies receiver IP and port.

---

## 📲 5. Receive & Display Data (ESP8266 Receiver)

- Listens for incoming UDP packets.
- Parses the distance from the received message.
- Maps the distance to:
  - Water height
  - Percentage filled
  - Water volume (liters)

### Example Calculation
- `maxDistance = 116.8 cm` (empty tank reference)
- `waterHeight = maxDistance - measuredDistance`
- `percentage = (waterHeight / maxDistance) × 100`
- `liters = (percentage / 100) × tankCapacityLiters`

### OLED Display Format
- Line 1: `"Water Tank:"`
- Line 2: Water in liters (font size 2)
- Line 3: Water level percentage (font size 3)

---

## 🔁 6. Loop and Update

- Runs in continuous loop:
  - Measure → Send → Receive → Display
- Refreshes every 1–2 seconds

---

## ⚠️ 7. Error Handling (Optional)

- If serial input is missing → show `"Waiting for data..."`.
- If distance > `maxDistance` → ignore or show `"Sensor Error"`.
- If Wi-Fi fails → reconnect or show `"Disconnected"` on OLED.

---

## 🧠 Notes

- Wi-Fi-based UDP transmission is preferred for simplicity and speed.
- OLED font sizes can be adjusted for readability.
- Ensure both ESP modules are in the same subnet or use an external router or hotspot.

---

