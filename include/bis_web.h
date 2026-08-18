#pragma once

#include <WebSocketsServer.h>

void logMessage(String m);
void syncCfg();
void sendFullState(uint8_t clientNum);
void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length);
