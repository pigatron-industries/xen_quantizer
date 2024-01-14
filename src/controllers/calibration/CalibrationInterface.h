#ifndef CalibrationInterface_h
#define CalibrationInterface_h

#include <eurorack_graphics.h>
#include "Hardware.h"
#include "OutputVisualiser.h"

class CalibrationInterface {
    public:
        CalibrationInterface() {}
        void init();
        void render();

        void setOutput(int output);
        void setVoltage(int voltage);
        void setValue(int value);

        void setOffset(int offset);
        void setScale(int scale);

        void focusOutput();
        void focusVoltage();
        void focusValue();

    private:
        VerticalContainer<TFTDisplay, 7> page;

        FocusManager<TFTDisplay> focusManager;

        TextComponent<TFTDisplay> title = TextComponent<TFTDisplay>(TFTDisplay::WIDTH, "CALIBRRATION", 2, TFT_ORANGE);
        FieldComponent<TFTDisplay> outputField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "OUTPUT:");
        FieldComponent<TFTDisplay> voltageField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "VOLTAGE:");
        FieldComponent<TFTDisplay> valueField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "VALUE:");

        FieldComponent<TFTDisplay> offsetField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "OFFSET:");
        FieldComponent<TFTDisplay> scaleField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "SCALE:");

        OutputVisualiser<TFTDisplay> outputVisualiser = OutputVisualiser<TFTDisplay>(TFTDisplay::WIDTH, 10);
};

#endif
