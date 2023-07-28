#ifndef NoteSequenceDecoderController_h
#define NoteSequenceDecoderController_h

#include "SequenceDecoderController.h"


class NoteSequenceDecoderController : public SequenceDecoderController {
    public:
        NoteSequenceDecoderController() : SequenceDecoderController("/note/", "NOTE") {}
        
    protected:
        virtual void decodeOutput(OutputNote* notes);
};

#endif
