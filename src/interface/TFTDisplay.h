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

        // display info
        uint16_t getWidth() { return WIDTH; }
        uint16_t getHeight() { return HEIGHT; }

        // fonts
        void setFont(uint8_t font);
        uint16_t getFontHeight(uint8_t font);
        uint16_t getFontWidth(uint8_t font);

        // colours
        void setTextColour(uint16_t colour);

        // text
        void text(const char* text, uint8_t x = 0, uint8_t y = 0);

        // shapes
        void fillRectangle(int x, int y, int w, int h, int color);
        void drawRectangle(int x, int y, int w, int h, int color);
    
    protected: 
        TFT_eSPI tft = TFT_eSPI();

        // char buffer[13];
};

#endif
