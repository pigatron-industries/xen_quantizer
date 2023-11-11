#ifndef NoteSequenceDecoderController_h
#define NoteSequenceDecoderController_h

#include "SequenceDecoderController.h"


class NoteSequenceDecoderController : public SequenceDecoderController {
    public:
        NoteSequenceDecoderController() : SequenceDecoderController("/note/", "NOTE") {
            interface.sequenceVisualiser.colours[0] = TFT_WHITE;
            interface.sequenceVisualiser.colours[1] = TFT_YELLOW;
            interface.sequenceVisualiser.colours[2] = TFT_MAGENTA;
            interface.sequenceVisualiser.colours[3] = TFT_MAGENTA;
            interface.sequenceVisualiser.colours[4] = TFT_MAGENTA;
            interface.sequenceVisualiser.colours[5] = TFT_MAGENTA;
            interface.sequenceVisualiser.colours[6] = TFT_MAGENTA;
            interface.sequenceVisualiser.colours[7] = TFT_MAGENTA;
            interface.sequenceVisualiser.colours[8] = TFT_GREEN;
            interface.sequenceVisualiser.colours[9] = TFT_GREEN;
            interface.sequenceVisualiser.colours[10] = TFT_BLUE;
            interface.sequenceVisualiser.colours[11] = TFT_BLUE;
            interface.sequenceVisualiser.setColourByOctave(true);
        }

        virtual void process();
        
    protected:
        virtual void decodeOutput(Array<OutputNote, MAX_NOTES_OUTPUT>& notes);

    private:
        AnalogTriggerOutput<DAC8164Device> triggerOutputs[4] = {
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[4]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[5]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[6]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[7])
        };
};

#endif
