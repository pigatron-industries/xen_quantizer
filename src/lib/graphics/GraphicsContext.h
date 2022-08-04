#ifndef GraphicsContext_h
#define GraphicsContext_h

#include <inttypes.h>

class GraphicsContext {
    public:
        GraphicsContext() {}
        virtual void init() = 0;

        virtual void clear() = 0;
        virtual void update() = 0;
        virtual void text(const char* text, uint8_t x = 0, uint8_t y = 0) = 0;
        // void text(int num, uint8_t x = TEXTLINE_1, uint8_t y = 0, uint8_t w = DISPLAY_WIDTH);
        // void drawWaveShape(WaveShape* waveShape, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t n = 1, bool bipolar = true);
    
        // static constexpr uint8_t LINE_HEIGHT = DISPLAY_FONT_HEIGHT+1;
        // static constexpr uint8_t TEXTLINE_1 = 0;
        // static constexpr uint8_t TEXTLINE_2 = LINE_HEIGHT;
        // static constexpr uint8_t TEXTLINE_3 = LINE_HEIGHT*2;
        // static constexpr uint8_t TEXTLINE_4 = LINE_HEIGHT*3;
    
    protected: 
};

#endif
