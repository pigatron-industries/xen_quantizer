#ifndef Tuning_h
#define Tuning_h

#include <eurorack.h>
#include "Note.h"

#define TUNING_MAX_NOTES 24

// typedef Array<Note, CHORD_MAX_NOTES> Chord;

class Tuning {
    public:

        Tuning() {}
        Tuning(std::initializer_list<Interval> notes, float cycleInterval) : 
            intervals(notes) { 
            setCycleInterval(cycleInterval); 
        }

        Tuning(int notes) {
            float interval = 1.0 / notes;
            for(int i = 0; i < notes; i++) {
                intervals.add(Interval(interval*i));
            }
            setCycleInterval(1);
        }

        int size() { return intervals.size(); }
        Note createNote(int cycle, int note, float offset = 0);

        int findCycle(float voltage, float offset = 0);

    private:
        Array<Interval, TUNING_MAX_NOTES> intervals;
        float cycleInterval;
        float cycleIntervalRecip;

        void setCycleInterval(float cycleInterval) { this->cycleInterval = cycleInterval; cycleIntervalRecip = 1.0/cycleInterval; }
        float getNoteVoltage(int cycle, int note, float offset = 0);
        float getCycleVoltage(int cycle) { return cycle * this->cycleInterval; }
        float getIntervalVoltage(int note) { return intervals[note].voltage; }
};

#endif