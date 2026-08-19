#pragma once

#include <Arduino.h>

void recordParamFrame();
void captureBank(uint8_t bankId);
int firstEmptyBank();
void stopRecording();
void getAnimatedParams(uint16_t playbackMs, uint16_t& outBpm, uint16_t& outOntime,
                       uint8_t& outDrunk, uint8_t& outProb, uint8_t& outSteps, uint8_t& outScrub);
void recallBank(uint8_t bankId);
void syncBankStatus();
void sendAnimatedParams();
void initBankStorage();
void loadBanksFromStorage();
void reportFilesystemStatus();
