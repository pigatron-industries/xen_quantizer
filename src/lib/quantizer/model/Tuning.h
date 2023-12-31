#ifndef Tuning_h
#define Tuning_h

#include <eurorack.h>
#include "Note.h"

#define TUNING_MAX_NOTES 100

/**
 * Tuning
 * A Tuning is made up of a set of intervals. There are no fixed frequency notes in a tuning.
 */
class Tuning {
    public:

        Tuning(const char* name = "") { strncpy(this->name, name, 16); }

        /**
         * Create a tuning with the given intervals.
         * @param notes A list of the intervals in the tuning.
         * @param cycleInterval The voltage difference between two cycles or 'octave', standard octave is 1.
         */
        Tuning(std::initializer_list<Interval> notes, float cycleInterval, const char* name = "") : 
            intervals(notes) { 
            setCycleInterval(cycleInterval); 
            strncpy(this->name, name, 16);
        }

        /**
         * Create an equally divided tuning with the given number of notes and cycle interval.
         * @param notes The number of notes in the tuning.
         * @param cycle The voltage difference between two cycles or 'octave', standard octave is 1.
         */
        Tuning(int notes, float cycle, const char* name = "") {
            for(int i = 0; i < notes; i++) {
                intervals.add(Interval((cycle*i)/notes));
            }
            setCycleInterval(cycle);
            strncpy(this->name, name, 16);
        }

        /**
         * Number of intervals in tuning.
         */
        int size() { return intervals.size(); }

        /**
         * Get the interval at the given index.
         */
        Interval& getInterval(int i) { return intervals[i]; }
        float getCycleInterval() { return cycleInterval; }

        float getIntervalVoltage(int i) {
            i = i%intervals.size();
            return intervals[i].voltage;
        }

        char* getName() { return name; }

        /**
         * Create a note from the tuning at the given cycle and note.
         * @param cycle The cycle or 'octave' number of the note.
         * @param note The number of intervals above the cycle number.
         * @param offset The voltage offset of the whole tuning.
         */
        Note createNote(int cycle, int note, float offset = 0);

        /**
         * Get the first note in the tuning at the given cycle.
         * @param cycle The cycle or 'octave' number of the note.
         * @param offset The voltage offset of the whole tuning.
         */
        Note getFirstNote(int cycle, float offset = 0);

        /**
         * Get the last note in the tuning at the given cycle.
         * @param cycle The cycle or 'octave' number of the note.
         * @param offset The voltage offset of the whole tuning.
         */
        Note getLastNote(int cycle, float offset = 0);

        /**
         * Find the cycle number that the given voltage falls into.
         * @param voltage The voltage to find the cycle for.
         * @param offset The voltage offset of the whole tuning.
         */
        int findCycle(float voltage, float offset = 0);

    private:
        Array<Interval, TUNING_MAX_NOTES> intervals;
        float cycleInterval;
        float cycleIntervalRecip;
        char name[17] = {0};

        void setCycleInterval(float cycleInterval) { this->cycleInterval = cycleInterval; cycleIntervalRecip = 1.0/cycleInterval; }
        float getCycleVoltage(int cycle) { return cycle * this->cycleInterval; }
        float getNoteVoltage(int cycle, int note, float offset = 0);
};

#endif