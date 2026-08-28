# BIS Project Context

## Project

BIS (Behavioral Instrument System) is a platform for kinetic sculptures,
robotic musical instruments, interactive installations, and experimental
control systems.

Current Version:
V14

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
- LittleFS

---

## Architecture

ESP32 owns:

- Sequencer
- Timing
- Playback
- Banks
- Persistence
- WebSocket communication

Browser owns:

- Display
- Editing
- Monitoring
- User interaction

Communication:

WebSocket protocol

Messages:

- CFG:
- RNG:
- G:
- P:
- BANKS:
- OUT:
- LOG:
- ANIM:

---

## Web Application

UI is served from LittleFS.

Filesystem structure:

data/
    index.html
    style.css
    app.js

Firmware and UI are developed independently.

Firmware upload:

platformio run -t upload

Filesystem upload:

platformio run -t uploadfs

---

## Design Philosophy

Banks are behavioral snapshots, not pattern slots.

Each bank stores:

- Grid state
- BPM
- ONTIME
- DRUNK
- PROBABILITY
- STEPS
- SCRUB
- Recorded parameter performance

The goal is behavior composition rather than pattern playback.

---

## Logging

```cpp
void logMessage(String m) {
    Serial.println(m);
    webSocket.broadcastTXT("LOG:" + m);
}
```

---

### Current Status

Stable:
- Sequencer
- Banks
- Persistence
- Browser synchronization
- WebSocket communication
- LittleFS web hosting

V15 Phase 1 Complete:
- Parameter Curves architecture
- Voice Curves architecture
- MIDI Map architecture
- Pin Map architecture
- Global module
- Theme variable system

Current Focus:
- Configuration persistence
- Runtime settings integration
- Theme system expansion