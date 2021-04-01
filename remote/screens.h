#include "screensMainPanel.h"
#include "screensDebug.h"

void drawScreens() {
  homeKey();
  display.clearDisplay();

  if (selectedScreen > 0) {
    display.fillRect(0, 0, 128, 13, WHITE);
    u8g2.setForegroundColor(BLACK);
    u8g2.setBackgroundColor(WHITE);
    u8g2.setCursor(1, 10);
    u8g2.print(screens[selectedScreen]);
    u8g2.setForegroundColor(WHITE);
    u8g2.setBackgroundColor(BLACK);
  }

  switch(selectedScreen) {
    case 0:
      mainPanel();
      break;
    case 1:
      // TODO: configScreen();
      break;
    case 2:
      debugInfo();
      break;
    case 3:
      debugAnalogs();
      break;
    case 4:
      debugDigitals();
      break;
  }

  display.display();
}
