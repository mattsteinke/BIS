BIS V15 PHASE 2 - SETTINGS PERSISTENCE IMPLEMENTATION SPECIFICATION

Context

BIS runs on:

- ESP32-S3
- PlatformIO
- Arduino Framework
- LittleFS
- WebSockets

The settings architecture foundation already exists and compiles successfully.

Current files:

include/
    bis_settings.h

src/
    bis_settings.cpp

Current structures:

struct Curve
struct ParameterCurves
struct BISSettings

Global object:

extern BISSettings bisSettings;

=====================================================
IMPORTANT PERFORMANCE DISCOVERY
=====================================================

Bank switching originally caused audible musical stuttering.

Investigation determined:

NOT:
- LittleFS
- Bank recall
- RAM copies

WAS:
- excessive websocket traffic

Specifically:

broadcastFullState()

during bank recall.

broadcastFullState() transmits:

CFG:
RNG:
P:
BANKS:

plus approximately:

175 grid updates

Removing broadcastFullState() from the bank recall path eliminated the musical pause.

ARCHITECTURAL RULE

REAL-TIME MUSICAL TIMING ALWAYS HAS PRIORITY OVER UI SYNCHRONIZATION.

Future settings work must not introduce timing stalls.

It is acceptable for UI updates to be delayed.

It is NOT acceptable for musical timing to be delayed.

Settings synchronization must never interfere with:

- bank recall
- playback
- trigger generation
- scheduler timing

=====================================================
OWNERSHIP RULES
=====================================================

Bank persistence belongs to:

bis_banks.*

Settings persistence belongs to:

bis_settings.*

Do not place settings persistence logic inside:

- bis_banks.cpp
- bis_web.cpp
- main.cpp

except for calling public APIs.

=====================================================
SETTINGS FILE
=====================================================

Use a single settings file:

/settings.bin

Do not create:

parameterCurves.bin
outputCurves.bin
midiMap.bin
pinMap.bin

The system should use one persistent settings object.

=====================================================
SETTINGS VERSIONING
=====================================================

Add explicit versioning now.

Example:

constexpr uint16_t SETTINGS_VERSION = 1;

BISSettings should contain:

uint16_t version;

Example:

struct BISSettings {

    uint16_t version;

    ParameterCurves parameterCurves;

    // Future:
    //
    // OutputCurves outputCurves;
    // MidiMap midiMap;
    // IRMap irMap;
    // PinMap pinMap;
    // SystemSettings system;
};

Loading behavior:

If:

settings.version != SETTINGS_VERSION

Then:

loadDefaultSettings()

and report:

SETTINGS VERSION MISMATCH

This will prevent future compatibility problems.

=====================================================
CURRENT DATA MODEL
=====================================================

struct Curve {

    uint16_t init;
    uint16_t mid;
    uint16_t max;
};

struct ParameterCurves {

    Curve bpm;
    Curve ontime;

    Curve drunk;
    Curve prob;

    Curve steps;
    Curve scrub;

    Curve cca;
    Curve ccb;
    Curve ccc;
    Curve ccd;
    Curve cce;
    Curve ccf;
    Curve ccg;
    Curve cch;
};

struct BISSettings {

    uint16_t version;

    ParameterCurves parameterCurves;

    // future expansion
};

extern BISSettings bisSettings;

=====================================================
PUBLIC API
=====================================================

bis_settings.h should expose:

void loadDefaultSettings();

bool loadSettings();

bool saveSettings();

bool settingsFileExists();

=====================================================
STARTUP SEQUENCE
=====================================================

Official initialization order:

setup()

↓

initBankStorage()

↓

loadBanksFromStorage()

↓

loadSettings()

↓

start web server

↓

start websocket

Settings should always load before any browser can connect.

=====================================================
PHASE 2A
SETTINGS FOUNDATION
=====================================================

Task 1

Implement loadDefaultSettings().

Move all parameter curve defaults from HTML into firmware.

Firmware becomes the source of truth.

HTML values become placeholders only.

The browser must never be considered the source of truth.

Current values exist in HTML:

bpmCurveInit
bpmCurveMid
bpmCurveMax

ontimeCurveInit
ontimeCurveMid
ontimeCurveMax

...

cchCurveInit
cchCurveMid
cchCurveMax

Populate every parameter curve in:

loadDefaultSettings()

=====================================================
Task 2
=====================================================

Implement:

settingsFileExists()

Use:

/settings.bin

=====================================================
Task 3
=====================================================

Implement:

loadSettings()

Loading behavior:

IF:

settings.bin exists

AND

version matches

THEN:

load BISSettings

ELSE:

loadDefaultSettings()

Expected logs:

SETTINGS FILE FOUND
SETTINGS FILE LOADED

or

SETTINGS VERSION MISMATCH
SETTINGS DEFAULTS LOADED

or

SETTINGS FILE NOT FOUND
SETTINGS DEFAULTS LOADED

=====================================================
Task 4
=====================================================

Implement:

saveSettings()

Use LittleFS.

Store entire:

BISSettings

as binary.

Follow the same persistence style already used by bank persistence.

No JSON.

=====================================================
LOGGING
=====================================================

Use the existing logMessage() pattern.

Expected log messages:

SETTINGS FILE FOUND

SETTINGS FILE LOADED

SETTINGS FILE CREATED

SETTINGS FILE SAVED

SETTINGS FILE NOT FOUND

SETTINGS DEFAULTS LOADED

SETTINGS VERSION MISMATCH

=====================================================
PHASE 2B
READ-ONLY UI POPULATION
=====================================================

Goal

Display firmware-owned settings in browser.

No editing.

Controls remain disabled.

=====================================================
Task 5
=====================================================

Add websocket message:

CURVES:

This message is responsible for transmitting all parameter curve values.

Do not use JSON.

Use BIS message style.

=====================================================
CURVES MESSAGE FORMAT
=====================================================

Use an explicit named format.

Example:

CURVES:
BPM:120:240:480
ONTIME:10:100:1000
DRUNK:0:50:100
PROB:0:50:100
STEPS:1:12:25
SCRUB:0:12:24
CCA:9:100:200
...
CCH:9:100:200

The protocol must be human-readable and debuggable.

Avoid anonymous positional payloads.

=====================================================
Task 6
=====================================================

Browser receives:

CURVES:

Populate:

bpmCurveInit
bpmCurveMid
bpmCurveMax

ontimeCurveInit
ontimeCurveMid
ontimeCurveMax

...

cchCurveInit
cchCurveMid
cchCurveMax

Result:

Firmware values appear in browser.

Browser remains read-only.

=====================================================
CURVES TRANSMISSION RULE
=====================================================

CURVES:

should only be sent:

- on client connect
- after loadSettings()

Do not continuously broadcast CURVES.

Do not send CURVES during playback.

=====================================================
PHASE 2C
EDITING AND SAVING
=====================================================

Goal

Enable editing.

=====================================================
Task 7
=====================================================

Remove disabled attribute from:

Parameter Curves only.

Do not enable:

- Output Curves
- MIDI Map
- IR Map
- Pin Map

=====================================================
Task 8
=====================================================

Add:

SAVE CURVES

button.

=====================================================
SAVE STRATEGY
=====================================================

Do NOT autosave.

Do NOT save after every field edit.

Settings are saved only when:

SAVE CURVES

is pressed.

Reason:

Avoid unnecessary flash writes.

=====================================================
Task 9
=====================================================

Create browser → firmware update message.

Possible:

SETCURVES:

or similar.

Update:

bisSettings.parameterCurves

in RAM.

=====================================================
Task 10
=====================================================

Call:

saveSettings()

after successful validation and SAVE CURVES action.

Persist to:

/settings.bin

=====================================================
FUTURE EXPANSION
=====================================================

Curve is a core BIS primitive.

Future systems should reuse:

struct Curve {
    init
    mid
    max
};

Planned future settings:

OutputCurves

MidiMap

IRMap

PinMap

SystemSettings

All future settings should become members of:

BISSettings

All future settings should persist through:

/settings.bin

using the same architecture.

=====================================================
PERFORMANCE REQUIREMENTS
=====================================================

Do not reintroduce:

broadcastFullState()

during bank recall.

Do not send large websocket floods during:

- bank recall
- playback
- scheduler execution

Future settings synchronization must use lightweight messages.

Console logging may be batched or throttled in the future.

Musical timing always wins over UI synchronization.

Implement incrementally.

Compile and test on real ESP32 hardware after each milestone before proceeding to the next phase.