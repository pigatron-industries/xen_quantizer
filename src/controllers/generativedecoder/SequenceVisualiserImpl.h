#include "SequenceVisualiser.h"

template<class G>
SequenceVisualiser<G>::SequenceVisualiser(uint16_t width, uint16_t height) {
    this->setWidth(width);
    this->setHeight(height);
}

template<class G>
void SequenceVisualiser<G>::setSequence(OutputNotesSequence* sequence) { 
    this->sequence = sequence; 
    tickWidth = this->getWidth() / sequence->size();
    sequenceWidth = tickWidth * sequence->size();
    this->render();
}

template<class G>
void SequenceVisualiser<G>::render() {
    this->graphicsContext->fillRectangle(this->getLeft(), this->getTop(), this->getWidth(), this->getHeight(), TFT_BLACK);
    renderSequence();
}

template<class G>
void SequenceVisualiser<G>::renderSequence() {
    // TODO 
    if(sequence != nullptr) {
        uint16_t tickLeft = this->getLeft();
        for(int i = 0; i < sequence->size(); i++) {
            renderTick((*sequence)[i], tickLeft);
            tickLeft += tickWidth;
        }
    }
}

template<class G>
void SequenceVisualiser<G>::renderTick(OutputNotes& notes, uint16_t tickLeft) {
    // uint16_t colour = TFT_NAVY;
    // if(scale != nullptr && scale->containsNote(note)) {
    //     colour = TFT_MAROON;
    // }
    // if(chord != nullptr) {
    //     if((*chord)[0].note == note) {
    //         colour = TFT_GREEN;
    //     } else if ((*chord)[1].note == note) {
    //         colour = TFT_RED;
    //     } else if ((*chord)[2].note == note) {
    //         colour = TFT_RED;
    //     }
    // }
    // this->graphicsContext->fillRectangle(noteLeft, this->getTop(), noteWidth-1, this->getHeight(), colour);
}
