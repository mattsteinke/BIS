#include "bis_state.h"
#include "config.h"

const uint8_t outputPins[TRACKS] = {1, 2, 8, 9, 10, 11, 12};

WebServer server(80);
WebSocketsServer webSocket(81);
Adafruit_NeoPixel pixels(1, RGB_PIN, NEO_GRB + NEO_KHZ800);

BISState bis;
BISBank banks[BIS_BANKS];
unsigned long lastStep = 0;

uint8_t selectedBank = 255;
uint8_t recordingBank = 255;
bool isRecording = false;
unsigned long recordStartTime = 0;
uint16_t lastRecordedParamMs = 0;

bool isBankPlaying = false;
unsigned long bankPlaybackStart = 0;

OutputPulse outputs[TRACKS];

bool rgbActive = false;
uint32_t rgbEnd = 0;

void getActiveRange(int& rangeStart, int& rangeEnd) {
  rangeStart = bis.scrub;
  rangeEnd = bis.scrub + bis.steps - 1;
  if (rangeEnd >= MAX_STEPS) rangeEnd = MAX_STEPS - 1;
}
