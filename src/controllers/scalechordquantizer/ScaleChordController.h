#ifndef ScaleChordController_h
#define ScaleChordController_h

#include "Controller.h"
#include "controllers/TuningSelection.h"
#include "lib/quantizer/ScaleFactory.h"
#include "lib/quantizer/QuantizerScale.h"
#include "lib/quantizer/QuantizerChord.h"
#include "ScaleChordInterface.h"


using namespace eurorack;

class ScaleChordController : public ParameterizedController<4>, TuningSelection {
    public:

        enum Parameter {
            TUNING,
            SCALE,
            CHORD,
            OFFSET
        };

        ScaleChordController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();

        int cycleParameter(int amount);
        virtual void cycleValue(int amount);
        void selectValue();

        virtual void update();
        virtual void process();

        

    private:

        IntegerInput<AnalogInputPinT> scaleOffsetPot = IntegerInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, -11, 11);
        IntegerInput<AnalogInputPinT> scaleOffsetCv = IntegerInput<AnalogInputPinT>(Hardware::hw.channel1CvPin, -5, 5, -11, 11);
        // LinearInput<AnalogInputPinT> linearScaleOffsetPot = LinearInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, 0, 1);
        // IntegerInput<AnalogInputPinT> chordQuality = IntegerInput<AnalogInputPinT>(Hardware::hw.channel2PotPin, -5, 5, 0, 1);
        // IntegerInput<AnalogInputPinT> chordInversion = IntegerInput<AnalogInputPinT>(Hardware::hw.channel3PotPin, -5, 5, 0, 1);
        AnalogGateInput<AnalogInputPinT> noQuantizeInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.channel4CvPin);

        GateInput<> triggerInputs[4] = {
            GateInput<>(*Hardware::hw.triggerInputPins[0]),
            GateInput<>(*Hardware::hw.triggerInputPins[1]),
            GateInput<>(*Hardware::hw.triggerInputPins[2]),
            GateInput<>(*Hardware::hw.triggerInputPins[3])
        };

        AnalogTriggerOutput<DAC8164Device> triggerOutputs[4] = {
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[0], 50000),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[1], 50000),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[2], 50000),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[3], 50000)
        };

        ScaleChordInterface interface;

        Scale* scale = &defaultTuningData->scales[0];
        ChordDef* chordDef = &scale->getChordDefs()[0];
        Chord chord;

        bool fixedOutput[4];

        QuantizerScale scaleQuantizer = QuantizerScale(*scale);
        QuantizerChord chordQuantizer = QuantizerChord(*scale, chord);

        float transpose;
        
        void setTuning(int index);
        void setScale(int index);
        void setChord(int index);
        void updateOffset();
        void updateChord();
        void updateOutput(int index);
};

#endif
