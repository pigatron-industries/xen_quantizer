#ifndef CalibrationController_h
#define CalibrationController_h

#include "Controller.h"
#include "CalibrationInterface.h"

class CalibrationController : public ParameterizedController<3> {
    public:

        enum Parameter {
            OUTPUTNUM = 0,
            VOLTAGE,
            OFFSET
        };

        CalibrationController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual int cycleParameter(int amount);
        virtual void cycleValue(int amount);
        virtual void selectValue();
        virtual void update();
        virtual void process();

    private:
        IntegerInput<AnalogInputPinT> octaveInput = IntegerInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, -4, 4);

        uint8_t currentOutput = 0;
        int8_t currentVoltage = 0;
        AnalogPinCalibration calibration;
        CalibrationInterface interface;

        void setOutput(uint8_t output);
        void setOffset(int8_t amount);

        void startCalibrate();
        void saveCalibration();
        void updateOutput();
};

#endif
