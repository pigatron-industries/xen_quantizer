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
        VerticalContainer<TFTDisplay, 4> page;
        TextComponent<TFTDisplay> title = TextComponent<TFTDisplay>(TFTDisplay::WIDTH, "SEQUENCER", 2, TFT_ORANGE);
};

#endif
