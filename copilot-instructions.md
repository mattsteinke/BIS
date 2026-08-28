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
- Configuration
- Theme management

### Web Application Structure

UI is served from LittleFS.

```text
data/
├── index.html
├── style.css
└── app.js
```

Firmware and browser code are developed independently.

---

## Interface Architecture

```text
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
```

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
- Responsive layout
- Mobile support
- WebSocket communication
- State recovery after refresh
- Output indicators
- Performance monitoring

### Persistence

- LittleFS storage
- Bank persistence across reboots
- Automatic bank restoration

---

## Configuration Architecture

### Parameter Curves

Every parameter supports:

- INIT
- MID
- MAX

curve definitions.

Parameters:

- BPM
- ONTIME
- DRUNK
- PROB
- STEPS
- SCRUB
- CCA
- CCB
- CCC
- CCD
- CCE
- CCF
- CCG
- CCH

### Voice Curves

Each voice/output supports:

- INIT
- MID
- MAX

curve definitions.

Voices:

- V1
- V2
- V3
- V4
- V5
- V6
- V7

### Global

Global owns shared resources:

- Outputs
- MIDI Activity
- Console
- MIDI Map
- Pin Map

### Current Status

Configuration controls currently function as UI architecture placeholders.

Settings remain intentionally disabled until persistence and runtime integration are implemented.

---

## WebSocket Protocol

The protocol below is considered stable.

Do not change unless explicitly requested.

```text
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

## Configuration Philosophy

Module settings should remain with the module they affect.

Examples:

PARAMETERS

- Parameter Curves
- Voice Curves

GLOBAL

- MIDI Map
- Pin Map
- Shared Resources

Shared resources belong in GLOBAL.

Performance controls belong in their respective modules.

---

## Theme System

Colors are managed via CSS custom properties.

Semantic hierarchy:

### Accent

- Module headers
- Settings headers
- Navigation

### Data

- Runtime values
- Editable values

### Success

- Output activity
- MIDI activity

### Warning

- Selection
- Playhead

### Danger

- Recording
- Errors

### Overwrite

- Overwrite mode

Future:

- Theme Hue control
- Theme Presets
- Appearance management

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

### V15 Phase 2

Configuration Integration

- LittleFS settings persistence
- Curve settings persistence
- MIDI map persistence
- Pin map persistence

Runtime Integration

- Parameter curve evaluation
- Voice curve evaluation
- MIDI mapping behavior
- Pin assignment behavior

Theme System

- Theme Hue control
- Theme presets

Browser Composer

- JSON import/export
- Preset management

### Future

- TFT Animation Module
- Web MIDI
- Browser Composer
- Behavior System
- Scene System
- Voice Architecture