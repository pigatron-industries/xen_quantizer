#ifndef Tuning_h
#define Tuning_h

#include <eurorack.h>

class Note {
    public:
        Note() {}
        Note(int repeat, int note) { this->repeat = repeat; this->note = note; }
        Note(int repeat, int note, float voltage) { this->repeat = repeat; this->note = note; this->voltage = voltage; }
        int repeat = 0;
        int note = 0;
        float voltage = 0;
};

class Interval {
    public:
        Interval() {}
        Interval(float voltage) { this->voltage = voltage; }
        float voltage = 0;
        bool enabled = false;
};

class Tuning {
    public:
        static constexpr int MAX_NOTES = 24;

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
        Note getNote(int octave, int note) { return Note(octave, note, getNoteValue(octave, note)); }

        bool isEnabled(const Note& note) { return note.note > 0 ? intervals[note.note-1].enabled : true; }
        void enable(int note, bool enabled = true);
        void enable(std::initializer_list<int> notes);

        int findRepeatNumber(float voltage) {
            return floorf(voltage * repeatIntervalRecip);
        }

    private:
        Array<Interval, MAX_NOTES> intervals; 
        float repeatInterval;
        float repeatIntervalRecip;

        float getNoteVoltage(int repeat, int note) { return getOctaveValue(repeat) + getIntervalValue(note); }
        float getRepeatVoltage(int repeat) { return repeat * this->repeatInterval; }
        float getIntervalVoltaage(int note) { return intervals[note].voltage; }
};

#endif