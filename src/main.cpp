#include <Arduino.h>
#include <LittleFS.h>
#include <WiFi.h>
#include "bis_banks.h"
#include "bis_scheduler.h"
#include "bis_state.h"
#include "bis_web.h"
#include "config.h"

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
    if (server.method() != HTTP_GET) {
      server.send(405, "text/plain", "Method Not Allowed");
      return;
    }
    File file = LittleFS.open("/index.html", FILE_READ);
    if (!file) {
      server.send(500, "text/plain", "Missing /index.html");
      return;
    }
    server.streamFile(file, "text/html");
    file.close();
  });
  server.on("/style.css", []() {
    if (server.method() != HTTP_GET) {
      server.send(405, "text/plain", "Method Not Allowed");
      return;
    }
    File file = LittleFS.open("/style.css", FILE_READ);
    if (!file) {
      server.send(500, "text/plain", "Missing /style.css");
      return;
    }
    server.streamFile(file, "text/css");
    file.close();
  });
  server.on("/app.js", []() {
    if (server.method() != HTTP_GET) {
      server.send(405, "text/plain", "Method Not Allowed");
      return;
    }
    File file = LittleFS.open("/app.js", FILE_READ);
    if (!file) {
      server.send(500, "text/plain", "Missing /app.js");
      return;
    }
    server.streamFile(file, "application/javascript");
    file.close();
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
