# BIS

Behavioral Instrument System (BIS)

BIS is a platform for autonomous kinetic sculptures, robotic musical instruments,
interactive installations, experimental control systems, and behavioral composition.

The current implementation targets ESP32-S3 hardware and provides a browser-based
performance and configuration environment where behaviors can be composed, recorded,
recalled, modified, and performed without requiring a computer during exhibition.

---

# Current Platform

## Hardware

- ESP32-S3 Ozbot DRVKit Clone
- ESP32-S3 Revision v0.2
- 8 MB Flash
- 2 MB PSRAM
- Native USB
- RGB LED on GPIO 48

## Software

- PlatformIO
- Arduino Framework
- WiFi
- WebServer
- WebSockets
- Adafruit NeoPixel
- LittleFS

---

# Current Features

## Sequencer

- 7-track sequencer
- Variable loop lengths
- Probability control
- Drunk/random walk sequencing
- Adjustable BPM
- Adjustable pulse on-time
- Real-time range visualization

## Banks & Transport

- 16 performance banks
- Bank recording
- Bank recall
- Looping playback
- Performance transport controls
- Overwrite workflow

## Parameters

### Runtime Parameters

- BPM
- ONTIME
- DRUNK
- PROB
- STEPS
- SCRUB

### Distributed Parameters

- CCA
- CCB
- CCC
- CCD
- CCE
- CCF
- CCG
- CCH

## Browser Interface

- Web-based control surface
- WebSocket communication
- Responsive layout
- Mobile-compatible layout
- Live performance monitoring
- Global diagnostics

---

# Configuration Architecture (V15)

## Parameters

### Parameter Curves

Each parameter provides:

- INIT
- MID
- MAX

curve configuration points.

### Voice Curves

Each output voice provides:

- INIT
- MID
- MAX

curve configuration points.

## Global

### Visible

- Outputs
- MIDI Activity
- Console

### Configuration

- MIDI Map
- Pin Map

### Future

- System Settings
- Theme Control
- JSON Import / Export

---

# UI Architecture

BANKS & TRANSPORT

PARAMETERS
    ▼ PARAMETER CURVES
    ▼ VOICE CURVES

SEQUENCER

GLOBAL
    OUTPUTS
    MIDI
    CONSOLE

    ▼ MIDI MAP
    ▼ PIN MAP

---

# Project Structure

src/
    ESP32 firmware

include/
    Shared headers

data/
    index.html
    style.css
    app.js

lib/
    Libraries

docs/
    Documentation

platformio.ini
    Platform configuration

---

# Build

Firmware:

```bash
platformio run
platformio run -t upload
```

Web UI (LittleFS):

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
- Modular configuration architecture

---

# Development Status

Current Stable Version: V14

Current Development Version: V15 Phase 1

Completed

- LittleFS web architecture
- Responsive interface
- Global module
- Parameter Curves architecture
- Voice Curves architecture
- MIDI Map architecture
- Pin Map architecture
- Theme variable system

Next

- Settings persistence
- Curve integration
- MIDI map integration
- Pin map integration
- Theme hue control
- JSON import/export

---

# License

Private development repository.