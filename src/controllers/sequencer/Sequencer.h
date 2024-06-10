#ifndef Sequence_h
#define Sequence_h

#include <eurorack.h>

#define MAX_STEPS 32
#define NUM_TRACKS 4


class SequenceStep {
    public:
        bool trigger = false;
        float voltage = 0;
};

typedef Array<SequenceStep, MAX_STEPS> Sequence;


class Sequencer {
    public:
        Sequencer();
        int getNumTracks() { return tracks.size(); }
        int getNumSteps() { return numSteps; }
        int getCurrentStep() { return currentStep; }
        Sequence& getTrack(int index) { return tracks[index]; }
        SequenceStep& getStep(int trackIndex, int stepIndex) { return tracks[trackIndex].get(stepIndex); }

        void setNumSteps(int numSteps) { this->numSteps = numSteps; }
        void clearTrack(int track);

        void tick();
        void reset();

    private:
        Array<Sequence, NUM_TRACKS> tracks = Array<Sequence, NUM_TRACKS>(NUM_TRACKS);
        int currentStep = -1;
        int numSteps = MAX_STEPS;
};





#endif