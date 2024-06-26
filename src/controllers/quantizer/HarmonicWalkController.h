#ifndef HarmonicWalkController_h
#define HarmonicWalkController_h

#include "Controller.h"
#include "HarmonicWalkInterface.h"
#include "controllers/TuningSelection.h"
#include "lib/quantizer/data/Tuning12EDO.h"
#include "lib/quantizer/ScaleFactory.h"
#include "lib/quantizer/filesystem/TuningsManager.h"
#include "lib/quantizer/QuantizerDifferential.h"

#define NUM_TRIGGER_OUTPUTS 4

using namespace eurorack;

class HarmonicWalkController : public ParameterizedController<2>, public TuningSelection {
    public:

        enum Parameter {
            TUNING
            // INTERVAL
        };

        HarmonicWalkController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();

        int cycleParameter(int amount);
        virtual void cycleValue(int amount);
        void selectValue();

        virtual void update();
        virtual void process();

    private:

        LinearInput<AnalogInputPinT> intervalInput = LinearInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, 0, 1);
        LinearInput<AnalogInputPinT> intervalCVInput = LinearInput<AnalogInputPinT>(Hardware::hw.channel1CvPin, -5, 5, -1, 1);

        GateInput<> triggerInputs[4] = {
            GateInput<>(*Hardware::hw.triggerInputPins[0], false),
            GateInput<>(*Hardware::hw.triggerInputPins[1], false),
            GateInput<>(*Hardware::hw.triggerInputPins[2], false),
            GateInput<>(*Hardware::hw.triggerInputPins[3], false)
        };

        AnalogTriggerOutput<DAC8164Device> triggerOutputs[NUM_TRIGGER_OUTPUTS] = {
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[0]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[1]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[2]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[3])
        };

        HarmonicWalkInterface interface;

        int interval = 1;

        QuantizerDifferential quantizer = QuantizerDifferential(*defaultTuningData->tuning);

        float outputVoltage = 0;
        
        void setTuning(int index);
        void setInterval(int interval);
        void clock();
};

#endif
