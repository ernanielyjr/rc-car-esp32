#define BORDER_RADIUS 4
#define BTN_DEBOUNCE_DELAY 250
#define ARROW_ANIMATION_TIME 500

#define SPEED_MAX 100
#define SPEED_MAX_WITHOUT_NITRO 70
#define SPEED_DANGER 90
int speed = 0;

#define NITRO_RECHARGE_TIME 20000
#define NITRO_USE_TIME 5000
boolean usingNitro = false;
int nitro = 0;

int headlightsMode = 0; // 0 | 1 | 2

int arrowsMode = 0; // 0 | 1 | 2 | 3

void drawFrame(int x, int y, boolean inverse) {
  if (inverse) {
    display.fillRoundRect(x, y, 20, 20, BORDER_RADIUS, WHITE);
  } else {
    display.drawRoundRect(x, y, 20, 20, BORDER_RADIUS, WHITE);
  }
}

//////////////////////////////////////////////////////////////

void gauge() {
  int angle = map(speed, 0, SPEED_MAX, 135, 181);
  if (angle >= 181) {
    angle = 0;
  }

  int xCenter = 128 - 4;
  int yCenter = 64 - 2;

  int arc = 32;

  display.fillCircle(xCenter, yCenter, arc + 6, WHITE);
  display.fillCircle(xCenter, yCenter, arc + 4, BLACK);
  display.fillRect(126, 24, 2, 22, BLACK);

  float x1 = sin(2 * angle * 2 * 3.14 / 360);
  float y1 = cos(2 * angle * 2 * 3.14 / 360);
  display.drawLine(xCenter, yCenter, xCenter + arc * x1, yCenter - arc * y1, WHITE);

  display.fillCircle(xCenter, yCenter, arc - 14, WHITE);
  if (speed < SPEED_DANGER) {
    display.fillCircle(xCenter, yCenter, arc - 16, BLACK);
  }

  int xLabel = 128 - 8;
  if (speed > 99) xLabel = 128 - 20;
  else if (speed > 9) xLabel = 128 - 14;

  u8g2.setForegroundColor(speed >= SPEED_DANGER ? BLACK : WHITE);
  u8g2.setBackgroundColor(speed >= SPEED_DANGER ? WHITE : BLACK);
  u8g2.setCursor(xLabel, 63);
  u8g2.print(speed);
  u8g2.setForegroundColor(WHITE);
  u8g2.setBackgroundColor(BLACK);
}

void arrow(int x, int y, boolean inverse, boolean flipped){
  int color = WHITE;
  if (inverse) color = BLACK;

  drawFrame(x, y, inverse);

  if (flipped) {
    display.fillTriangle(x + 16, y +  9, x + 10, y +  3, x + 10, y +  9, color);
    display.fillTriangle(x + 16, y + 10, x + 10, y + 16, x + 10, y + 10, color);
    display.fillRect(x + 3, y + 7, 7, 6, color);
  } else {
    display.fillTriangle(x + 3, y +  9, x + 9, y +  3, x + 9, y +  9, color);
    display.fillTriangle(x + 3, y + 10, x + 9, y + 16, x + 9, y + 10, color);
    display.fillRect(x + 10, y + 7, 7, 6, color);
  }

}

void leftArrow(int x, int y, boolean inverse) {
  arrow(x, y, inverse, false);
}

void rightArrow(int x, int y, boolean inverse) {
  arrow(x, y, inverse, true);
}

void headlight(int x, int y, boolean inverse, boolean high) {
  int color = WHITE;
  if (inverse) color = BLACK;

  drawFrame(x, y, inverse);

  display.fillRect(x +  3, y +  7, 2, 6, color);
  display.fillRect(x +  4, y +  4, 2, 3, color);
  display.fillRect(x +  4, y + 13, 2, 3, color);
  display.fillRect(x +  5, y +  3, 2, 2, color);
  display.fillRect(x +  5, y + 15, 2, 2, color);
  display.fillRect(x +  7, y +  2, 3, 2, color);
  display.fillRect(x +  7, y + 16, 3, 2, color);
  display.fillRect(x +  9, y +  3, 2, 4, color);
  display.fillRect(x +  9, y + 13, 2, 4, color);
  display.fillRect(x + 10, y +  7, 2, 6, color);

  if (high) {
    display.fillRect(x + 12, y +  4, 6, 2, color);
    display.fillRect(x + 13, y +  9, 5, 2, color);
    display.fillRect(x + 12, y + 14, 6, 2, color);
  } else {
    display.drawLine(x + 12, y +  3, x + 17, y +  5, color);
    display.drawLine(x + 12, y +  4, x + 17, y +  6, color);
    display.drawLine(x + 13, y +  8, x + 17, y + 10, color);
    display.drawLine(x + 13, y +  9, x + 17, y + 11, color);
    display.drawLine(x + 12, y + 13, x + 17, y + 15, color);
    display.drawLine(x + 12, y + 14, x + 17, y + 16, color);
  }
}

void headlightNormal(int x, int y, boolean inverse) {
  headlight(x, y, inverse, false);
}

void headlightHigh(int x, int y, boolean inverse) {
  headlight(x, y, inverse, true);
}

void music(int x, int y, boolean inverse) {
  int color = WHITE;
  if (inverse) color = BLACK;

  drawFrame(x, y, inverse);

  display.fillRect(x +  5, y + 12, 4,  2, color);
  display.fillRect(x +  4, y + 13, 2,  2, color);
  display.fillRect(x +  5, y + 15, 5,  1, color);
  display.fillRect(x +  9, y +  4, 2, 11, color);
  display.fillRect(x + 13, y +  6, 3,  2, color);

  display.drawFastHLine(x +  5, y + 15, 5, color);
  display.drawFastHLine(x +  8, y + 14, 1, color);
  display.drawFastVLine(x + 11, y +  4, 2, color);
  display.drawFastVLine(x + 12, y +  5, 2, color);
  display.drawFastVLine(x + 16, y +  5, 2, color);

  if (!inverse) {
    display.drawLine(x + 5, y + 5, x + 15, y + 15, color);
    display.drawLine(x + 5, y + 6, x + 15, y + 16, color);
  }
}

void siren(int x, int y) {
  drawFrame(x, y, true);

  display.fillRect(x + 4, y + 16, 12,  2, BLACK);
  display.fillRect(x + 4, y + 11, 12,  4, BLACK);
  display.fillRect(x + 7, y +  8,  9,  3, BLACK);
  display.fillRect(x + 4, y +  8,  2,  3, BLACK);

  display.drawFastHLine(x + 6, y + 15, 8, BLACK);
  display.drawFastHLine(x + 8, y +  7, 7, BLACK);
  display.drawFastHLine(x + 6, y +  6, 8, BLACK);
  display.drawFastHLine(x + 7, y +  5, 6, BLACK);
  display.drawFastHLine(x + 5, y +  7, 2, BLACK);

  display.drawLine(x +  2, y + 2, x +  4, y + 4, BLACK);
  display.drawLine(x +  7, y + 1, x +  8, y + 3, BLACK);
  display.drawLine(x + 12, y + 1, x + 11, y + 3, BLACK);
  display.drawLine(x + 17, y + 2, x + 15, y + 4, BLACK);
}

void unknownByNow(int x, int y, boolean inverse) {
  drawFrame(x, y, inverse);
}

void drawNitro(int x, int y, int w, int h) {
  const int fillNitro = map(nitro, 0, 100, 0, w - 4);
  const int textW = 40;

  const int spacing = BORDER_RADIUS / 2;

  display.fillRoundRect(x, y, w, h, BORDER_RADIUS, WHITE);
  display.fillRoundRect(x + 1, y + 10, w - 2, h - 11, BORDER_RADIUS, BLACK);

  u8g2.setForegroundColor(BLACK);
  u8g2.setBackgroundColor(WHITE);
  u8g2.setCursor(x + ((w - textW) / 2), y + 8 + 1);
  u8g2.print("NITRO");
  u8g2.setForegroundColor(WHITE);
  u8g2.setBackgroundColor(BLACK);

  display.fillRoundRect(x + 2, y + 11, fillNitro, h - 13, BORDER_RADIUS, WHITE);
  display.drawRoundRect(x + 1, y + 10, w - 2, h - 11, BORDER_RADIUS, BLACK);

  display.drawRoundRect(x - 1, y - 1, w + 2, h + 2, BORDER_RADIUS, BLACK);
}

unsigned long lastNitroMillis = 0;

void decreaseNitro() {
  if (nitro <= 0) {
    nitro = 0;
    return;
  }

  if (millis() - lastNitroMillis > NITRO_USE_TIME / 100) {
    nitro--;
    lastNitroMillis = millis();
  }
}

void increaseNitro() {
  if (nitro >= 100) {
    nitro = 100;
    return;
  }

  if (millis() - lastNitroMillis > NITRO_RECHARGE_TIME / 100) {
    nitro++;
    lastNitroMillis = millis();
  }
}

void handleNitro() {
  usingNitro = false;

  if (!digitalRead(btnNitro)) {
    decreaseNitro();
    if (nitro > 0) {
      usingNitro = true;
    }
  } else if (nitro < 100) {
    increaseNitro();
  }
}

void handleVibrate() {
  boolean vibrate = false;
  if (usingNitro) {
    vibrate = true;
  }

  // outras coisas que ativam a vibração

  digitalWrite(VIBRATE_OUT, vibrate ? HIGH : LOW);
}

void handleSpeed() {
  // TODO: se ficar segurando o acelerador, incrementar a velocidade aos poucos
  speed = map(analogRead(RX_ANALOG), 0, 4095, 0, usingNitro ? SPEED_MAX : SPEED_MAX_WITHOUT_NITRO);
}

unsigned long btnHeadlightsMillis = 0;

void handleHeadlights() {
  const int button = digitalRead(btnHeadlights);
  if (!button && (millis() - btnHeadlightsMillis) > BTN_DEBOUNCE_DELAY) {
    headlightsMode++;
    if (headlightsMode > 2) {
      headlightsMode = 0;
    }

    btnHeadlightsMillis = millis();
  }
}

unsigned long btnAlertArrowMillis = 0;
unsigned long btnLeftArrowMillis = 0;
unsigned long btnRightArrowMillis = 0;

void handleArrows() {
  const int buttonAlert = digitalRead(btnAlertArrow);
  const int buttonLeft = digitalRead(btnLeftArrow);
  const int buttonRight = digitalRead(btnRightArrow);

  Serial.print("arrowsMode: ");
  Serial.println(arrowsMode);

  if (!buttonAlert && (millis() - btnAlertArrowMillis) > BTN_DEBOUNCE_DELAY) {
    arrowsMode = arrowsMode == 3 ? 0 : 3;
    btnAlertArrowMillis = millis();
  }

  if (!buttonLeft && (millis() - btnLeftArrowMillis) > BTN_DEBOUNCE_DELAY) {
    arrowsMode = arrowsMode == 1 ? 0 : 1;
    btnLeftArrowMillis = millis();
  }

  if (!buttonRight && (millis() - btnRightArrowMillis) > BTN_DEBOUNCE_DELAY) {
    arrowsMode = arrowsMode == 2 ? 0 : 2;
    btnRightArrowMillis = millis();
  }
}

void actions() {
  handleNitro();
  handleVibrate();
  handleSpeed();
  handleHeadlights();
  handleArrows();
}

unsigned long stateLeftArrowMillis = 0;
boolean stateLeftArrow = false;
boolean animateLeftArrowState() {
  const boolean active = arrowsMode == 1 || arrowsMode == 3;
  if (!active) return false;

  if (millis() - stateLeftArrowMillis > ARROW_ANIMATION_TIME) {
    stateLeftArrow = !stateLeftArrow;
    stateLeftArrowMillis = millis();
  }

  return stateLeftArrow;
};

unsigned long stateRightArrowMillis = 0;
boolean stateRightArrow = false;
boolean animateRightArrowState() {
  const boolean active = arrowsMode == 2 || arrowsMode == 3;
  if (!active) return false;

  if (millis() - stateRightArrowMillis > ARROW_ANIMATION_TIME) {
    stateRightArrow = !stateRightArrow;
    stateRightArrowMillis = millis();
  }

  return stateRightArrow;
};

void visual() {
  const boolean state = false;

  leftArrow(1, 0, animateLeftArrowState());

  headlightNormal(22, 0, headlightsMode >= 1);
  headlightHigh(43, 0, headlightsMode == 2);

  // if (false) {
  //   siren(64, 0);
  // } else {
  //   music(64, 0, state);
  // }

  // unknownByNow(85, 0, state); // TODO: botar algo util
  rightArrow(106, 0, animateRightArrowState());

  drawNitro(0, 64 - 30, 80, 30);
  gauge();
}

void mainPanel() {
  // sendData();
  actions();
  visual();
}
