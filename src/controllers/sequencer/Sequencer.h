#ifndef Sequence_h
#define Sequence_h

#include <eurorack.h>

#define MAX_STEPS 32
#define NUM_TRACKS 4
#define NUM_PATTERNS 64


class SequenceStep {
    public:
        bool trigger = false;
        float voltage = 0;
};

typedef Array<SequenceStep, MAX_STEPS> TrackPattern;
typedef Array<TrackPattern, NUM_TRACKS> Pattern;


class Sequencer {
    public:
        Sequencer();
        int getNumTracks() { return numTracks; }
        int getNumSteps() { return numSteps; }
        int getCurrentStep() { return currentStep; }
        TrackPattern& getTrack(int index) { return patterns[currentPattern][index]; }
        SequenceStep& getStep(int trackIndex, int stepIndex) { return patterns[currentPattern][trackIndex].get(stepIndex); }

        void setCurrentPattern(int pattern) { currentPattern = pattern; }
        int addPattern();
        void setNumSteps(int numSteps) { this->numSteps = numSteps; }
        void clearTrack(int track);

        void tick();
        void reset();

    private:
        Array<Pattern, NUM_PATTERNS> patterns = Array<Pattern, NUM_PATTERNS>();

        int currentStep = -1;
        int currentPattern = 0;
        int numTracks = NUM_TRACKS;
        int numSteps = MAX_STEPS;
};





#endif