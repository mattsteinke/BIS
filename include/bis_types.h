#pragma once

#include <Arduino.h>
#include "config.h"

struct ParamFrame {
  uint16_t timestamp;
  uint16_t bpm;
  uint16_t ontimeMs;
  uint8_t drunk;
  uint8_t probability;
  uint8_t steps;
  uint8_t scrub;
};

struct BISBank {
  bool grid[TRACKS][MAX_STEPS];
  uint16_t startBpm, startOntimeMs;
  uint8_t startDrunk, startProbability, startSteps, startScrub;
  ParamFrame paramHistory[MAX_PARAM_FRAMES];
  uint16_t paramFrameCount;
  uint16_t bankDuration;
  bool hasData;
};

struct BISState {
  bool playing = false;
  int currentStep = 0;
  uint16_t bpm = 120, intervalMs = 125, ontimeMs = 50;
  uint8_t drunk = 0, probability = 100;
  uint8_t steps = 25;
  uint8_t scrub = 0;
  bool grid[TRACKS][MAX_STEPS];
};

struct OutputPulse {
  bool active = false;
  uint32_t endTime = 0;
  uint32_t ontimeDuration = 0;
};
