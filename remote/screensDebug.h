void debugInfo() {
  u8g2.setCursor(0, 14 + 9);
  u8g2.print("Firmware version");

  u8g2.setCursor(0, 28 + 9);
  u8g2.print("Mac Address");

  u8g2.setCursor(0, 42 + 9);
  u8g2.print("IP");

  u8g2.setCursor(0, 60 + 9);
  u8g2.print("SSID");
}

void debugAnalogs() {
  // TODO: usar posições relativas
  display.drawRect(0, 14, 10, 50, WHITE);  // L2 frame
  display.drawRect(11, 14, 50, 50, WHITE); // LX/LY frame
  display.drawRect(65, 14, 50, 50, WHITE); // RX/RY frame
  display.drawRect(116, 14, 10, 50, WHITE); // R2 frame

  const int lx = map(analogRead(LX_ANALOG), 0, 4095, 13, 58);
  const int ly = map(analogRead(LY_ANALOG), 0, 4095, 16, 61);
  const int l2 = map(analogRead(L2_ANALOG), 0, 4095, 0, 50);

  const int rx = map(analogRead(RX_ANALOG), 0, 4095, 67, 112);
  const int ry = map(analogRead(RY_ANALOG), 0, 4095, 16, 61);
  const int r2 = map(analogRead(R2_ANALOG), 0, 4095, 0, 50);

  display.fillCircle(lx, ly, 2, WHITE);
  display.fillCircle(rx, ry, 2, WHITE);

  display.fillRect(2, 16 + l2, 6, 46 - l2, WHITE);
  display.fillRect(118, 16 + r2, 6, 46 - r2, WHITE);
}

void debugDigitals() {
  const int select = digitalRead(SELECT_DIGITAL);
  const int start = digitalRead(START_DIGITAL);

  const int up = digitalRead(UP_DIGITAL);
  const int down = digitalRead(DOWN_DIGITAL);
  const int left = digitalRead(LEFT_DIGITAL);
  const int right = digitalRead(RIGHT_DIGITAL);

  const int square = digitalRead(SQUARE_DIGITAL);
  const int triangle = digitalRead(TRIANGLE_DIGITAL);
  const int cross = digitalRead(CROSS_DIGITAL);
  const int circle = digitalRead(CIRCLE_DIGITAL);

  const int l1 = digitalRead(L1_DIGITAL);
  const int r1 = digitalRead(R1_DIGITAL);

  const int circleRadius = 7;
  const int circleSpacing = 5;

  const int rectW = 20;
  const int rectH = 10;

  int areaW = 50;
  int areaH = 50;

  /////////////////////////////////////

  int baseX = 0;
  int baseY = 14;

  int middleX = areaW / 2 + baseX - 1;
  int middleY = areaH / 2 + baseY - 1;

  if (up) display.drawCircle(middleX, middleY - circleRadius - circleSpacing, circleRadius, WHITE);
  else display.fillCircle(middleX, middleY - circleRadius - circleSpacing, circleRadius, WHITE);
  if (right) display.drawCircle(middleX + circleRadius + circleSpacing, middleY, circleRadius, WHITE);
  else display.fillCircle(middleX + circleRadius + circleSpacing, middleY, circleRadius, WHITE);
  if (down) display.drawCircle(middleX, middleY + circleRadius + circleSpacing, circleRadius, WHITE);
  else display.fillCircle(middleX, middleY + circleRadius + circleSpacing, circleRadius, WHITE);
  if (left) display.drawCircle(middleX - circleRadius - circleSpacing, middleY, circleRadius, WHITE);
  else display.fillCircle(middleX - circleRadius - circleSpacing, middleY, circleRadius, WHITE);

  if (l1) display.drawRoundRect(baseX + areaW - (rectW / 2) - 1, baseY, rectW, rectH, 5, WHITE);
  else display.fillRoundRect(baseX + areaW - (rectW / 2) - 1, baseY, rectW, rectH, 5, WHITE);

  if (select) display.drawRoundRect(baseX + areaW - (rectW / 2) - 1, baseY + areaH - rectH, rectW, rectH, 5, WHITE);
  else display.fillRoundRect(baseX + areaW - (rectW / 2) - 1, baseY + areaH - rectH, rectW, rectH, 5, WHITE);

  /////////////////////////////////////

  baseX = 128 - areaW;
  baseY = 14;

  middleX = areaW / 2 + baseX - 1;
  middleY = areaH / 2 + baseY - 1;

  if (triangle) display.drawCircle(middleX, middleY - circleRadius - circleSpacing, circleRadius, WHITE);
  else display.fillCircle(middleX, middleY - circleRadius - circleSpacing, circleRadius, WHITE);
  if (circle) display.drawCircle(middleX + circleRadius + circleSpacing, middleY, circleRadius, WHITE);
  else display.fillCircle(middleX + circleRadius + circleSpacing, middleY, circleRadius, WHITE);
  if (cross) display.drawCircle(middleX, middleY + circleRadius + circleSpacing, circleRadius, WHITE);
  else display.fillCircle(middleX, middleY + circleRadius + circleSpacing, circleRadius, WHITE);
  if (square) display.drawCircle(middleX - circleRadius - circleSpacing, middleY, circleRadius, WHITE);
  else display.fillCircle(middleX - circleRadius - circleSpacing, middleY, circleRadius, WHITE);

  if (r1) display.drawRoundRect(baseX - (rectW / 2) + 1, baseY, rectW, rectH, 5, WHITE);
  else display.fillRoundRect(baseX - (rectW / 2) + 1, baseY, rectW, rectH, 5, WHITE);

  if (start) display.drawRoundRect(baseX - (rectW / 2) + 1, baseY + areaH - rectH, rectW, rectH, 5, WHITE);
  else display.fillRoundRect(baseX - (rectW / 2) + 1, baseY + areaH - rectH, rectW, rectH, 5, WHITE);
}