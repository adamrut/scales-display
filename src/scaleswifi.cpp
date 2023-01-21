#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "scalesstate.h"
#include "scaleswifi.h"
#include "secure.h"

void printWifiStatus() {
  Serial.println("Connected to " + WiFi.SSID());
  //Serial.println("IP Address: " + WiFi.localIP());
}

void initWifi(ProgramState * state) {
  state->isConnected = false;
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  uint8_t wifiStatus = WL_DISCONNECTED;
  while (wifiStatus != WL_CONNECTED) {
    wifiStatus = connectToWifi(HOME_SSID, HOME_PW);
  }
  Serial.println("Connected");
  state->isConnected = true;
  printWifiStatus();
}

uint8_t connectToWifi(const char * ssid, const char * pw) {
  Serial.println("Connecting to wifi");
  WiFi.begin(ssid, pw);
  delay(1000);
  return WiFi.status();
}