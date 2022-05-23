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
        Scale() :
            firstNoteIndex(0, 0) {}
        Scale(Tuning& tuning, std::initializer_list<int> notes) : 
            notes(notes),
            firstNoteIndex(0, notes.size()-1) { this->tuning = &tuning; }
        Scale(Tuning& tuning, std::initializer_list<int> notes, std::initializer_list<int> chordDef) : 
            notes(notes),
            chordDefs({chordDef}),
            firstNoteIndex(0, notes.size()-1) { this->tuning = &tuning; }
        Scale(Tuning& tuning, std::initializer_list<int> notes, ChordDef& chordDef) : 
            notes(notes),
            chordDefs({chordDef}),
            firstNoteIndex(0, notes.size()-1) { this->tuning = &tuning; }

        void setOffset(int offset) { this->offset = offset; calcNoteOffsets(); }

        void addChordDef(std::initializer_list<int> chordDef) { chordDefs.add({chordDef}); }

        int size() { return notes.size(); }
        int getNote(int index);

        Note getFirstNote(int cycle);
        Note getLastNote(int cycle);

        bool containsNote(int note);

    private:
        Tuning* tuning;

        Array<int, TUNING_MAX_NOTES> notes;
        Array<ChordDef, MAX_CHORD_DEFS> chordDefs;
        int offset = 0;

        CycleEnum<int> firstNoteIndex;

        int getOffsetNote(int note);
        void calcNoteOffsets();
};


#endif