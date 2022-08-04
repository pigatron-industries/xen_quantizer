#include "Display.h"

void Display::init() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_NAVY);
    tft.setTextColor(TFT_WHITE);
    tft.drawChar('R', 0, 0);
}