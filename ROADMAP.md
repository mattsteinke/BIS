# BIS Roadmap

This document tracks planned development for the Behavioral Instrument System (BIS).

The goal is to prioritize practical improvements that make BIS more reliable,
usable, and maintainable while evolving toward a modular behavioral instrument architecture.

---

# Current Stable Version

## V14

Completed:

- ESP32-S3 PlatformIO firmware
- WebSocket control system
- Browser-hosted UI
- 7-track sequencer
- 16 performance banks
- Parameter recording
- Parameter playback
- Persistent bank storage
- Browser state synchronization
- LittleFS web hosting
- Separate:
  - index.html
  - style.css
  - app.js

---

# Current Development

## V15 Phase 1 ✅ Complete

### Configuration Architecture

Implemented:

- Parameter Curves architecture
- Voice Curves architecture
- MIDI Map architecture
- Pin Map architecture
- Global module architecture
- Theme variable system
- Responsive panel-based UI
- Configuration control naming system

### Current Interface

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

Status:

Architecture complete.
Runtime integration pending.

---

## V15 Phase 2

### Settings Persistence

Priority: High

Goal:

Connect existing configuration architecture to runtime storage.

Features:

- LittleFS settings persistence
- Curve settings persistence
- MIDI map persistence
- Pin map persistence
- System settings persistence

Success Criteria:

- Settings survive reboot
- Settings restore automatically
- Existing workflow preserved

---

## V15 Phase 3

### Runtime Integration

Priority: High

Goal:

Connect UI configuration to actual runtime behavior.

Features:

- Parameter curve evaluation
- Voice curve evaluation
- MIDI mapping runtime behavior
- Pin assignment runtime behavior

Success Criteria:

- Curve values affect behavior
- MIDI mappings function
- Pin assignments function
- Existing performance system remains stable

---

## V15 Phase 4

### Theme and Appearance

Priority: Medium

Goal:

Allow UI customization without affecting instrument behavior.

Features:

- Theme Hue control
- Theme Presets

Presets:

- Blue
- Green
- Purple
- Amber
- Monochrome

Future:

- User theme presets
- Theme import/export

Success Criteria:

- Preserve color relationships
- Runtime theme switching
- No firmware dependency

---

# Future Releases

## Browser Composer

Planned

Potential Features:

- JSON configuration import/export
- Preset management
- Multi-view layouts
- Touch-first layouts
- Accessibility improvements
- Multi-device support

---

## Behavior System

Planned

Potential Features:

- Behaviors
- Gestures
- Behavior routing
- Behavior recording
- Behavior transformation

---

## Scene System

Planned

Potential Features:

- Scene management
- Scene transitions
- Scene recall
- Scene layering

---

## Score System

Planned

Potential Features:

- Multi-scene performances
- Performance timelines
- Automated transitions
- Behavioral scores

---

## Voice Architecture

Planned

Potential Features:

- Voice abstraction
- Voice-specific curves
- Capability mapping
- Voice calibration
- Voice grouping
- Voice templates

---

## Visualization

Planned

Potential Features:

- TFT Animation Module
- Enhanced visual feedback
- Visualization editor
- Animation development tools

---

## Performance Integration

Planned

Potential Features:

- Web MIDI
- External controller integration
- Expanded performance workflows

---

# Long-Term Architecture

Future runtime evolution:

- Voice Manager
- Routing Engine
- Parameter Engine
- Browser Composer
- Extended performance systems

---

# Design Principles

When developing BIS:

- Preserve existing functionality.
- Prefer small, testable changes.
- Use non-blocking code.
- Use millis()-based timing.
- Maintain PlatformIO compatibility.
- Prioritize artist workflow over architectural purity.
- Favor reliability over cleverness.
- Keep configuration separate from performance.
- Keep modules self-contained.

---

# Development Workflow

1. Define feature.
2. Create implementation plan.
3. Implement minimally.
4. Test locally.
5. Test on ESP32 hardware.
6. Commit.
7. Push to GitHub.
8. Update CHANGELOG.md.
9. Update ROADMAP.md when milestones change.