#ifndef Scale_h
#define Scale_h

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

class Scale {
    public:
        static constexpr int MAX_NOTES = 24;

        Scale() {}
        Scale(int notes) {
            float interval = 1.0 / notes;
            for(int i = 1; i <= notes; i++) {
                intervals.add(Interval(interval*i));
            }
            octaveInterval = 1.0;
            octaveIntervalRecip = 1.0/octaveInterval;
        }

        int getNotes() { return intervals.size(); }
        Note getNote(int octave, int note) { return Note(octave, note, getNoteValue(octave, note)); }

        float getNoteValue(int octave, int note) { return getOctaveValue(octave) + getIntervalValue(note); }
        float getOctaveValue(int octave) { return octave * this->octaveInterval; }
        float getIntervalValue(int note) { return note > 0 ? intervals[note-1].value : 0; }

        bool isEnabled(const Note& note) { return note.note > 0 ? intervals[note.note-1].enabled : true; }
        void enable(int note, bool enabled = true);
        void enable(std::initializer_list<int> notes);

        int findOctave(float value) {
            return floorf(value * octaveIntervalRecip);
        }

    private:
        Array<Interval, MAX_NOTES> intervals;
        float octaveInterval;
        float octaveIntervalRecip;

};

#endif
