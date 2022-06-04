#ifndef QuantizerController_h
#define QuantizerController_h

#include "Controller.h"
#include "lib/quantizer/ScaleFactory.h"
#include "lib/quantizer/ScaleRepository.h"
#include "lib/quantizer/QuantizerScale.h"
#include "lib/quantizer/QuantizerChord.h"


using namespace eurorack;

class QuantizerController : public Controller {
    public:

        QuantizerController() : Controller() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:

        IntegerInput<AnalogInputPinT> quantizedScaleOffsetPot = IntegerInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, 0, 11);
        LinearInput<AnalogInputPinT> linearScaleOffsetPot = LinearInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, 0, 1);
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
            Interval(1/12.0, 7),
            Interval(2/12.0, 6),
            Interval(3/12.0, 5),
            Interval(4/12.0, 3),
            Interval(5/12.0, 2),
            Interval(6/12.0, 5),
            Interval(7/12.0, 1),
            Interval(8/12.0, 5),
            Interval(9/12.0, 4),
            Interval(10/12.0, 5),
            Interval(11/12.0, 7)}, 
            1.0);

        ChordDef chordDefs[1] = {
            ChordDef({0, 2, 4, 6})
        };

        Scale harmonicScales[8] = {
            ScaleFactory::createHarmonicScale(tuning, 0),
            ScaleFactory::createHarmonicScale(tuning, 1),
            ScaleFactory::createHarmonicScale(tuning, 2),
            ScaleFactory::createHarmonicScale(tuning, 3),
            ScaleFactory::createHarmonicScale(tuning, 4),
            ScaleFactory::createHarmonicScale(tuning, 5),
            ScaleFactory::createHarmonicScale(tuning, 6),
            ScaleFactory::createHarmonicScale(tuning, 7)
        };

        Scale scales[2] = {
            Scale(tuning, {0, 2, 4, 5, 7, 9, 11}, chordDefs[0]), // Major
            Scale(tuning, {0, 1, 4, 5, 7, 8, 11}, chordDefs[0])  // Double harmonic
        };

        Chord chord;

        QuantizerScale scaleQuantizer = QuantizerScale(scales[0]);
        QuantizerChord chordQuantizer = QuantizerChord(scales[0], chord);
        
        void chordClock();
        void noteClock();
};

#endif
