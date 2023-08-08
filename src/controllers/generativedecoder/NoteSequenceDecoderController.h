#ifndef NoteSequenceDecoderController_h
#define NoteSequenceDecoderController_h

#include "SequenceDecoderController.h"


class NoteSequenceDecoderController : public SequenceDecoderController {
    public:
        NoteSequenceDecoderController() : SequenceDecoderController("/note/", "NOTE") {}

        virtual void process();
        
    protected:
        virtual void decodeOutput(OutputNote* notes);

    private:
        AnalogTriggerOutput<DAC8164Device> triggerOutputs[4] = {
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[4]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[5]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[6]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[7])
        };
};

#endif
