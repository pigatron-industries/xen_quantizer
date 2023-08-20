#ifndef HarmonicWalkController_h
#define HarmonicWalkController_h

#include "Controller.h"
#include "HarmonicWalkInterface.h"
#include "lib/quantizer/data/Tuning12EDO.h"
#include "lib/quantizer/ScaleFactory.h"
#include "lib/quantizer/filesystem/TuningsManager.h"
#include "lib/quantizer/QuantizerDifferential.h"

#define NUM_TRIGGER_OUTPUTS 4

using namespace eurorack;

class HarmonicWalkController : public ParameterizedController<2> {
    public:

        enum Parameter {
            TUNING,
            INTERVAL
        };

        HarmonicWalkController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();

        int cycleParameter(int amount);
        virtual void cycleValue(int amount);

        virtual void update();
        virtual void process();

    private:

        GateInput<> triggerInputs[4] = {
            GateInput<>(*Hardware::hw.triggerInputPins[0], false),
            GateInput<>(*Hardware::hw.triggerInputPins[1], false),
            GateInput<>(*Hardware::hw.triggerInputPins[2], false),
            GateInput<>(*Hardware::hw.triggerInputPins[3], false)
        };

        AnalogTriggerOutput<DAC8164Device> triggerOutputs[NUM_TRIGGER_OUTPUTS] = {
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[5]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[6]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[7]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[8])
        };

        HarmonicWalkInterface interface;

        int interval = 1;

        StaticTuningData* defaultTuningData = &Tuning12EDO::data;
        TuningData* tuningData = nullptr;
        Tuning* tuning = defaultTuningData->tuning;

        QuantizerDifferential quantizer = QuantizerDifferential(*defaultTuningData->tuning);

        float outputVoltage = 0;
        
        void setTuning(int index);
        void setInterval(int interval);
        void clock();
};

#endif
