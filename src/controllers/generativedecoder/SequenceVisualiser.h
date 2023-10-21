#ifndef SequenceVisualiser_h
#define SequenceVisualiser_h

#include <inttypes.h>
#include <eurorack_graphics.h>
#include "lib/neural/model/SequenceDecoderModel.h"


template<class G>
class SequenceVisualiser : public Component<G> {

public:
    SequenceVisualiser(uint16_t width, uint16_t height);
    virtual void render();

    void setSequence(OutputNotesSequence* sequence);

protected:
    OutputNotesSequence* sequence = nullptr;
    Scale* scale = nullptr;
    Chord* chord = nullptr;

    uint16_t colour;
    uint16_t noteWidth;
    uint16_t sequenceWidth;

    void renderSequence();
    void renderTick(OutputNotes& notes, uint16_t tickLeft);
};

// #include "SequenceVisualiserImpl.h"
#endif