#ifndef Display_h
#define Display_h

#include "lib/graphics/GraphicsContext.h"
#include <TFT_eSPI.h>

// #include <SPI.h>
// #include <Wire.h>

// #define DISPLAY_WIDTH 64

// #define DISPLAY_FONT u8g2_font_5x7_mf
// #define DISPLAY_FONT_HEIGHT 7
// #define DISPLAY_FONT_WIDTH 5

class TFTDisplay : public GraphicsContext {
    public:
        static const uint16_t WIDTH = TFT_HEIGHT;
        static const uint16_t HEIGHT = TFT_WIDTH;

        TFTDisplay() {}
        void init();

        void clear();
        void update();

        void setFont(uint8_t font);
        void text(const char* text, uint8_t x = 0, uint8_t y = 0);

        void fillRectangle(int x, int y, int w, int h, int color);
    
    protected: 
        TFT_eSPI tft = TFT_eSPI();

        // char buffer[13];
};

#endif
