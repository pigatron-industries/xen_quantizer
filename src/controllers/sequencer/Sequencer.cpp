#include "Sequencer.h"


Sequencer::Sequencer() {
    SequenceStep step;
    for (int i = 0; i < NUM_TRACKS; i++) {
        tracks[i].init(step, MAX_STEPS);
    }
}

void Sequencer::clearTrack(int track) {
    for (int i = 0; i < numSteps; i++) {
        tracks[track].get(i).trigger = false;
        tracks[track].get(i).voltage = 0;
    }
}

void Sequencer::tick() {
    currentStep = (currentStep + 1) % numSteps;
}

void Sequencer::reset() {
    currentStep = -1;
}
