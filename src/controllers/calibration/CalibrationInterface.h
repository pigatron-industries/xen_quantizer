#ifndef CalibrationInterface_h
#define CalibrationInterface_h

#include "Hardware.h"
#include "lib/graphics/containers/VerticalContainer.h"
#include "lib/graphics/components/FieldComponent.h"

class CalibrationInterface {
    public:
        CalibrationInterface() {}
        void init();
        void render();

        void setOutput(int output);
        void setVoltage(int voltage);
        void setOffset(int offset);

    private:
        VerticalContainer<TFTDisplay, 4> page;
        TextComponent<TFTDisplay> title = TextComponent<TFTDisplay>(TFTDisplay::WIDTH, "CALIBRRATION", 2, TFT_ORANGE);
        FieldComponent<TFTDisplay> outputField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 80, "OUTPUT:");
        FieldComponent<TFTDisplay> voltageField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 80, "VOLTAGE:");
        FieldComponent<TFTDisplay> offsetField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 80, "OFFSET:");
};

#endif
