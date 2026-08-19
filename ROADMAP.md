# BIS Roadmap

This document tracks planned development for the Behavioral Instrument System (BIS).

The goal is to prioritize practical improvements that make BIS more reliable,
usable, and maintainable while gradually evolving toward the long-term BIS architecture.

---

# Current Stable Version

## V14

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
- Persistent bank storage
- Browser state synchronization
- LittleFS web hosting
- Separated HTML / CSS / JavaScript architecture

---

# Next Release

## V15

### Preferences System

Priority: High

Goal:

Provide a persistent configuration system inspired by the original BIS Composer workflow.

Features:

- Preferences panel
- Persistent user settings
- Startup configuration
- User-adjustable defaults
- Settings management UI

Success Criteria:

- Settings survive reboot
- Settings remain independent from banks
- Existing workflow remains unchanged

---

### Performance Feedback

Priority: Medium

Goal:

Improve performer awareness of timing and system state.

Features:

- Loop-start visual indicator
- Active bank feedback improvements
- Enhanced visual status monitoring

Success Criteria:

- Clear loop timing feedback
- No impact on sequencing behavior

---

### Expanded Performance Range

Priority: Medium

Goal:

Support a wider range of installation and performance behaviors.

Features:

- BPM range: 5–400
- Minimum pulse on-time: 5 ms

Success Criteria:

- Firmware validation updated
- Browser UI updated
- Existing behavior preserved

---

# Future Releases

## Browser Composer

Planned

Potential Features:

- Preferences pages
- Diagnostics pages
- Preset management
- Mobile optimization
- Alternate performance views
- Enhanced editing workflows

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
