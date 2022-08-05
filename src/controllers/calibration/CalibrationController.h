#ifndef TuningController_h
#define TuningController_h

#include "Controller.h"
#include "lib/graphics/containers/VerticalContainer.h"
#include "lib/graphics/components/FieldComponent.h"

class CalibrationController : public ParameterizedController<8> {
    public:
        CalibrationController() : ParameterizedController<8>() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual int cycleMode(int amount);
        virtual void cycleValue(int amount);
        virtual void update();
        virtual void process();

    private:
        IntegerInput<AnalogInputPinT> octaveInput = IntegerInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, -4, 4);

        int octave = 0;
        int currentVoltage = 0;
        AnalogPinCalibration calibration;

        VerticalContainer<TFTDisplay, 4> displayPage;
        TextComponent<TFTDisplay> title = TextComponent<TFTDisplay>(TFTDisplay::WIDTH, "CALIBRRATION");
        FieldComponent<TFTDisplay> outputField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 80, "OUTPUT:");
        FieldComponent<TFTDisplay> voltageField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 80, "VOLTAGE:");
        FieldComponent<TFTDisplay> offsetField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 80, "OFFSET:");

        void startCalibrate();
        void saveCalibration();
        void updateOutput();
};

#endif
