#include "scalesinterface.h"
#include <Arduino.h>
#include "scalesstate.h"
#include "scalesaws.h"
#include "scalesdisplay.h"

static void magicButtonClicked() {
  Serial.println("Button clicked");
  // connect to scales using ESPNow and ask for current reading
  // zero the scales at this point
  // might need to wait for a valid result
  // update display with result of reading
  ProgramState * state = getProgramState();
  double currentVal = state->weight;
  state->weight = currentVal + 0.25;
}

static void magicButtonPressed() {
  Serial.println("Button pressed");
  // connect to aws and publish weight outbound queue
  ProgramState * state = getProgramState();
  state->isUploading = true;
  renderDisplay(state);
  connectToAws(state);
  publishWeightToAWS(state);
}

void configureMagicButton() {
  ProgramState * state = getProgramState();
  state->magicButton.attachClick(magicButtonClicked);
  state->magicButton.attachLongPressStop(magicButtonPressed);
}
