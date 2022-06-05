#ifndef ScaleChordController_h
#define ScaleChordController_h

#include "Controller.h"
#include "lib/quantizer/data/Tuning12EDO.h"
#include "lib/quantizer/ScaleFactory.h"
#include "lib/quantizer/TuningRepository.h"
#include "lib/quantizer/QuantizerScale.h"
#include "lib/quantizer/QuantizerChord.h"


using namespace eurorack;

class ScaleChordController : public Controller {
    public:

        ScaleChordController() : Controller() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:

        IntegerInput<AnalogInputPinT> quantizedScaleOffsetPot = IntegerInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, 0, 11);
        LinearInput<AnalogInputPinT> linearScaleOffsetPot = LinearInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, 0, 1);
        IntegerInput<AnalogInputPinT> dissonance = IntegerInput<AnalogInputPinT>(Hardware::hw.channel2PotPin, -5, 5, 0, 7);
        LinearInput<AnalogInputPinT> channel3Pot = LinearInput<AnalogInputPinT>(Hardware::hw.channel3PotPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> channel4Pot = LinearInput<AnalogInputPinT>(Hardware::hw.channel4PotPin, -5, 5, -5, 5);

        GateInput<MCP23S17Device> clockInputs[4] = {
            GateInput<MCP23S17Device>(*Hardware::hw.clockInputPins[0], false),
            GateInput<MCP23S17Device>(*Hardware::hw.clockInputPins[1], false),
            GateInput<MCP23S17Device>(*Hardware::hw.clockInputPins[2], false),
            GateInput<MCP23S17Device>(*Hardware::hw.clockInputPins[3], false),
        };

        TuningData* tuningData = &Tuning12EDO::data;
        Scale* scale = &tuningData->scales[0];
        ChordDef* chordDef = &tuningData->chordDefs[0];

        Chord chord;

        QuantizerScale scaleQuantizer = QuantizerScale(*scale);
        QuantizerChord chordQuantizer = QuantizerChord(*scale, chord);
        
        void chordClock();
        void noteClock();
};

#endif
