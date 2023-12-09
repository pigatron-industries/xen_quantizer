#include "SequenceVisualiser.h"

template<class G>
SequenceVisualiser<G>::SequenceVisualiser(uint16_t width, uint16_t height) {
    this->setWidth(width);
    this->setHeight(height);
    setNumNotes(12);
    for (int i = 0; i < VISIBLE_NOTES; i++) {
        colours[i] = TFT_WHITE;
    }
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
    render();
}

template<class G>
void SequenceVisualiser<G>::setCurrentTick(int8_t tick) {
    // clear current tick
    uint16_t tickLeft = tickWidth * currentTick;
    this->graphicsContext->fillRectangle(tickLeft, this->getTop(), tickWidth-1, this->getHeight(), TFT_BLACK);
    renderTick((*sequence)[currentTick], tickLeft);

    // render new tick
    if (tick >= 0) {
        currentTick = tick;
        tickLeft = tickWidth * currentTick;
        this->graphicsContext->fillRectangle(tickLeft, this->getTop(), tickWidth-1, this->getHeight(), TFT_MAROON);
        renderTick((*sequence)[currentTick], tickLeft);
    }
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
    for (int i = 0; i < notes.size(); i++) {
        uint8_t pitch = notes[i].note % 12;

        uint16_t colour = 0;
        if (colourByOctave) {
            uint8_t octave = notes[i].note / 12;
            colour = colours[octave];
        } else {
            colour = colours[pitch];
        }
        
        this->graphicsContext->fillRectangle(tickLeft, bottom - noteHeight - (pitch * noteHeight), tickWidth-1, noteHeight, colour);
    }
}
