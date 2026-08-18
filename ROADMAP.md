# BIS Roadmap

This document tracks planned development for the Behavioral Instrument System (BIS).

The goal is to prioritize practical improvements that make BIS more reliable, usable, and maintainable while gradually evolving toward the long-term BIS architecture.

---

# Current Stable Version

## v13

Implemented:

- ESP32-S3 PlatformIO firmware
- Browser-hosted UI
- WebSocket control
- 7-track sequencer
- 16 banks
- Parameter recording
- Parameter playback
- Looping bank playback
- Probability control
- Drunk-walk sequencing
- RGB status feedback

---

# Next Release

# v14.0

## Persistent Memory

Priority: High

Goal:

Banks survive power cycles.

Features:

- LittleFS integration
- Save all 16 banks
- Save grid state
- Save parameter history
- Save bank duration
- Restore banks during startup

Success Criteria:

- Power cycle does not erase stored banks.
- Existing workflow remains unchanged.
- Flash wear minimized.

---

# v14.1

## Loop Feedback

Priority: Medium

Goal:

Provide performer feedback when the sequencer returns to the beginning of its loop.

Features:

- Active bank flashes green at loop start.
- Returns to yellow after flash.

Success Criteria:

- Clear visual loop timing feedback.
- No impact on sequencing behavior.

---

## Expanded BPM Range

Priority: Medium

Goal:

Support slower and faster performances.

New Limits:

- Minimum BPM: 5
- Maximum BPM: 400

Success Criteria:

- UI updated.
- Firmware validation updated.
- Timing remains stable.

---

## Expanded On-Time Range

Priority: Medium

Goal:

Support shorter trigger pulses.

New Limits:

- Minimum on-time: 5 ms

Success Criteria:

- UI updated.
- Firmware validation updated.
- Existing behavior preserved.

---

# v14.2

## Settings Persistence

Priority: High

Goal:

System settings survive power cycles.

Store:

- BPM
- OnTime
- Probability
- Drunk
- Steps
- Scrub
- Last selected bank

Success Criteria:

- Settings restored automatically at boot.
- Independent of bank storage.

---

# Future Releases

## Browser Composer Foundation

Planned

Potential Features:

- Modular UI architecture
- Separate HTML / CSS / JavaScript files
- Improved mobile usability
- Configuration pages
- Diagnostics pages

---

## Behavior System

Planned

Potential Features:

- Behaviors
- Gestures
- Behavior routing
- Behavior recording

---

## Scene System

Planned

Potential Features:

- Scene management
- Scene transitions
- Scene recall

---

## Score System

Planned

Potential Features:

- Multi-scene performances
- Performance timelines
- Automated transitions

---

## Voice Architecture

Planned

Potential Features:

- Voice abstraction
- Capability mapping
- Calibration system

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

---

# Development Workflow

1. Define feature.
2. Create implementation plan.
3. Implement minimally.
4. Compile.
5. Test on ESP32 hardware.
6. Commit.
7. Push to GitHub.
8. Update CHANGELOG.md.