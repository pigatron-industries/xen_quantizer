#ifndef SequencerInterface_h
#define SequencerInterface_h

#include <eurorack_graphics.h>
#include "Hardware.h"

class SequencerInterface {
    public:
        SequencerInterface(const char* titleText) : title(TFTDisplay::WIDTH, titleText, 2, TFT_ORANGE) {}
        void init();
        void render();

        void setModel(char* modelName);
        void focusModel();

    private:
        FocusManager<TFTDisplay> focusManager;

        VerticalContainer<TFTDisplay, 4> page;
        TextComponent<TFTDisplay> title;
        FieldComponent<TFTDisplay> modelField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "MODEL:");

        MessageBoxComponent<TFTDisplay> messageBox = MessageBoxComponent<TFTDisplay>(TFTDisplay::WIDTH*0.5, TFTDisplay::HEIGHT*0.5, 2, TFT_ORANGE);
};

#endif