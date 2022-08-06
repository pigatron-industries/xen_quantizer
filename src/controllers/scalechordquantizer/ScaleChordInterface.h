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


    private:
        VerticalContainer<TFTDisplay, 4> page;
        TextComponent<TFTDisplay> title = TextComponent<TFTDisplay>(TFTDisplay::WIDTH, "CHORD QUANTIZER", 2, TFT_ORANGE);
        // FieldComponent<TFTDisplay> outputField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 80, "OUTPUT:");
        // FieldComponent<TFTDisplay> voltageField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 80, "VOLTAGE:");
        // FieldComponent<TFTDisplay> offsetField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 80, "OFFSET:");
};

#endif
