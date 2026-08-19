# BIS

Behavioral Instrument System (BIS)

BIS is a platform for creating autonomous kinetic sculptures, robotic musical instruments, interactive installations, interactive toys, and experimental performance systems.

The current implementation targets ESP32-S3 hardware and provides a browser-based sequencer and performance environment where behaviors can be composed, recorded, recalled, and performed without requiring a computer during exhibition.

---

# Current Platform

Hardware:

- ESP32-S3 Ozbot DRVKit Clone
- ESP32-S3 Revision v0.2
- 8 MB Flash
- 2 MB PSRAM
- Native USB
- RGB LED on GPIO 48

Software:

- PlatformIO
- Arduino Framework
- WiFi
- WebServer
- WebSockets
- Adafruit NeoPixel

---

# Current Features

## Sequencer

- 7-track sequencer
- Variable loop lengths
- Probability control
- Drunk/random walk step movement
- Adjustable BPM
- Adjustable pulse on-time

## Banks

- 16 performance banks
- Pattern storage
- Parameter recording
- Parameter playback
- Bank recall
- Looping playback

## Browser Interface

- Web-based control surface
- WebSocket communication
- Sequencer editing
- Parameter editing
- Bank management
- Live performance monitoring

## Runtime

- Autonomous operation
- Browser optional after configuration
- ESP32-hosted UI
- Real-time control

---

# Project Structure

```text
src/
    Firmware implementation

include/
    Headers and shared definitions

lib/
    Project libraries

docs/
    Documentation

platformio.ini
    PlatformIO build configuration
```

---

# Build

Compile:

```bash
platformio run
```

Upload:

```bash
platformio run -t upload
```

Upload filesystem image (LittleFS web app files in [data/](/Users/matthewsteinke/Documents/PlatformIO/Projects/BIS/data)):

```bash
platformio run -t uploadfs
```

Monitor:

```bash
platformio device monitor
```

---

# Design Principles

- Behaviors before hardware
- Non-blocking firmware
- millis()-based timing
- Browser-first interaction
- Autonomous performance
- Reusable compositions
- Hardware-independent artistic structures

---

# Development Status

Current Stable Version:

```text
v14
```

---

# License

Private development repository.