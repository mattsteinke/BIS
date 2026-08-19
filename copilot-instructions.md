# BIS Copilot Instructions

You are assisting with the BIS (Behavioral Instrument System) project.

---

## Platform

- ESP32-S3 Ozbot DRVKit Clone
- ESP32-S3 Revision v0.2
- 8 MB Flash
- 2 MB PSRAM
- Native USB
- RGB LED GPIO48

---

## Development Environment

- PlatformIO
- Arduino Framework
- VS Code
- GitHub Copilot

---

## Current Architecture

### Firmware Responsibilities

The ESP32 owns:

- Sequencer
- Timing
- Playback
- Bank management
- Persistence
- WebSocket communication
- System state

### Browser Responsibilities

The browser owns:

- Display
- Editing
- Monitoring
- User interaction

### Web Application Structure

UI is served from LittleFS.

```
data/
├── index.html
├── style.css
└── app.js
```

Firmware and browser code are developed independently.

---

## Current Stable Features

### Sequencer

- 7-track sequencer
- BPM control
- ONTIME control
- Probability control
- DRUNK control
- STEPS control
- SCRUB control
- Playhead visualization
- Range visualization

### Banks

- 16 performance banks
- Bank recording
- Bank recall
- Parameter recording
- Parameter playback
- Parameter looping
- Persistent storage
- Browser synchronization

### Browser

- Web-based control surface
- WebSocket communication
- State recovery after refresh
- Output indicators
- Performance monitoring

### Persistence

- LittleFS storage
- Bank persistence across reboots
- Automatic bank restoration

---

## WebSocket Protocol

The protocol below is considered stable.

Do not change unless explicitly requested.

```
CFG:
RNG:
G:
P:
BANKS:
OUT:
LOG:
ANIM:
```

Preserve compatibility whenever possible.

---

## Design Philosophy

Banks are behavioral snapshots, not pattern slots.

A bank represents a complete behavioral state including:

- Grid state
- BPM
- ONTIME
- PROBABILITY
- DRUNK
- STEPS
- SCRUB
- Recorded parameter performance

Favor behavior composition over pattern storage.

---

## Coding Rules

- Use non-blocking code
- Prefer millis() timing
- Avoid delay() unless explicitly required
- Preserve existing behavior unless asked to redesign
- PlatformIO-compatible code only
- Use ESP32-safe patterns
- Minimize RAM usage
- Minimize flash writes
- Favor maintainability over cleverness

---

## When Reviewing Code

Look for:

- Timing issues
- Watchdog risks
- Memory risks
- Flash wear concerns
- WiFi reliability issues
- WebSocket reliability issues
- Maintainability concerns
- Browser/firmware separation concerns

---

## When Implementing Features

Prefer:

- Small changes
- Surgical fixes
- Backward-compatible behavior
- Clear test procedures
- Architecture consistency

Always preserve:

- Sequencer behavior
- Bank behavior
- Persistence behavior
- WebSocket protocol compatibility

Unless explicitly instructed otherwise.

---

## Build and Upload

Firmware:

```bash
platformio run
platformio run -t upload
```

Filesystem (LittleFS Web UI):

```bash
platformio run -t uploadfs
```

Rules:

- Changes in `src/` or `include/` require firmware upload.
- Changes in `data/index.html`, `data/style.css`, or `data/app.js` require filesystem upload.

---

## Current Priorities

### V15

- Preferences panel
- Persistent user settings
- Configuration workflow improvements
- Browser usability improvements

### Future

- TFT Animation Module
- Web MIDI
- Browser Composer
- Behavior System
- Scene System
- Voice Architecture