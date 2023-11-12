#ifndef MidiInterface_h
#define MidiInterface_h

#include <eurorack_graphics.h>
#include "Hardware.h"
// #include "NoteVisualiser.h"

class MidiInterface {
    public:
        MidiInterface() {}
        void init();
        void render();

    private:
        FocusManager<TFTDisplay> focusManager;

        VerticalContainer<TFTDisplay, 1> page;
        TextComponent<TFTDisplay> title = TextComponent<TFTDisplay>(TFTDisplay::WIDTH, "MIDI INPUT", 2, TFT_ORANGE);
};

#endif
