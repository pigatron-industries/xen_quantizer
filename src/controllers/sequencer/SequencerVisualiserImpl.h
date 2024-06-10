#include "SequencerVisualiser.h"

template<class G>
SequencerVisualiser<G>::SequencerVisualiser(uint16_t width, uint16_t height) {
    this->setWidth(width);
    this->setHeight(height);
}

template<class G>
void SequencerVisualiser<G>::setSequencer(Sequencer* sequencer) { 
    this->sequencer = sequencer;
    tickWidth = this->getWidth() / sequencer->getNumSteps();
    sequenceWidth = tickWidth * sequencer->getNumSteps();
    trackHeight = this-> getHeight() / sequencer->getNumTracks();
    sequenceHeight = trackHeight * sequencer->getNumTracks();
    render();
}

template<class G>
void SequencerVisualiser<G>::setCurrentTick(int16_t tick) {
    if(this->graphicsContext == nullptr) {
        return;
    }

    // clear current tick
    uint16_t tickLeft = tickWidth * currentTick;
    this->graphicsContext->fillRectangle(tickLeft, this->getTop(), tickWidth-1, this->getHeight(), TFT_BLACK);
    renderTick(currentTick, tickLeft);

    // render new tick
    if (tick >= 0) {
        currentTick = tick;
        tickLeft = tickWidth * currentTick;
        this->graphicsContext->fillRectangle(tickLeft, this->getTop(), tickWidth-1, this->getHeight(), TFT_MAROON);
        renderTick(currentTick, tickLeft);
    }
}

template<class G>
void SequencerVisualiser<G>::render() {
    this->graphicsContext->fillRectangle(this->getLeft(), this->getTop(), this->getWidth(), this->getHeight(), TFT_BLACK);
    renderSequence();
}

template<class G>
void SequencerVisualiser<G>::renderSequence() {
    if(sequencer != nullptr) {
        bottom = this->getTop() + sequenceHeight;
        uint16_t tickLeft = this->getLeft();
        for(int tick = 0; tick < sequencer->getNumSteps(); tick++) {
            renderTick(tick, tickLeft);
            tickLeft += tickWidth;
        }
    }
}

template<class G>
void SequencerVisualiser<G>::renderTick(int tick, uint16_t tickLeft) {
    for (int track = 0; track < sequencer->getNumTracks(); track++) {
        SequenceStep& step = sequencer->getStep(track, tick);
        if(step.trigger) {
            this->graphicsContext->fillRectangle(tickLeft, bottom - trackHeight - (track * trackHeight), tickWidth-1, trackHeight, TFT_WHITE);
        }
    }
}
