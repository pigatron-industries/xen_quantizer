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

        void setTuningName(char* name);
        void setTuning(Tuning* tuning);
        void setChannel(int outputChannel, int midiChannel);

        void focusTuning();
        void focusChannel(int outputChannel);

        void showMessage(const char* message);

    private:
        FocusManager<TFTDisplay> focusManager;

        VerticalContainer<TFTDisplay, 3> page;
        TextComponent<TFTDisplay> title = TextComponent<TFTDisplay>(TFTDisplay::WIDTH, "MIDI INPUT", 2, TFT_ORANGE);
        FieldComponent<TFTDisplay> tuningField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "TUNING:");

        HorizontalContainer<TFTDisplay, 4> channelsRow;
        FieldComponent<TFTDisplay> channelFields[4] = {
            FieldComponent<TFTDisplay>(TFTDisplay::WIDTH/4, TFTDisplay::WIDTH/8, "CH0:"),
            FieldComponent<TFTDisplay>(TFTDisplay::WIDTH/4, TFTDisplay::WIDTH/8, "CH1:"),
            FieldComponent<TFTDisplay>(TFTDisplay::WIDTH/4, TFTDisplay::WIDTH/8, "CH2:"),
            FieldComponent<TFTDisplay>(TFTDisplay::WIDTH/4, TFTDisplay::WIDTH/8, "CH3:")
        };

        MessageBoxComponent<TFTDisplay> messageBox = MessageBoxComponent<TFTDisplay>(TFTDisplay::WIDTH*0.5, TFTDisplay::HEIGHT*0.5, 2, TFT_ORANGE);
};

#endif
