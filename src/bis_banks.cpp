#include "bis_banks.h"

#include <LittleFS.h>

#include "bis_state.h"
#include "bis_web.h"

namespace {
bool littleFsReady = false;

String bankPath(uint8_t bankId) {
  return "/bank" + String(bankId) + ".bin";
}

void logFileOpenResult(bool ok, const String& path) {
  logMessage(String(ok ? "FILE OPEN SUCCESS " : "FILE OPEN FAILED ") + path);
}

void logWriteResult(bool ok, const String& path) {
  logMessage(String(ok ? "WRITE SUCCESS " : "WRITE FAILED ") + path);
}

void logReadResult(bool ok, const String& path) {
  logMessage(String(ok ? "READ SUCCESS " : "READ FAILED ") + path);
}
}  // namespace

void recordParamFrame() {
  if (!isRecording || recordingBank >= BIS_BANKS) return;

  unsigned long now = millis();
  uint16_t elapsedMs = (now - recordStartTime) & 0xFFFF;

  if (elapsedMs == lastRecordedParamMs) return;
  lastRecordedParamMs = elapsedMs;

  BISBank& bank = banks[recordingBank];
  if (bank.paramFrameCount >= MAX_PARAM_FRAMES) return;

  ParamFrame& frame = bank.paramHistory[bank.paramFrameCount];
  frame.timestamp = elapsedMs;
  frame.bpm = bis.bpm;
  frame.ontimeMs = bis.ontimeMs;
  frame.drunk = bis.drunk;
  frame.probability = bis.probability;
  frame.steps = bis.steps;
  frame.scrub = bis.scrub;

  bank.paramFrameCount++;
}

void captureBank(uint8_t bankId) {
  if (bankId >= BIS_BANKS) return;

  BISBank& bank = banks[bankId];

  for (int t = 0; t < TRACKS; t++)
    for (int s = 0; s < MAX_STEPS; s++)
      bank.grid[t][s] = bis.grid[t][s];

  bank.startBpm = bis.bpm;
  bank.startOntimeMs = bis.ontimeMs;
  bank.startDrunk = bis.drunk;
  bank.startProbability = bis.probability;
  bank.startSteps = bis.steps;
  bank.startScrub = bis.scrub;

  bank.bankDuration = (millis() - recordStartTime) & 0xFFFF;
  bank.hasData = true;

  if (littleFsReady) {
    const String path = bankPath(bankId);
    File file = LittleFS.open(path, FILE_WRITE, true);
    if (file) {
      logFileOpenResult(true, path);
      const size_t written = file.write((const uint8_t*)&bank, sizeof(BISBank));
      file.close();
      const bool writeOk = (written == sizeof(BISBank));
      logWriteResult(writeOk, path);
      if (writeOk) {
        logMessage("BANK" + String(bankId) + " SAVED");
      } else {
        logMessage("BANK" + String(bankId) + " SAVE FAILED");
      }
      const bool existsAfterWrite = LittleFS.exists(path);
      logMessage("EXISTS " + path + " " + String(existsAfterWrite ? "TRUE" : "FALSE"));
    } else {
      logFileOpenResult(false, path);
      logWriteResult(false, path);
      logMessage("EXISTS " + path + " " + String(LittleFS.exists(path) ? "TRUE" : "FALSE"));
      logMessage("BANK" + String(bankId) + " SAVE FAILED");
    }
  } else {
    logMessage("LITTLEFS FAILED");
  }

  logMessage("CAPTURE BANK " + String(bankId + 1) + " (" + String(bank.bankDuration) + "ms)");
}

int firstEmptyBank() {
  for (int i = 0; i < BIS_BANKS; i++)
    if (!banks[i].hasData) return i;
  return -1;
}

void stopRecording() {
  if (!isRecording) return;

  recordParamFrame();
  captureBank(recordingBank);
  logMessage("RECORD STOP - BANK " + String(recordingBank + 1) + " SAVED");

  if (overwriteMode) {
    logMessage("OVERWRITE COMPLETE");
    overwriteMode = false;
    overwriteTargetBank = 255;
  }

  isRecording = false;
  recordingBank = 255;
  isBankPlaying = false;
}

void getAnimatedParams(uint16_t playbackMs, uint16_t& outBpm, uint16_t& outOntime,
                       uint8_t& outDrunk, uint8_t& outProb, uint8_t& outSteps, uint8_t& outScrub) {
  BISBank& bank = banks[selectedBank];

  if (bank.paramFrameCount == 0) {
    outBpm = bank.startBpm;
    outOntime = bank.startOntimeMs;
    outDrunk = bank.startDrunk;
    outProb = bank.startProbability;
    outSteps = bank.startSteps;
    outScrub = bank.startScrub;
    return;
  }

  ParamFrame* frame1 = NULL;
  ParamFrame* frame2 = NULL;

  for (int i = 0; i < bank.paramFrameCount; i++) {
    if (bank.paramHistory[i].timestamp <= playbackMs) {
      frame1 = &bank.paramHistory[i];
    }
    if (bank.paramHistory[i].timestamp >= playbackMs && frame2 == NULL) {
      frame2 = &bank.paramHistory[i];
    }
  }

  if (frame1 == NULL) {
    outBpm = bank.startBpm;
    outOntime = bank.startOntimeMs;
    outDrunk = bank.startDrunk;
    outProb = bank.startProbability;
    outSteps = bank.startSteps;
    outScrub = bank.startScrub;
    return;
  }

  if (frame2 == NULL || frame1 == frame2) {
    outBpm = frame1->bpm;
    outOntime = frame1->ontimeMs;
    outDrunk = frame1->drunk;
    outProb = frame1->probability;
    outSteps = frame1->steps;
    outScrub = frame1->scrub;
    return;
  }

  float t = (float)(playbackMs - frame1->timestamp) / (float)(frame2->timestamp - frame1->timestamp);
  t = constrain(t, 0.0f, 1.0f);

  outBpm = frame1->bpm + (uint16_t)((frame2->bpm - frame1->bpm) * t);
  outOntime = frame1->ontimeMs + (uint16_t)((frame2->ontimeMs - frame1->ontimeMs) * t);
  outDrunk = frame1->drunk + (uint8_t)((frame2->drunk - frame1->drunk) * t);
  outProb = frame1->probability + (uint8_t)((frame2->probability - frame1->probability) * t);
  outSteps = frame1->steps + (uint8_t)((frame2->steps - frame1->steps) * t);
  outScrub = frame1->scrub + (uint8_t)((frame2->scrub - frame1->scrub) * t);
}

void recallBank(uint8_t bankId) {
  if (bankId >= BIS_BANKS || !banks[bankId].hasData) {
    logMessage("BANK" + String(bankId) + " NOT FOUND");
    return;
  }

  BISBank& bank = banks[bankId];

  for (int t = 0; t < TRACKS; t++)
    for (int s = 0; s < MAX_STEPS; s++)
      bis.grid[t][s] = bank.grid[t][s];

  bis.bpm = bank.startBpm;
  bis.ontimeMs = bank.startOntimeMs;
  bis.drunk = bank.startDrunk;
  bis.probability = bank.startProbability;
  bis.steps = bank.startSteps;
  bis.scrub = bank.startScrub;

  bis.intervalMs = 60000 / (bis.bpm * 4);
  bis.currentStep = bis.scrub;

  selectedBank = bankId;
  bis.playing = true;
  isBankPlaying = true;
  bankPlaybackStart = millis();
  lastStep = 0;

  logMessage("BANK" + String(bankId) + " LOADED");
  logMessage("RECALL BANK " + String(bankId + 1));
  logMessage("AUTO-PLAY BANK " + String(bankId + 1));
}

void syncBankStatus() {
  String bankData = "BANKS:";
  for (int i = 0; i < BIS_BANKS; i++) {
    bankData += String(banks[i].hasData ? 1 : 0);
  }
  bankData += ":" + String(selectedBank);
  bankData += ":" + String(isRecording ? 1 : 0);
  bankData += ":" + String(isRecording ? recordingBank : 255);
  bankData += ":" + String(isBankPlaying ? 1 : 0);
  bankData += ":" + String(overwriteMode ? 1 : 0);
  bankData += ":" + String(overwriteTargetBank);
  webSocket.broadcastTXT(bankData);
}

void sendAnimatedParams() {
  if (!isBankPlaying || selectedBank >= BIS_BANKS) return;

  BISBank& bank = banks[selectedBank];

  // Loop the recorded parameter animation over the bank's captured duration
  // (bankDuration) instead of letting raw elapsed time run past the end of
  // the recording, which previously left getAnimatedParams() stuck on the
  // final frame indefinitely. Using modulo here keeps the animation cycling
  // in step with the free-running sequencer for as long as the bank plays.
  unsigned long elapsedMs = millis() - bankPlaybackStart;  // unsigned math handles millis() rollover correctly
  uint16_t loopLen = bank.bankDuration;
  uint16_t playbackMs = (loopLen > 0) ? (uint16_t)(elapsedMs % loopLen) : 0;

  uint16_t animBpm, animOntime;
  uint8_t animDrunk, animProb, animSteps, animScrub;

  getAnimatedParams(playbackMs, animBpm, animOntime, animDrunk, animProb, animSteps, animScrub);

  bis.bpm = animBpm;
  bis.ontimeMs = animOntime;
  bis.drunk = animDrunk;
  bis.probability = animProb;
  bis.steps = animSteps;
  bis.scrub = animScrub;
  bis.intervalMs = 60000 / (bis.bpm * 4);

  webSocket.broadcastTXT("ANIM:" + String(animBpm) + ":" + String(animOntime) + ":" + String(animDrunk) + ":" +
                         String(animProb) + ":" + String(animSteps) + ":" + String(animScrub));
}

void initBankStorage() {
  littleFsReady = LittleFS.begin(true);
  logMessage(littleFsReady ? "LITTLEFS READY" : "LITTLEFS FAILED");
}

void loadBanksFromStorage() {
  int found = 0;
  int empty = 0;

  for (uint8_t bankId = 0; bankId < BIS_BANKS; bankId++) {
    BISBank& bank = banks[bankId];

    if (!littleFsReady) {
      bank.hasData = false;
      bank.paramFrameCount = 0;
      logMessage("BANK" + String(bankId) + " EMPTY");
      empty++;
      continue;
    }

    const String path = bankPath(bankId);
    if (!LittleFS.exists(path)) {
      bank.hasData = false;
      bank.paramFrameCount = 0;
      logMessage("BANK" + String(bankId) + " EMPTY");
      empty++;
      continue;
    }

    File file = LittleFS.open(path, FILE_READ);
    if (!file) {
      logFileOpenResult(false, path);
      logReadResult(false, path);
      bank.hasData = false;
      bank.paramFrameCount = 0;
      logMessage("BANK" + String(bankId) + " EMPTY");
      empty++;
      continue;
    }
    logFileOpenResult(true, path);

    const size_t bytesRead = file.read((uint8_t*)&bank, sizeof(BISBank));
    file.close();

    const bool readOk = (bytesRead == sizeof(BISBank));
    logReadResult(readOk, path);

    if (readOk && bank.hasData && bank.paramFrameCount <= MAX_PARAM_FRAMES) {
      found++;
      logMessage("BANK" + String(bankId) + " LOADED");
    } else {
      bank.hasData = false;
      bank.paramFrameCount = 0;
      empty++;
      logMessage("BANK" + String(bankId) + " EMPTY");
    }
  }

  logMessage("BANKS FOUND: " + String(found));
  logMessage("BANKS EMPTY: " + String(empty));
}

void reportFilesystemStatus() {
  logMessage("LITTLEFS STATUS");

  for (uint8_t bankId = 0; bankId < BIS_BANKS; bankId++) {
    const String filename = "bank" + String(bankId) + ".bin";

    if (!littleFsReady) {
      logMessage(filename + " MISSING");
      continue;
    }

    const String path = "/" + filename;
    if (!LittleFS.exists(path)) {
      logMessage(filename + " MISSING");
      continue;
    }

    File file = LittleFS.open(path, FILE_READ);
    if (!file) {
      logFileOpenResult(false, path);
      logMessage(filename + " MISSING");
      continue;
    }
    logFileOpenResult(true, path);

    const size_t size = file.size();
    file.close();
    logMessage(filename + " SIZE=" + String(size));
  }
}
