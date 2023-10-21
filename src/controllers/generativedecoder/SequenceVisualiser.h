#ifndef SequenceVisualiser_h
#define SequenceVisualiser_h

#include <inttypes.h>
#include <eurorack_graphics.h>
#include "lib/neural/model/SequenceDecoderModel.h"

#define VISIBLE_NOTES 12


template<class G>
class SequenceVisualiser : public Component<G> {

public:
    SequenceVisualiser(uint16_t width, uint16_t height);
    virtual void render();

    void setNumNotes(uint8_t numNotes);
    void setSequence(OutputNotesSequence* sequence);

protected:
    OutputNotesSequence* sequence = nullptr;
    
    uint16_t numNotes = VISIBLE_NOTES;

    uint16_t colours[VISIBLE_NOTES];
    uint16_t bottom;
    uint16_t tickWidth;
    uint16_t noteHeight;
    uint16_t sequenceWidth;
    uint16_t sequenceHeight;

    void renderSequence();
    void renderTick(OutputNotes& notes, uint16_t tickLeft);
};

#include "SequenceVisualiserImpl.h"
#endif