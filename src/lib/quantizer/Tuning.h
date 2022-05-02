#ifndef Tuning_h
#define Tuning_h

#include <eurorack.h>

#define TUNING_MAX_NOTES 24
#define CHORD_MAX_NOTES 4

class Note {
    public:
        Note() {}
        Note(int repeat, int note, float voltage, int offset = 0) 
            { this->repeat = repeat; this->note = note; this->voltage = voltage; this->offset = offset; }
        int repeat = 0;
        int note = 0;
        int offset = 0;
        float voltage = 0;
};

class Interval {
    public:
        Interval() {}
        Interval(float voltage) { this->voltage = voltage; }
        float voltage = 0;
};

typedef Array<int, TUNING_MAX_NOTES> ScaleDef;
typedef Array<int, CHORD_MAX_NOTES> ChordDef;
typedef Array<Note, TUNING_MAX_NOTES> Chord;

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
        Array<Interval, TUNING_MAX_NOTES> intervals; 
        float repeatInterval;
        float repeatIntervalRecip;

        float getNoteVoltage(int repeat, int note, int offset = 0);
        float getRepeatVoltage(int repeat) { return repeat * this->repeatInterval; }
        float getIntervalVoltage(int note) { return intervals[note].voltage; }
};

#endif