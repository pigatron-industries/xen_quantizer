#include "TFTDisplay.h"

void TFTDisplay::init() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
}

void TFTDisplay::clear() {
    tft.fillScreen(TFT_BLACK);
}

void TFTDisplay::update() {
    
}

// fonts

void TFTDisplay::setFont(uint8_t font) {
    tft.setTextFont(font);
}

uint16_t TFTDisplay::getFontHeight(uint8_t font) {
    return tft.fontHeight(font);
}

uint16_t TFTDisplay::getFontWidth(uint8_t font) {
    return 10;  //TODO add values for both fonts
}

// colours

void TFTDisplay::setTextColour(uint16_t colour) {
    tft.setTextColor(colour);
}


void TFTDisplay::text(const char* text, uint8_t x, uint8_t y) {
    tft.drawString(text, x, y);
}

void TFTDisplay::fillRectangle(int x, int y, int w, int h, int color) {
    tft.fillRect(x, y, w, h, color);
}

void TFTDisplay::drawRectangle(int x, int y, int w, int h, int color) {
    tft.drawRect(x, y, w, h, color);
}