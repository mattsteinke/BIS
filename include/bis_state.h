#pragma once

#include <Adafruit_NeoPixel.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include "bis_types.h"

extern WebServer server;
extern WebSocketsServer webSocket;
extern Adafruit_NeoPixel pixels;

extern BISState bis;
extern BISBank banks[BIS_BANKS];
extern unsigned long lastStep;

extern uint8_t selectedBank;
extern uint8_t recordingBank;
extern bool isRecording;
extern unsigned long recordStartTime;
extern uint16_t lastRecordedParamMs;

extern bool isBankPlaying;
extern unsigned long bankPlaybackStart;

extern OutputPulse outputs[TRACKS];

extern bool rgbActive;
extern uint32_t rgbEnd;

void getActiveRange(int& rangeStart, int& rangeEnd);
