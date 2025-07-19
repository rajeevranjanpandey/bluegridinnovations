# Source Code: Wireless Water Tank Monitoring System

wireless water tank level monitoring system.

## 📁 Files

### ✅ `transmitter_esp8266.ino`
- This sketch runs on an ESP8266 module connected to Arduino Uno.
- It reads distance (in cm) sent over Serial from the Uno and forwards it via UDP.
- The receiver ESP8266 uses this to update the OLED display.

### ✅ `receiver_esp8266.ino`
- This sketch runs on another ESP8266 with an OLED display.
- It listens for UDP packets and displays:
  - Water level in liters
  - Tank fullness in %
- Implements simple averaging over 5 samples to smooth readings.

### ✅ `arduino_uno_serial_sender.ino`
- Code for Arduino Uno.
- Measures water level using an ultrasonic sensor (HC-SR04 or DYP-A02YYUW).
- Sends measured distance over serial to the ESP8266 (TX to RX).

---

## 🔧 How It Works

1. Arduino Uno continuously measures water level using an ultrasonic sensor.
2. It sends the measured distance in cm to ESP8266 via Serial.
3. The transmitter ESP8266 forwards this data via UDP.
4. The receiver ESP8266 receives the data and shows it on an OLED display.
5. The distance is converted to liters and percentage using tank dimensions.

---

## 🧠 Code Features

- UDP-based communication over Wi-Fi.
- OLED display with Adafruit libraries.
- Adjustable tank dimensions.
- Simple noise filtering using averaging.
- Modular and easily adaptable.

---

## 📦 Libraries Used

- `ESP8266WiFi.h`
- `WiFiUDP.h`
- `Adafruit_SSD1306.h`
- `Adafruit_GFX.h`

