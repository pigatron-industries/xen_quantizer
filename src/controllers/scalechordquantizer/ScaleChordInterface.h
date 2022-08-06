#ifndef ScaleChordInterface_h
#define ScaleChordInterface_h

#include "Hardware.h"
#include "lib/graphics/containers/VerticalContainer.h"
#include "lib/graphics/components/FieldComponent.h"

class ScaleChordInterface {
    public:
        ScaleChordInterface() {}
        void init();
        void render();

        void setTuning(const char* tuningName);
        void setScale(const char* scaleName);
        void setChord(const char* chordName);

    private:
        VerticalContainer<TFTDisplay, 4> page;
        TextComponent<TFTDisplay> title = TextComponent<TFTDisplay>(TFTDisplay::WIDTH, "CHORD QUANTIZER", 2, TFT_ORANGE);
        FieldComponent<TFTDisplay> tuningField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 40, "TUNING:");
        FieldComponent<TFTDisplay> scaleField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 40, "SCALE:");
        FieldComponent<TFTDisplay> chordField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 40, "CHORD:");
};

#endif
