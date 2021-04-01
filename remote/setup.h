void configPins() {
  pinMode(HOME_DIGITAL, INPUT_PULLUP);

  pinMode(SELECT_DIGITAL, INPUT_PULLUP);
  pinMode(START_DIGITAL, INPUT_PULLUP);

  pinMode(UP_DIGITAL, INPUT_PULLUP);
  pinMode(DOWN_DIGITAL, INPUT_PULLUP);
  pinMode(LEFT_DIGITAL, INPUT_PULLUP);
  pinMode(RIGHT_DIGITAL, INPUT_PULLUP);

  pinMode(SQUARE_DIGITAL, INPUT_PULLUP);
  pinMode(TRIANGLE_DIGITAL, INPUT_PULLUP);
  pinMode(CROSS_DIGITAL, INPUT_PULLUP);
  pinMode(CIRCLE_DIGITAL, INPUT_PULLUP);

  pinMode(L1_DIGITAL, INPUT_PULLUP);
  pinMode(R1_DIGITAL, INPUT_PULLUP);

  pinMode(LX_ANALOG, INPUT);
  pinMode(LY_ANALOG, INPUT);
  pinMode(RX_ANALOG, INPUT);
  pinMode(RY_ANALOG, INPUT);
  pinMode(L2_ANALOG, INPUT);
  pinMode(R2_ANALOG, INPUT);

  pinMode(VIBRATE_OUT, OUTPUT);
}

void configDisplay() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;);
  }

  display.clearDisplay();
  display.setRotation(2);

  u8g2.begin(display);
  u8g2.setFont(u8g2_font_bitcasual_tf);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2.setForegroundColor(WHITE);
}

void splashScreen() {
  if (!digitalRead(HOME_DIGITAL)) {
    display.display();
    delay(250);
    return;
  }


  display.drawBitmap(0, 0, splashScreenImage, 128, 64, WHITE);
  display.display();
  digitalWrite(VIBRATE_OUT, HIGH);
  delay(200);
  digitalWrite(VIBRATE_OUT, LOW);
  delay(2300);

  digitalWrite(VIBRATE_OUT, HIGH);
  for (int i = 1; i <= 64; i*=2) {
    display.fillCircle(16, 32, i, WHITE);
    display.fillCircle(128 - 16, 32, i, WHITE);
    display.display();
    delay(30);
  }
  delay(500);
  digitalWrite(VIBRATE_OUT, LOW);
  display.clearDisplay();
  display.display();
}
