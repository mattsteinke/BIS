#pragma once

#include <Arduino.h>

/*
    BIS Curve Primitive

    Three-point response curve used throughout BIS.

    INIT = start of range
    MID  = midpoint response
    MAX  = end of range
*/

struct Curve {
    uint16_t init;
    uint16_t mid;
    uint16_t max;
};

/*
    Parameter Response Curves

    Defines how UI values map into actual parameter values.
*/

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

/*
    Master BIS Settings

    Output curves, MIDI maps, pin maps, etc.
    can be added here later without changing
    the persistence architecture.
*/

struct BISSettings {

    ParameterCurves parameterCurves;

    // Future:
    //
    // OutputCurves outputCurves;
    // MidiMap midiMap;
    // PinMap pinMap;
    // SystemSettings system;
};

/*
    Global Settings Object
*/

extern BISSettings bisSettings;