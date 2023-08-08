#ifndef DrumSequenceDecoderController_h
#define DrumSequenceDecoderController_h

#include "SequenceDecoderController.h"

#define NUM_TRIGGER_OUTPUTS 6

class DrumSequenceDecoderController : public SequenceDecoderController {
    public:
        DrumSequenceDecoderController() : SequenceDecoderController("/perc/", "DRUM") {}

        virtual void process();
        
    protected:
        virtual void decodeOutput(Array<OutputNote, MAX_NOTES_OUTPUT>& notes);

    private:
        // 0 1 2 3
        // 4 5 6 7
        AnalogTriggerOutput<DAC8164Device> triggerOutputs[NUM_TRIGGER_OUTPUTS] = {
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[0]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[4]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[1]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[2]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[3]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[5])
        };

        int8_t getOutput(uint8_t instrument);
        int8_t getAccentOutput(int8_t output);
        float getAccent(int8_t output, uint8_t instrument);
};

#endif
