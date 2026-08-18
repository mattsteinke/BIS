#include "bis_scheduler.h"

#include <esp_system.h>

#include "bis_banks.h"
#include "bis_state.h"
#include "bis_web.h"
#include "config.h"

void fireTrigger(int t, int st) {
  digitalWrite(outputPins[t], HIGH);
  outputs[t].active = true;
  outputs[t].ontimeDuration = bis.ontimeMs;
  outputs[t].endTime = millis() + bis.ontimeMs;
  webSocket.broadcastTXT("OUT:" + String(t) + ":" + String(bis.ontimeMs));
  logMessage("TRIG T" + String(t) + " S" + String(st) + " (" + String(bis.ontimeMs) + "ms)");
}

void pulseRGBRed() {
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.setBrightness(RGB_BRIGHTNESS);
  pixels.show();
  rgbActive = true;
  rgbEnd = millis() + bis.ontimeMs;
}

void updateOut() {
  for (int i = 0; i < TRACKS; i++) {
    if (outputs[i].active && millis() >= outputs[i].endTime) {
      digitalWrite(outputPins[i], LOW);
      outputs[i].active = false;
    }
  }
  if (rgbActive && millis() >= rgbEnd) {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
    rgbActive = false;
  }
}

void scheduler() {
  if (!bis.playing) return;

  if (isBankPlaying) {
    sendAnimatedParams();
  }

  if (millis() - lastStep < bis.intervalMs) return;
  lastStep = millis();

  int rangeStart, rangeEnd;
  getActiveRange(rangeStart, rangeEnd);

  float drunk = bis.drunk / 100.0f;
  bool rev = ((esp_random() % 10000) / 10000.0f) < drunk;

  if (rev) bis.currentStep--;
  else bis.currentStep++;

  if (bis.currentStep < rangeStart) bis.currentStep = rangeEnd;
  if (bis.currentStep > rangeEnd) bis.currentStep = rangeStart;

  logMessage("STEP=" + String(bis.currentStep) + (rev ? " REV" : " FWD") + " (range " + String(rangeStart) + "-" +
             String(rangeEnd) + ")");

  webSocket.broadcastTXT("P:" + String(bis.currentStep));
  pulseRGBRed();

  for (int t = 0; t < TRACKS; t++)
    if (bis.grid[t][bis.currentStep])
      if (((esp_random() % 10000) / 10000.0f) < (bis.probability / 100.0f))
        fireTrigger(t, bis.currentStep);
}
