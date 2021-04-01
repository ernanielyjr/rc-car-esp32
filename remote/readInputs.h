int homeKeyHold = 0;

void homeKey() {
  if (!digitalRead(HOME_DIGITAL)) {
    delay(250);

    if (!digitalRead(HOME_DIGITAL)) {
      homeKeyHold++;

      if (homeKeyHold >= 12) {
        display.clearDisplay();
        u8g2.setCursor(0, 9);
        u8g2.print("restarting...");
        display.display();
        delay(2000);
        ESP.restart();
      }
      return;
    }

    homeKeyHold = 0;
    selectedScreen++;

    if (selectedScreen >= sizeof(screens) / sizeof(screens[0])) {
      selectedScreen = 0;
    }
  }
}

void readInputs() {
  homeKey();
}
