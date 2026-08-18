# BIS Changelog

All notable changes to the Behavioral Instrument System (BIS) will be documented in this file.

The format is inspired by Keep a Changelog and uses semantic versioning where practical.

---

# [Unreleased]

## Planned

### Persistence
- LittleFS storage for banks
- Automatic bank restore on boot
- Persistent settings framework

### UI
- Loop-start bank flash indicator
- Additional browser interface cleanup
- Improved performer feedback

### Sequencer
- BPM range expanded to 5–400 BPM
- Minimum pulse on-time reduced to 5 ms

---

# [v14.0] - Planned

## Added
- LittleFS persistent bank storage
- Automatic bank restoration at startup

## Goals
- Preserve all bank data between power cycles
- Preserve recorded parameter performances
- Establish foundation for future settings persistence

---

# [v13.1]

## Fixed
- Bank parameter playback now loops continuously with recalled banks
- Recorded parameter animations no longer freeze after a single pass

## Improved
- Browser interface cleanup
- Web UI readability and maintainability

---

# [v13.0]

## Added
- ESP32-S3 PlatformIO build environment
- Web-based control interface
- WebSocket communications
- 7-track sequencer
- 16 performance banks
- Parameter recording
- Parameter playback
- Bank recall and autoplay
- Probability control
- Drunk-walk sequencing
- RGB status feedback

## Hardware
- ESP32-S3 Ozbot DRVKit Clone
- RGB LED on GPIO 48

## Platform
- PlatformIO
- Arduino Framework

---

# Version Roadmap

## v14
Persistence and reliability

- LittleFS bank storage
- Settings storage foundation
- Improved loop feedback
- Expanded performance ranges

## v15
Composition infrastructure

- Behavior framework
- Gesture management
- Scene system
- Score system

## Future
Runtime architecture evolution

- Voice Manager
- Routing Engine
- Parameter Engine
- Browser Composer
- Extended performance systems