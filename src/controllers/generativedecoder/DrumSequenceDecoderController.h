#ifndef DrumSequenceDecoderController_h
#define DrumSequenceDecoderController_h

#include "SequenceDecoderController.h"


class DrumSequenceDecoderController : public SequenceDecoderController {
    public:
        DrumSequenceDecoderController() : SequenceDecoderController("/perc/", "DRUM") {}
        
    protected:
        virtual void decodeOutput(OutputNote* notes);
};

#endif
