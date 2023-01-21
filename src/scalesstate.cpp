#include "scalesstate.h"

static WiFiMulti wifiMultiInstance;

createSafeString(displayWeightValue, 16);

ProgramState programState = {
  wifiMultiInstance,
  MQTTClient(256),
  WiFiClientSecure(),
  77.5,
  false,
  OneButton(MAGIC_BUTTON_PIN, true, true),
  displayWeightValue,
  false
};

ProgramState * getProgramState() {
  return &programState;
}
