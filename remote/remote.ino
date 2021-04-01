#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <U8g2_for_Adafruit_GFX.h>

#include "constants.h"
#include "setup.h"
#include "readInputs.h"
#include "screens.h"

void setup() {
  #if (RC_DEBUG)
    Serial.begin(57600);
  #endif

  configPins();
  configDisplay();
  splashScreen();
}

void loop() {
  readInputs();
  drawScreens();
}
