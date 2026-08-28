# BIS Changelog

All notable changes to the Behavioral Instrument System (BIS) are documented in this file.

The format is inspired by Keep a Changelog and uses semantic versioning where practical.

---

# [Unreleased]

## Planned

### V15 Phase 2

#### Persistence
- LittleFS settings persistence
- Curve settings persistence
- MIDI map persistence
- Pin map persistence
- System settings persistence

#### Configuration
- Runtime curve editing
- Runtime MIDI mapping
- Runtime pin assignment
- JSON export/import

#### Appearance
- Theme hue control
- Theme presets

  - Blue
  - Green
  - Purple
  - Amber
  - Monochrome

#### General
- Preferences panel
- Persistent user settings
- Additional UI refinement

---

# [v15.0] - Phase 1

## Added

### Parameter Configuration
- Parameter Curves architecture
- Voice Curves architecture

### Global Configuration
- MIDI Map architecture
- Pin Map architecture
- Global module architecture

### Theme System
- CSS variable-based theme system
- Semantic color hierarchy
- Color opacity hierarchy

### Future Integration
- Configuration control IDs for:
  - Parameter Curves
  - Voice Curves
  - MIDI Map
  - Pin Map

## Changed

### Interface Architecture

Reorganized interface into:

- Banks & Transport
- Parameters
  - Parameter Curves
  - Voice Curves
- Sequencer
- Global
  - Outputs
  - MIDI
  - Console
  - MIDI Map
  - Pin Map

### UI Layout

- Responsive panel-based layout
- Responsive parameter matrix
- Responsive bank layout
- Responsive sequencer layout
- Responsive meter layout

### Global Module

- Renamed Meter to Global
- Moved Console into Global
- Combined system status and configuration tools

## Improved

- Browser responsiveness
- Mobile usability
- Parameter organization
- Configuration discoverability
- Instrument-oriented workflow
- Theme consistency

## Notes

All configuration controls remain disabled placeholders.

No firmware behavior changes were introduced.

No WebSocket protocol changes were introduced.

This release establishes the complete configuration architecture for future integration.

---

# [v14.0]

## Changed

- Web UI moved out of embedded firmware source
- Removed monolithic `web_page.h`
- Browser application split into:
  - `data/index.html`
  - `data/style.css`
  - `data/app.js`
- Browser assets now served from LittleFS

## Improved

- Clear separation between firmware and browser application
- Smaller and more maintainable firmware codebase
- Faster browser UI iteration
- Independent firmware and UI deployment workflows

## Preserved

- Existing WebSocket protocol
  - CFG:
  - RNG:
  - G:
  - P:
  - BANKS:
  - OUT:
  - LOG:
  - ANIM:
- Sequencer behavior
- Bank behavior
- Playback behavior
- Transport behavior
- Persistence behavior

## Notes

This release introduces no intended user-visible functional changes.

V14 focused on architectural cleanup and browser/firmware separation.

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

## v16

### Visualization

- TFT Animation Module
- Enhanced visual feedback
- Animation development tools

## v17

### Performance Integration

- Web MIDI
- External control integration
- Expanded performance workflows

## Future

### Runtime Architecture Evolution

- Voice Manager
- Routing Engine
- Parameter Engine
- Browser Composer
- Extended performance systems