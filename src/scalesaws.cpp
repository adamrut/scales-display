#include <ArduinoJson.h>
#include "secure.h"
#include "scalesstate.h"
#include "scalesaws.h"


static void scaleReadingHandler(String &topic, String &payload) {
  Serial.println("Message received from AWS: " + payload);
  // read in result from google sheets via AWS
  // -1 weight went down, 0 weight is the same, 1 weight went up
  // updatedate display with graphic representation of result (maybe smileys)
  StaticJsonDocument<128> resultDoc;
  deserializeJson(resultDoc, payload);
}


void connectToAws(ProgramState * state) {
  state->net.setCACert(AWS_CERT_CA);
  state->net.setCertificate(AWS_CERT_CRT);
  state->net.setPrivateKey(AWS_CERT_PRIVATE);

  Serial.println("Starting MQ Client");
  state->mqClient.begin(AWS_IOT_ENDPOINT, 8883, state->net);

  while (!state->mqClient.connect("scale_display")) {
    Serial.print(".");
    delay(100);
  }

  state->mqClient.subscribe(INBOUND_QUEUE);
}

void publishWeightToAWS(ProgramState * state) {
  StaticJsonDocument<128> msg;
  msg["name"] = "Adam";
  msg["weight"] = state->weight;
  char jsonBuffer[256];
  serializeJson(msg, jsonBuffer);
  Serial.println("Publishing Message");
  if (state->mqClient.publish(OUTBOUND_QUEUE, jsonBuffer)) {
    Serial.println("Message publish succeeded");
  } else {
    Serial.println("Message publish failed");
  }
}