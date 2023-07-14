#ifndef CalibrationController_h
#define CalibrationController_h

#include "Controller.h"
#include "CalibrationInterface.h"

class CalibrationController : public ParameterizedController<8> {
    public:
        CalibrationController() : ParameterizedController<8>() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual int cycleParameter(int amount);
        virtual void cycleValue(int amount);
        virtual void update();
        virtual void process();

    private:
        IntegerInput<AnalogInputPinT> octaveInput = IntegerInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, -4, 4);

        int currentVoltage = 0;
        AnalogPinCalibration calibration;
        CalibrationInterface interface;

        void startCalibrate();
        void saveCalibration();
        void updateOutput();
};

#endif
