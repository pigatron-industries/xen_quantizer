#ifndef CalibrationInterface_h
#define CalibrationInterface_h

#include <eurorack_graphics.h>
#include "Hardware.h"

class CalibrationInterface {
    public:
        CalibrationInterface() {}
        void init();
        void render();

        void setOutput(int output);
        void setVoltage(int voltage);
        void setOffset(int offset);

        void focusOutput();
        void focusVoltage();
        void focusOffset();

    private:
        VerticalContainer<TFTDisplay, 4> page;

        FocusManager<TFTDisplay> focusManager;

        TextComponent<TFTDisplay> title = TextComponent<TFTDisplay>(TFTDisplay::WIDTH, "CALIBRRATION", 2, TFT_ORANGE);
        FieldComponent<TFTDisplay> outputField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "OUTPUT:");
        FieldComponent<TFTDisplay> voltageField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "VOLTAGE:");
        FieldComponent<TFTDisplay> offsetField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "OFFSET:");
};

#endif
