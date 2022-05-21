#ifndef ScaleDef_h
#define ScaleDef_h

#include <eurorack.h>
#include "Note.h"

#define SCALE_MAX_NOTES 24
#define CHORD_MAX_NOTES 5
#define MAX_CHORD_DEFS 5

typedef Array<int, CHORD_MAX_NOTES> ChordDef;
typedef Array<Note, CHORD_MAX_NOTES> Chord;

class ScaleDef {
    public:
        ScaleDef() {}
        ScaleDef(std::initializer_list<int> notes) : notes(notes) {}
        ScaleDef(std::initializer_list<int> notes, std::initializer_list<int> chordDef) : 
            notes(notes),
            chordDefs({chordDef}) {}
        ScaleDef(std::initializer_list<int> notes, ChordDef& chordDef) : 
            notes(notes),
            chordDefs({chordDef}) {}

        void addChordDef(std::initializer_list<int> chordDef) { chordDefs.add({chordDef}); }

        int size() { return notes.size(); }
        int getNote(int index) { return notes[index%notes.size()]; }

        bool contains(int note) { return notes.contains(note); }

    private:
        Array<int, SCALE_MAX_NOTES> notes;
        Array<ChordDef, MAX_CHORD_DEFS> chordDefs;
};


#endif