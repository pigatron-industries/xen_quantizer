#ifndef SequenceVisualiser_h
#define SequenceVisualiser_h

#include <inttypes.h>
#include <eurorack_graphics.h>
#include "lib/quantizer/model/Scale.h"


template<class G>
class SequenceVisualiser : public Component<G> {

public:
    SequenceVisualiser(uint16_t width, uint16_t height);
    virtual void render();

    void setTuning(Tuning* tuning);
    void setScale(Scale* scale);
    void setChord(Chord* chord);

protected:
    Tuning* tuning = nullptr;
    Scale* scale = nullptr;
    Chord* chord = nullptr;
    uint16_t colour;

    uint16_t noteWidth;
    uint16_t tuningWidth;

    void renderTuning();
    void renderNote(int note, uint16_t noteLeft);
};

// #include "SequenceVisualiserImpl.h"
#endif