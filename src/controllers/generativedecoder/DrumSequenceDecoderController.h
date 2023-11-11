#ifndef DrumSequenceDecoderController_h
#define DrumSequenceDecoderController_h

#include "SequenceDecoderController.h"

#define NUM_TRIGGER_OUTPUTS 5

class DrumSequenceDecoderController : public SequenceDecoderController {
    public:
        DrumSequenceDecoderController() : SequenceDecoderController("/perc/", "DRUM") {
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
            interface.sequenceVisualiser.setColourByOctave(false);
        }

        virtual void process();
        
    protected:
        virtual void decodeOutput(Array<OutputNote, MAX_NOTES_OUTPUT>& notes);

    private:
        // 0 2 3 4
        // 1 5 6 7
        AnalogTriggerOutput<DAC8164Device> triggerOutputs[NUM_TRIGGER_OUTPUTS] = {
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[0]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[4]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[1]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[2]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[3])
        };

        int8_t getOutput(uint8_t instrument);
        int8_t getAccentOutput(int8_t output);
        float getAccent(int8_t output, uint8_t instrument);
};

#endif
