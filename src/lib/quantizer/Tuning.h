#ifndef Tuning_h
#define Tuning_h

#include <eurorack.h>
#include "Note.h"
#include "ScaleRepository.h"

typedef Array<Note, CHORD_MAX_NOTES> Chord;

class Tuning {
    public:

        Tuning() {}
        Tuning(int notes) {
            float interval = 1.0 / notes;
            for(int i = 0; i <= notes; i++) {
                intervals.add(Interval(interval*i));
            }
            repeatInterval = 1.0;
            repeatIntervalRecip = 1.0/repeatInterval;
        }

        int getNotes() { return intervals.size(); }
        Note createNote(int repeat, int note, int offset = 0);
        Chord createChord(Note& root, ChordDef& chordDef);

        int findRepeatNumber(float voltage) {
            return floorf(voltage * repeatIntervalRecip);
        }

    private:
        Array<Interval, SCALE_MAX_NOTES> intervals;
        float repeatInterval;
        float repeatIntervalRecip;

        float getNoteVoltage(int repeat, int note, int offset = 0);
        float getRepeatVoltage(int repeat) { return repeat * this->repeatInterval; }
        float getIntervalVoltage(int note) { return intervals[note].voltage; }
};

#endif