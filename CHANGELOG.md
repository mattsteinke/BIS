# BIS Changelog

All notable changes to the Behavioral Instrument System (BIS) will be documented in this file.

The format is inspired by Keep a Changelog and uses semantic versioning where practical.

---

# [Unreleased]

## UI Milestone

### Changed
- Redesigned browser interface into panel-based layout
- Combined Banks and Transport into a unified performance section
- Converted Parameters into a responsive two-column parameter matrix
- Added placeholder distributed parameters:
  - CCA
  - CCB
  - CCC
  - CCD
  - CCE
  - CCF
  - CCG
  - CCH
- Improved browser responsiveness and scaling behavior
- Enlarged bank pads for performance use
- Enlarged sequencer cells
- Enlarged output status indicators
- Added MIDI status indicator to Meter section

### Fixed
- Restored SCRUB/STEPS sequencer range highlighting after removal of legacy range display
- Decoupled sequencer highlighting from obsolete rangebar UI elements

### Preserved
- WebSocket protocol
  - CFG:
  - RNG:
  - G:
  - P:
  - BANKS:
  - OUT:
  - LOG:
  - ANIM:
- Bank behavior
- Sequencer behavior
- Playback behavior
- Browser synchronization behavior

### Notes
This milestone focuses on interface architecture and usability.

No firmware behavior changes were intended.

The interface now functions more as a musical instrument control surface and less as a firmware configuration page.

## Planned

### V15
- Preferences panel
- Persistent user settings
- Original BIS Composer-inspired configuration workflow
- Additional UI refinement

### Future
- TFT Animation Module
- Web MIDI
- Extended performance and composition tools

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
  - `CFG:`
  - `RNG:`
  - `G:`
  - `P:`
  - `BANKS:`
  - `OUT:`
  - `LOG:`
  - `ANIM:`
- Sequencer behavior
- Bank behavior
- Playback behavior
- Transport behavior
- Persistence behavior

## Notes
This release introduces no intended user-visible functional changes.

V14 is an architectural cleanup release focused on decoupling the browser interface from firmware while preserving all existing behavior.

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

## v15
Preferences and configuration

- Preferences panel
- Persistent settings
- UI workflow improvements
- Composer-inspired configuration tools

## v16
Visualization

- TFT Animation Module
- Enhanced visual feedback
- Animation development tools

## v17
Performance Integration

- Web MIDI
- External control integration
- Expanded performance workflows

## Future
Runtime architecture evolution

- Voice Manager
- Routing Engine
- Parameter Engine
- Browser Composer
- Extended performance systems