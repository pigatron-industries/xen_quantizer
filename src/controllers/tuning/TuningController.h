#ifndef TuningController_h
#define TuningController_h

#include "Controller.h"

class TuningController : public Controller {
    public:
        TuningController() : Controller() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        IntegerInput<AnalogInputPinT> octavePot = IntegerInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, -5, 5);

        int octave = 0;
};

#endif
