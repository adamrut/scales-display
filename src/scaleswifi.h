#ifndef _SCALES_WIFI_
#define _SCALES_WIFI_

#include "scalesstate.h"

void printWifiStatus();
void initWifi(ProgramState * state);
uint8_t connectToWifi(const char * ssid, const char * pw);
#endif