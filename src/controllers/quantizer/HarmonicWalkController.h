#ifndef HarmonicWalkController_h
#define HarmonicWalkController_h

#include "Controller.h"
#include "lib/quantizer/data/Tuning12EDO.h"
#include "lib/quantizer/ScaleFactory.h"
#include "lib/quantizer/filesystem/TuningsManager.h"
#include "lib/quantizer/QuantizerDifferential.h"


using namespace eurorack;

class HarmonicWalkController : public Controller {
    public:

        HarmonicWalkController() : Controller() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:

        IntegerInput<AnalogInputPinT> quantizedScaleOffsetPot = IntegerInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, 0, 11);
        LinearInput<AnalogInputPinT> linearScaleOffsetPot = LinearInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, 0, 1);
        IntegerInput<AnalogInputPinT> interval = IntegerInput<AnalogInputPinT>(Hardware::hw.channel2PotPin, -5, 5, 0, 7);
        LinearInput<AnalogInputPinT> channel3Pot = LinearInput<AnalogInputPinT>(Hardware::hw.channel3PotPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> channel4Pot = LinearInput<AnalogInputPinT>(Hardware::hw.channel4PotPin, -5, 5, -5, 5);

        GateInput<MCP23S17Device> clockInputs[4] = {
            GateInput<MCP23S17Device>(*Hardware::hw.clockInputPins[0], false),
            GateInput<MCP23S17Device>(*Hardware::hw.clockInputPins[1], false),
            GateInput<MCP23S17Device>(*Hardware::hw.clockInputPins[2], false),
            GateInput<MCP23S17Device>(*Hardware::hw.clockInputPins[3], false)
        };

        StaticTuningData* tuningData = &Tuning12EDO::getData();

        Scale* scale = &tuningData->scales[0];

        QuantizerDifferential quantizer = QuantizerDifferential(*tuningData->tuning);

        float outputVoltage = 0;
        
        void clock();
};

#endif
