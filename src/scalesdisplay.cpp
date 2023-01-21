#include "scalesdisplay.h"
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>

Adafruit_SSD1306 oled(128, 32, &Wire, -1);

bool initDisplay() {
    return oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void renderDisplay(ProgramState * state) {
    oled.clearDisplay();
    oled.display();
    oled.clearDisplay();
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0, 0);
    oled.setTextSize(2);
    if (state->isUploading) {
        oled.print("Uploading");
    } else {
        oled.print(state->displayWeight.c_str());
    }
    oled.display();
}
