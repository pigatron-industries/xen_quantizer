#ifndef Tuning_h
#define Tuning_h

#include <eurorack.h>

class Note {
    public:
        Note() {}
        Note(int octave, int note) { this->octave = octave; this->note = note; }
        Note(int octave, int note, float value) { this->octave = octave; this->note = note; this->value = value; }
        int octave = 0;
        int note = 0;
        float value = 0;
};

class Interval {
    public:
        Interval() {}
        Interval(float value) { this->value = value; }
        float value = 0;
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

        int findOctave(float value) {
            return floorf(value * repeatIntervalRecip);
        }

    private:
        Array<Interval, MAX_NOTES> intervals; 
        float repeatInterval;
        float repeatIntervalRecip;

        float getNoteValue(int octave, int note) { return getOctaveValue(octave) + getIntervalValue(note); }
        float getOctaveValue(int octave) { return octave * this->repeatInterval; }
        float getIntervalValue(int note) { return intervals[note].value; }
};

#endif
