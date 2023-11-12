#ifndef Display_h
#define Display_h

#include <eurorack_graphics.h>
#define setup_t etft_espi_setup_t // fix conflict between TFT_eSPI and usb_host
#include <TFT_eSPI.h>


class TFTDisplay : public GraphicsContext {
    public:
        static const uint16_t WIDTH = TFT_HEIGHT;
        static const uint16_t HEIGHT = TFT_WIDTH;

        static const uint16_t DEF_COLOUR_TEXT = TFT_WHITE;
        static const uint16_t DEF_COLOUR_BACK = TFT_BLACK;
        static const uint16_t DEF_COLOUR_FOCUS_TEXT = TFT_WHITE;
        static const uint16_t DEF_COLOUR_FOCUS_BACK = TFT_NAVY;

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
