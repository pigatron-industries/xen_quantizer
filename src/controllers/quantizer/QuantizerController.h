#ifndef QuantizerController_h
#define QuantizerController_h

#include "Controller.h"
#include "lib/quantizer/ScaleQuantizer.h"
#include "lib/quantizer/ScaleRepository.h"


using namespace eurorack;

class QuantizerController : public Controller {
    public:

        QuantizerController() : Controller() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:

        IntegerInput<AnalogInputPinT> scaleOffsetPot = IntegerInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, 0, 11);
        LinearInput<AnalogInputPinT> channel2Pot = LinearInput<AnalogInputPinT>(Hardware::hw.channel2PotPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> channel3Pot = LinearInput<AnalogInputPinT>(Hardware::hw.channel3PotPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> channel4Pot = LinearInput<AnalogInputPinT>(Hardware::hw.channel4PotPin, -5, 5, -5, 5);

        GateInput<MCP23S17Device> clockInputs[4] = {
            GateInput<MCP23S17Device>(*Hardware::hw.clockInputPins[0], false),
            GateInput<MCP23S17Device>(*Hardware::hw.clockInputPins[1], false),
            GateInput<MCP23S17Device>(*Hardware::hw.clockInputPins[2], false),
            GateInput<MCP23S17Device>(*Hardware::hw.clockInputPins[3], false),
        };

        int scaleMode = 0;

        // Tuning tuning = Tuning(12);

        Tuning tuning = Tuning({
            Interval(0, 0), 
            Interval(100/1200.0),
            Interval(200/1200.0),
            Interval(300/1200.0),
            Interval(400/1200.0),
            Interval(500/1200.0),
            Interval(600/1200.0),
            Interval(700/1200.0),
            Interval(800/1200.0),
            Interval(900/1200.0),
            Interval(1000/1200.0),
            Interval(1100/1200.0)}, 
            1.0);

        ScaleRepository scaleRepository = ScaleRepository();

        ChordDef chordDefs[1] = {
            ChordDef({0, 2, 4, 6})
        };

        Scale scales[1] = {
            Scale(tuning, {0, 2, 4, 5, 7, 9, 11}, chordDefs[0])
        };

        ScaleQuantizer scaleQuantizer = ScaleQuantizer(tuning, scales[0]);
        
        void chordClock();
        void noteClock();
};

#endif
