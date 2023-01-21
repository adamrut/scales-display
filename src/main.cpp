#include <Arduino.h>
#include "secure.h"
#include "scalesstate.h"
#include "scaleswifi.h"
#include "scalesinterface.h"
#include "scalesdisplay.h"

void setup() {
  Serial.println("Initialising Wifi connection");
  ProgramState * state = getProgramState();
  Serial.begin(921600);
  pinMode(LED_BUILTIN, OUTPUT);
  initWifi(state);

  Serial.println("Program State: ");
  Serial.println(state->weight);
  
  if (!initDisplay()) {
    Serial.println("Display initialisation failed!");
  }
  
  state->displayWeight.clear();
  state->displayWeight.print("Loading");
  Serial.println(state->displayWeight.c_str());
  Serial.println("Before render");
  renderDisplay(state);
  
  configureMagicButton();

  digitalWrite(LED_BUILTIN, HIGH);
}

double lastWeight = 0.0;

void loop() {
  delay(100);
  ProgramState * state = getProgramState();
  state->magicButton.tick();

  if (WiFi.status() != WL_CONNECTED) {
    initWifi(state);
  }

  if (state->weight != lastWeight) {
    Serial.println(state->weight);
    state->displayWeight.clear();
    state->displayWeight.print(state->weight);
    state->displayWeight.print("kg");
    renderDisplay(state);
    lastWeight = state->weight;
  }
  

  // draw display based on state
  // - Wifi status
  // - Current weight reading
  // - Result graphic
  // - Progress info
}

