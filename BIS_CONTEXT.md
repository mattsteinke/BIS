# BIS Project Context

## Project

BIS is a platform for kinetic sculptures, robotic musical instruments,
interactive installations, and experimental control systems.

---

## Hardware

Board:
ESP32-S3 Ozbot DRVKit Clone

CPU:
Dual Core 240 MHz

Flash:
8 MB

PSRAM:
2 MB

USB:
Native USB

RGB LED:
GPIO 48

Board Revision:
ESP32-S3 v0.2

---

## Software

Framework:
Arduino

Build System:
PlatformIO

Development Environment:
VS Code

---

## Installed Libraries

- WiFi
- WebServer
- WebSockets
- Adafruit NeoPixel

---

## Logging

```cpp
void logMessage(String m) {
    Serial.println(m);
    webSocket.broadcastTXT("LOG:" + m);
}
```
``