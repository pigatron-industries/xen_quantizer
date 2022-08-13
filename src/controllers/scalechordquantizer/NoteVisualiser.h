#ifndef NoteVisualiser_h
#define NoteVisualiser_h

#include <inttypes.h>
#include "lib/graphics/Component.h"
#include "lib/quantizer/model/Scale.h"


template<class G>
class NoteVisualiser : public Component<G> {

public:
    NoteVisualiser(uint16_t width, uint16_t height);
    // virtual void layout();
    virtual void render();

    void setTuning(Tuning* tuning);
    void setScale(Scale* scale);

protected:
    Tuning* tuning = nullptr;
    Scale* scale = nullptr;
    uint16_t colour;

    uint16_t noteWidth;
    uint16_t tuningWidth;

    void renderTuning();
    void renderNote(int note, uint16_t noteLeft);
};

#include "NoteVisualiserImpl.h"
#endif