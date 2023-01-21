#ifndef _SCALES_STATE_
#define _SCALES_STATE_

#include <WiFiMulti.h>
#include <MQTTClient.h>
#include <WiFiClientSecure.h>
#include <OneButton.h>
#include <SafeString.h>

#define OUTBOUND_QUEUE "scale_display_reading/topic"
#define INBOUND_QUEUE "scale_display_writing/topic"
#define WIFI_TIMEOUT 10000
#define MAGIC_BUTTON_PIN 4

typedef struct ProgramState {
  WiFiMulti wifiMulti;
  MQTTClient mqClient;
  WiFiClientSecure net;
  double weight;
  bool isConnected;
  OneButton magicButton;
  SafeString& displayWeight;
  bool isUploading;
} ProgramState;

ProgramState * getProgramState();
#endif