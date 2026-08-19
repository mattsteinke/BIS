#include "bis_web.h"

#include "bis_banks.h"
#include "bis_state.h"

void logMessage(String m) {
  Serial.println(m);
  webSocket.broadcastTXT("LOG:" + m);
}

void syncCfg() {
  webSocket.broadcastTXT("CFG:" + String(bis.bpm) + ":" + String(bis.ontimeMs) + ":" + String(bis.drunk) + ":" +
                         String(bis.probability) + ":" + String(bis.steps) + ":" + String(bis.scrub));
  int rangeStart, rangeEnd;
  getActiveRange(rangeStart, rangeEnd);
  webSocket.broadcastTXT("RNG:" + String(rangeStart) + ":" + String(rangeEnd));
}

void sendFullState(uint8_t clientNum) {
  webSocket.sendTXT(clientNum, "CFG:" + String(bis.bpm) + ":" + String(bis.ontimeMs) + ":" + String(bis.drunk) + ":" +
                              String(bis.probability) + ":" + String(bis.steps) + ":" + String(bis.scrub));
  int rangeStart, rangeEnd;
  getActiveRange(rangeStart, rangeEnd);
  webSocket.sendTXT(clientNum, "RNG:" + String(rangeStart) + ":" + String(rangeEnd));
  webSocket.sendTXT(clientNum, "P:" + String(bis.currentStep));
  for (int t = 0; t < TRACKS; t++)
    for (int s = 0; s < MAX_STEPS; s++)
      webSocket.sendTXT(clientNum, "G:" + String(t) + ":" + String(s) + ":" + String(bis.grid[t][s] ? 1 : 0));

  syncBankStatus();
}

void broadcastFullState() {
  webSocket.broadcastTXT("CFG:" + String(bis.bpm) + ":" + String(bis.ontimeMs) + ":" + String(bis.drunk) + ":" +
                         String(bis.probability) + ":" + String(bis.steps) + ":" + String(bis.scrub));
  int rangeStart, rangeEnd;
  getActiveRange(rangeStart, rangeEnd);
  webSocket.broadcastTXT("RNG:" + String(rangeStart) + ":" + String(rangeEnd));
  webSocket.broadcastTXT("P:" + String(bis.currentStep));
  for (int t = 0; t < TRACKS; t++)
    for (int s = 0; s < MAX_STEPS; s++)
      webSocket.broadcastTXT("G:" + String(t) + ":" + String(s) + ":" + String(bis.grid[t][s] ? 1 : 0));
  syncBankStatus();
}

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t) {
  if (type == WStype_CONNECTED) {
    sendFullState(num);
    logMessage("CLIENT CONNECTED");
    return;
  }
  if (type != WStype_TEXT) return;

  String m = (char*)payload;

  if (m == "PLAY") {
    if (!isRecording && !bis.playing) {
      bis.playing = true;
      lastStep = 0;
      logMessage("PLAY");
    }
  } else if (m == "STOP") {
    bis.playing = false;
    if (isRecording) stopRecording();
    if (isBankPlaying) {
      isBankPlaying = false;
      selectedBank = 255;
    }
    logMessage("STOP");
    syncBankStatus();
  } else if (m == "RECORD") {
    if (!isRecording) {
      int target = -1;
      if (overwriteMode && overwriteTargetBank < BIS_BANKS) {
        target = overwriteTargetBank;
      } else {
        target = firstEmptyBank();
      }
      if (target < 0) {
        logMessage("RECORD - NO EMPTY BANKS AVAILABLE");
      } else {
        recordingBank = target;
        isRecording = true;
        recordStartTime = millis();
        lastRecordedParamMs = 0;
        banks[recordingBank].paramFrameCount = 0;
        recordParamFrame();
        logMessage("RECORD START - BANK " + String(target + 1));
      }
    } else {
      stopRecording();
    }
    syncBankStatus();
  } else if (m.startsWith("BANK:")) {
    uint8_t bankId = m.substring(5).toInt();
    if (bankId >= BIS_BANKS) return;
    if (isRecording) {
      if (bankId == recordingBank) {
        stopRecording();
        syncBankStatus();
      } else {
        logMessage("Bank locked while recording");
      }
      return;
    }
    if (overwriteMode) {
      overwriteTargetBank = bankId;
      logMessage("OVERWRITE TARGET = BANK " + String(bankId + 1));
      syncBankStatus();
      return;
    }
    if (banks[bankId].hasData) {
      recallBank(bankId);
      broadcastFullState();
    } else {
      logMessage("BANK" + String(bankId) + " NOT FOUND");
    }
  } else if (m == "OVERWRITE") {
    if (isRecording) return;
    overwriteMode = !overwriteMode;
    if (overwriteMode) {
      overwriteTargetBank = 255;
      logMessage("OVERWRITE MODE ON");
    } else {
      overwriteTargetBank = 255;
      logMessage("OVERWRITE MODE OFF");
    }
    syncBankStatus();
  } else if (m == "FILESYS:") {
    reportFilesystemStatus();
  } else if (m.startsWith("BPM:")) {
    if (!isRecording && !isBankPlaying) {
      bis.bpm = m.substring(4).toInt();
      bis.intervalMs = 60000 / (bis.bpm * 4);
      syncCfg();
    } else if (isRecording) {
      bis.bpm = m.substring(4).toInt();
      bis.intervalMs = 60000 / (bis.bpm * 4);
      recordParamFrame();
    }
  } else if (m.startsWith("ONT:")) {
    if (!isRecording && !isBankPlaying) {
      bis.ontimeMs = m.substring(4).toInt();
      syncCfg();
    } else if (isRecording) {
      bis.ontimeMs = m.substring(4).toInt();
      recordParamFrame();
    }
  } else if (m.startsWith("DRUNK:")) {
    if (!isRecording && !isBankPlaying) {
      bis.drunk = constrain(m.substring(6).toInt(), 0, 100);
      syncCfg();
    } else if (isRecording) {
      bis.drunk = constrain(m.substring(6).toInt(), 0, 100);
      recordParamFrame();
    }
  } else if (m.startsWith("PROB:")) {
    if (!isRecording && !isBankPlaying) {
      bis.probability = constrain(m.substring(5).toInt(), 0, 100);
      syncCfg();
    } else if (isRecording) {
      bis.probability = constrain(m.substring(5).toInt(), 0, 100);
      recordParamFrame();
    }
  } else if (m.startsWith("STEPS:")) {
    if (!isRecording && !isBankPlaying) {
      bis.steps = constrain(m.substring(6).toInt(), 1, MAX_STEPS);
      logMessage("STEPS=" + String(bis.steps));
      syncCfg();
    } else if (isRecording) {
      bis.steps = constrain(m.substring(6).toInt(), 1, MAX_STEPS);
      recordParamFrame();
    }
  } else if (m.startsWith("SCRUB:")) {
    if (!isRecording && !isBankPlaying) {
      bis.scrub = constrain(m.substring(6).toInt(), 0, MAX_STEPS - 1);
      logMessage("SCRUB=" + String(bis.scrub));
      syncCfg();
    } else if (isRecording) {
      bis.scrub = constrain(m.substring(6).toInt(), 0, MAX_STEPS - 1);
      recordParamFrame();
    }
  } else if (m.startsWith("S:")) {
    if (!isBankPlaying) {
      int a = m.indexOf(':');
      int b = m.indexOf(':', a + 1);
      int t = m.substring(a + 1, b).toInt();
      int s = m.substring(b + 1).toInt();
      bis.grid[t][s] = !bis.grid[t][s];
      webSocket.broadcastTXT("G:" + String(t) + ":" + String(s) + ":" + String(bis.grid[t][s] ? 1 : 0));
    }
  }
}
