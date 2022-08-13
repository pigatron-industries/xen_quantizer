#include "NoteVisualiser.h"

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
    renderTuning();
    renderScale();
}

template<class G>
void NoteVisualiser<G>::renderTuning() {
    if(tuning != nullptr) {
        this->graphicsContext->fillRectangle(this->getLeft(), this->getTop(), this->getWidth(), this->getHeight(), TFT_BLACK);
        uint16_t noteLeft = this->getLeft();
        for(int i = 0; i < tuning->size(); i++) {
            this->graphicsContext->fillRectangle(noteLeft, this->getTop(), noteWidth-1, this->getHeight(), TFT_NAVY);
            noteLeft += noteWidth;
        }
    }
}

template<class G>
void NoteVisualiser<G>::renderScale() {
    if(scale != nullptr) {
        for(int i = 0; i < scale->size(); i++) {
            uint8_t note = scale->getNote(i);
            uint16_t noteLeft = this->getLeft() + noteWidth*note;
            this->graphicsContext->fillRectangle(noteLeft, this->getTop(), noteWidth-1, this->getHeight(), TFT_MAROON);
        }
    }
}

template<class G>
void NoteVisualiser<G>::setTuning(Tuning* tuning) { 
    this->tuning = tuning; 
    noteWidth = this->getWidth() / tuning->size();
    this->renderTuning();
}

template<class G>
void NoteVisualiser<G>::setScale(Scale* scale) { 
    this->scale = scale;
    setTuning(scale->getTuning());
    this->renderScale();
}
