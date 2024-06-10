#ifndef SequencerVisualiser_h
#define SequencerVisualiser_h

#include <inttypes.h>
#include <eurorack_graphics.h>
#include "Sequencer.h"


template<class G>
class SequencerVisualiser : public Component<G> {

public:
    SequencerVisualiser(uint16_t width, uint16_t height);
    virtual void render();

    void setSequencer(Sequencer* sequence);
    void setCurrentTick(int16_t tick);

protected:
    Sequencer* sequencer = nullptr;
    uint16_t currentTick = 0;

    uint16_t bottom;
    uint16_t tickWidth;
    uint16_t trackHeight;
    uint16_t sequenceWidth;
    uint16_t sequenceHeight;

    void renderSequence();
    void renderTick(int tick, uint16_t tickLeft);
};

#include "SequencerVisualiserImpl.h"
#endif