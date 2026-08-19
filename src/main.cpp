#include <Arduino.h>
#include <WiFi.h>
#include "bis_banks.h"
#include "bis_scheduler.h"
#include "bis_state.h"
#include "bis_web.h"
#include "config.h"
#include "web_page.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("=== BIS V13 BOOT ===");

  for (int i = 0; i < TRACKS; i++) pinMode(outputPins[i], OUTPUT);

  pixels.begin();
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.setBrightness(RGB_BRIGHTNESS);
  pixels.show();

  for (int i = 0; i < BIS_BANKS; i++) { 
    banks[i].hasData = false;
    banks[i].paramFrameCount = 0;
  }

  WiFi.mode(WIFI_AP);
  WiFi.softAP("BIS-ESP32", "harmonicbrain");

  server.on("/", []() {
    server.send_P(200, "text/html", PAGE_HTML);
  });
  server.begin();

  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);

  initBankStorage();
  loadBanksFromStorage();

  logMessage("BIS V13 START - BANK CAPTURE/RECALL WITH ANIMATION");
  logMessage("Board: Ozbot DRVKit (ESP32-S3)");
  logMessage("RGB LED: GPIO48 (NeoPixel)");
}

void loop() {
  server.handleClient();
  webSocket.loop();
  scheduler();
  updateOut();
}
