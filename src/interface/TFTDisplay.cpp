#include "TFTDisplay.h"

void TFTDisplay::init() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_NAVY);
    tft.setTextColor(TFT_WHITE);
}

void TFTDisplay::clear() {
    tft.fillScreen(TFT_BLACK);
}

void TFTDisplay::update() {
    
}

void TFTDisplay::setFont(uint8_t font) {
    tft.setTextFont(font);
}

void TFTDisplay::text(const char* text, uint8_t x, uint8_t y) {
    tft.setTextColor(TFT_WHITE);
    tft.drawString(text, x, y);
}
