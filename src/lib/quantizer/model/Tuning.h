#ifndef Tuning_h
#define Tuning_h

#include <eurorack.h>
#include "Note.h"

#define TUNING_MAX_NOTES 100

class Tuning {
    public:

        Tuning(const char* name = "") { strncpy(this->name, name, 16); }
        Tuning(std::initializer_list<Interval> notes, float cycleInterval, const char* name = "") : 
            intervals(notes) { 
            setCycleInterval(cycleInterval); 
            strncpy(this->name, name, 16);
        }

        Tuning(int notes, float cycle, const char* name = "") {
            for(int i = 0; i < notes; i++) {
                intervals.add(Interval(cycle*i/notes));
            }
            setCycleInterval(cycle);
            strncpy(this->name, name, 16);
        }

        int size() { return intervals.size(); }
        Interval& getInterval(int i) { return intervals[i]; }
        char* getName() { return name; }

        Note createNote(int cycle, int note, float offset = 0);
        Note getFirstNote(int cycle, float offset = 0);
        Note getLastNote(int cycle, float offset = 0);

        int findCycle(float voltage, float offset = 0);

    private:
        Array<Interval, TUNING_MAX_NOTES> intervals;
        float cycleInterval;
        float cycleIntervalRecip;
        char name[16] = {0};

        void setCycleInterval(float cycleInterval) { this->cycleInterval = cycleInterval; cycleIntervalRecip = 1.0/cycleInterval; }
        float getNoteVoltage(int cycle, int note, float offset = 0);
        float getCycleVoltage(int cycle) { return cycle * this->cycleInterval; }
        float getIntervalVoltage(int note) { return intervals[note].voltage; }
};

#endif