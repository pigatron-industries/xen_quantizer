#ifndef QuantizerController_h
#define QuantizerController_h

#include "Controller.h"

using namespace eurorack;

class QuantizerController : public Controller {
    public:

        QuantizerController() : Controller() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:

        LinearInput<AnalogInputPinT> channel1Pot = LinearInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> channel2Pot = LinearInput<AnalogInputPinT>(Hardware::hw.channel2PotPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> channel3Pot = LinearInput<AnalogInputPinT>(Hardware::hw.channel3PotPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> channel4Pot = LinearInput<AnalogInputPinT>(Hardware::hw.channel4PotPin, -5, 5, -5, 5);

};

#endif
