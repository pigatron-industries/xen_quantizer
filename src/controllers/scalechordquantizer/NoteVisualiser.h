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
};


template<class G>
NoteVisualiser<G>::NoteVisualiser(uint16_t width, uint16_t height) {
    this->setWidth(width);
    this->setHeight(height);
}

// template<class G>
// void NoteVisualiser<G>::layout() {
// }

template<class G>
void NoteVisualiser<G>::render() {
    if(tuning != nullptr) {
        uint16_t noteLeft = this->getLeft();
        for(int i = 0; i < tuning->size(); i++) {
            this->graphicsContext->fillRectangle(noteLeft, this->getTop(), noteWidth-1, this->getHeight(), TFT_NAVY);
            noteLeft += noteWidth;
        }

        if(scale != nullptr) {
            for(int i = 0; i < scale->size(); i++) {
                uint8_t note = scale->getNote(i);
                noteLeft = this->getLeft() + noteWidth*note;
                this->graphicsContext->fillRectangle(noteLeft, this->getTop(), noteWidth-1, this->getHeight(), TFT_MAROON);
            }
        }
    }
}

template<class G>
void NoteVisualiser<G>::setTuning(Tuning* tuning) { 
    this->tuning = tuning; 
    noteWidth = this->getWidth() / tuning->size();
    this->render();
}

template<class G>
void NoteVisualiser<G>::setScale(Scale* scale) { 
    this->scale = scale; 
    this->render();
}

#endif
