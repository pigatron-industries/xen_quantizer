#include "SequenceVisualiser.h"

template<class G>
SequenceVisualiser<G>::SequenceVisualiser(uint16_t width, uint16_t height) {
    this->setWidth(width);
    this->setHeight(height);
    setNumNotes(12);
}

template<class G>
void SequenceVisualiser<G>::setNumNotes(uint8_t numNotes) {
    noteHeight = this->getHeight() / numNotes; 
    sequenceHeight = noteHeight * numNotes;
}

template<class G>
void SequenceVisualiser<G>::setSequence(OutputNotesSequence* sequence) { 
    this->sequence = sequence; 
    tickWidth = this->getWidth() / sequence->size();
    sequenceWidth = tickWidth * sequence->size();
    colours[0] = TFT_WHITE;
    colours[1] = TFT_YELLOW;
    colours[2] = TFT_MAGENTA;
    colours[3] = TFT_MAGENTA;
    colours[4] = TFT_MAGENTA;
    colours[5] = TFT_MAGENTA;
    colours[6] = TFT_MAGENTA;
    colours[7] = TFT_MAGENTA;
    colours[8] = TFT_GREEN;
    colours[9] = TFT_GREEN;
    colours[10] = TFT_BLUE;
    colours[11] = TFT_BLUE;
    render();
}

template<class G>
void SequenceVisualiser<G>::setCurrentTick(uint8_t tick) {
    // clear current tick
    uint16_t tickLeft = tickWidth * currentTick;
    this->graphicsContext->fillRectangle(tickLeft, this->getTop(), tickWidth-1, this->getHeight(), TFT_BLACK);
    renderTick((*sequence)[currentTick], tickLeft);

    // render new tick
    currentTick = tick;
    tickLeft = tickWidth * currentTick;
    this->graphicsContext->fillRectangle(tickLeft, this->getTop(), tickWidth-1, this->getHeight(), TFT_MAROON);
    renderTick((*sequence)[currentTick], tickLeft);
}

template<class G>
void SequenceVisualiser<G>::render() {
    this->graphicsContext->fillRectangle(this->getLeft(), this->getTop(), this->getWidth(), this->getHeight(), TFT_BLACK);
    renderSequence();
}

template<class G>
void SequenceVisualiser<G>::renderSequence() {
    if(sequence != nullptr) {
        bottom = this->getTop() + sequenceHeight;
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
    // this->graphicsContext->fillRectangle(tickLeft, this->getTop(), tickWidth-1, this->getHeight(), colour);

    for (int i = 0; i < notes.size(); i++) {
        uint16_t colour = colours[notes[i].note];
        this->graphicsContext->fillRectangle(tickLeft, bottom - noteHeight - (notes[i].note * noteHeight), tickWidth-1, noteHeight, colour);
    }
}
