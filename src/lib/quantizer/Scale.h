#ifndef ScaleDef_h
#define ScaleDef_h

#include <eurorack.h>
#include "Note.h"
#include "Tuning.h"

#define CHORD_MAX_NOTES 5
#define MAX_CHORD_DEFS 5

typedef Array<int, CHORD_MAX_NOTES> ChordDef;
typedef Array<Note, CHORD_MAX_NOTES> Chord;

class Scale {
    public:
        Scale(Tuning& tuning) { this->tuning = &tuning; }
        Scale(Tuning& tuning, std::initializer_list<int> notes) : 
            notes(notes) { this->tuning = &tuning; }
        Scale(Tuning& tuning, std::initializer_list<int> notes, std::initializer_list<int> chordDef) : 
            notes(notes),
            chordDefs({chordDef}) { this->tuning = &tuning; }
        Scale(Tuning& tuning, std::initializer_list<int> notes, ChordDef& chordDef) : 
            notes(notes),
            chordDefs({chordDef}) { this->tuning = &tuning; }

        void setOffset(float offset) { this->offset = offset; }
        float getOffset() { return offset; }
        Tuning* getTuning() { return tuning; }

        void addNote(int note) { notes.add(note); }
        void addChordDef(std::initializer_list<int> chordDef) { chordDefs.add({chordDef}); }

        int size() { return notes.size(); }
        int getNote(int index);
        int getIndex(Note& note);

        Note getFirstNote(int cycle);
        Note getLastNote(int cycle);

        bool containsNote(int note);

    protected:
        Tuning* tuning;

        Array<int, TUNING_MAX_NOTES> notes;
        Array<ChordDef, MAX_CHORD_DEFS> chordDefs;
        float offset = 0;
};


#endif