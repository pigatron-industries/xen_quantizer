#ifndef HarmonicWalkInterface_h
#define HarmonicWalkInterface_h

#include <eurorack_graphics.h>
#include "Hardware.h"

class HarmonicWalkInterface {
    public:
        HarmonicWalkInterface() {}
        void init();
        void render();

        void setTuningName(char* name);
        void setTuning(Tuning* tuning);
        void setInterval(int interval);

        void focusTuning();
        void focusInterval();

        void showMessage(const char* message);

    private:
        FocusManager<TFTDisplay> focusManager;

        VerticalContainer<TFTDisplay, 7> page;
        TextComponent<TFTDisplay> title = TextComponent<TFTDisplay>(TFTDisplay::WIDTH, "HARMONIC WALK", 2, TFT_ORANGE);
        FieldComponent<TFTDisplay> tuningField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "TUNING:");
        FieldComponent<TFTDisplay> intervalField  = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "INTERVAL:");

        MessageBoxComponent<TFTDisplay> messageBox = MessageBoxComponent<TFTDisplay>(TFTDisplay::WIDTH*0.5, TFTDisplay::HEIGHT*0.5, 2, TFT_ORANGE);
};

#endif
