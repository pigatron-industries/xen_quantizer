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
}

template<class G>
void NoteVisualiser<G>::renderTuning() {
    this->graphicsContext->fillRectangle(this->getLeft(), this->getTop(), this->getWidth(), this->getHeight(), TFT_BLACK);
    if(tuning != nullptr) {
        uint16_t noteLeft = this->getLeft();
        if(scale != nullptr) {
            noteLeft += noteWidth*scale->getOffset();
        }
        for(int i = 0; i < tuning->size(); i++) {
            renderNote(i, noteLeft);
            noteLeft += noteWidth;
            noteLeft %= tuningWidth;
        }
    }
}

template<class G>
void NoteVisualiser<G>::renderNote(int note, uint16_t noteLeft) {
    uint16_t colour = TFT_NAVY;
    if(scale != nullptr && scale->containsNote(note)) {
        colour = TFT_MAROON;
    }
    this->graphicsContext->fillRectangle(noteLeft, this->getTop(), noteWidth-1, this->getHeight(), colour);
}

template<class G>
void NoteVisualiser<G>::setTuning(Tuning* tuning) { 
    this->tuning = tuning; 
    noteWidth = this->getWidth() / tuning->size();
    tuningWidth = noteWidth * tuning->size();
    this->renderTuning();
}

template<class G>
void NoteVisualiser<G>::setScale(Scale* scale) { 
    this->scale = scale;
    setTuning(scale->getTuning());
}
