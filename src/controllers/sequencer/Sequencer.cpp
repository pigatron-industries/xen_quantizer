#include "Sequencer.h"


Sequencer::Sequencer() {
    SequenceStep step;
    addPattern();
}

void Sequencer::clearTrack(int track) {
    for (int i = 0; i < numSteps; i++) {
        patterns[currentPattern][track].get(i).gate = false;
        patterns[currentPattern][track].get(i).voltage = 0;
    }
}

int Sequencer::addPattern() {
    SequenceStep step;
    TrackPattern track = TrackPattern(step, MAX_STEPS);
    Pattern pattern = Pattern(track, NUM_TRACKS);
    return patterns.add(pattern);
}

void Sequencer::tick() {
    currentStep = (currentStep + 1) % numSteps;
}

void Sequencer::reset() {
    currentStep = -1;
}
