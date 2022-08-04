#ifndef Display_h
#define Display_h

#include <TFT_eSPI.h>

// #include <SPI.h>
// #include <Wire.h>

// #define DISPLAY_WIDTH 64

// #define DISPLAY_FONT u8g2_font_5x7_mf
// #define DISPLAY_FONT_HEIGHT 7
// #define DISPLAY_FONT_WIDTH 5

class Display {
    public:
        Display() {}
        void init();

        void clear();
        void update();
        // void text(const char* text, uint8_t x = TEXTLINE_1, uint8_t y = 0, uint8_t w = DISPLAY_WIDTH);
        // void text(int num, uint8_t x = TEXTLINE_1, uint8_t y = 0, uint8_t w = DISPLAY_WIDTH);
        // void drawWaveShape(WaveShape* waveShape, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t n = 1, bool bipolar = true);
    
        // static constexpr uint8_t LINE_HEIGHT = DISPLAY_FONT_HEIGHT+1;
        // static constexpr uint8_t TEXTLINE_1 = 0;
        // static constexpr uint8_t TEXTLINE_2 = LINE_HEIGHT;
        // static constexpr uint8_t TEXTLINE_3 = LINE_HEIGHT*2;
        // static constexpr uint8_t TEXTLINE_4 = LINE_HEIGHT*3;
    
    protected: 
        TFT_eSPI tft = TFT_eSPI();

        // char buffer[13];
};

#endif
