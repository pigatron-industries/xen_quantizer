#ifndef SequencerInterface_h
#define SequencerInterface_h

#include <eurorack_graphics.h>
#include "Hardware.h"

class SequencerInterface {
    public:
        SequencerInterface() {}
        void init();
        void render();

    private:
        FocusManager<TFTDisplay> focusManager;

        VerticalContainer<TFTDisplay, 1> page;
        TextComponent<TFTDisplay> title = TextComponent<TFTDisplay>(TFTDisplay::WIDTH, "SEQUENCER", 2, TFT_ORANGE);

        MessageBoxComponent<TFTDisplay> messageBox = MessageBoxComponent<TFTDisplay>(TFTDisplay::WIDTH*0.5, TFTDisplay::HEIGHT*0.5, 2, TFT_ORANGE);
};

#endif
