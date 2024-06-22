#ifndef SequencerInterface_h
#define SequencerInterface_h

#include <eurorack_graphics.h>
#include "Hardware.h"
#include "SequencerVisualiser.h"

class SequencerInterface {
    public:
        SequencerInterface() {}
        void init();
        void render();

        void setSequencer(Sequencer* sequencer) {
            sequencerVisualiser.setSequencer(sequencer);
        }

        void setPattern(int pattern) {
            patternField.setValue(pattern);
            render();
        }

        void setCurrentTick(int16_t tick) {
            sequencerVisualiser.setCurrentTick(tick);
        }

        void focusPattern() {
            focusManager.setFocus(&patternField);
        }

    private:
        FocusManager<TFTDisplay> focusManager;

        VerticalContainer<TFTDisplay, 3> page;
        TextComponent<TFTDisplay> title = TextComponent<TFTDisplay>(TFTDisplay::WIDTH, "SEQUENCER", 2, TFT_ORANGE);
        FieldComponent<TFTDisplay> patternField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, TFTDisplay::WIDTH/2, "Pattern", 1, TFT_WHITE);
        SequencerVisualiser<TFTDisplay> sequencerVisualiser = SequencerVisualiser<TFTDisplay>(TFTDisplay::WIDTH, 4*3);

        MessageBoxComponent<TFTDisplay> messageBox = MessageBoxComponent<TFTDisplay>(TFTDisplay::WIDTH*0.5, TFTDisplay::HEIGHT*0.5, 2, TFT_ORANGE);
};

#endif
