#ifndef TuningController_h
#define TuningController_h

#include "Controller.h"
#include "lib/graphics/containers/VerticalContainer.h"
#include "lib/graphics/components/TextComponent.h"

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

        VerticalContainer<TFTDisplay, 2> displayPage;
        TextComponent<TFTDisplay> text1;
        TextComponent<TFTDisplay> text2;
        TextComponent<TFTDisplay> text3;
        TextComponent<TFTDisplay> text4;

        void startCalibrate();
        void saveCalibration();
        void updateOutput();
};

#endif
