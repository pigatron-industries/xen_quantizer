#ifndef ScaleDef_h
#define ScaleDef_h

#include <eurorack.h>
#include "Note.h"
#include "Tuning.h"

#define CHORD_MAX_NOTES 5
#define MAX_CHORD_DEFS 5

typedef Array<Note, CHORD_MAX_NOTES> Chord;

class ChordDef {
    public:
        ChordDef() {}
        ChordDef(std::initializer_list<int> scaleNotes) : scaleNotes(scaleNotes) {}

    public:
        Array<int, CHORD_MAX_NOTES> scaleNotes;
};

class Scale {
    public:
        Scale() {}
        Scale(Tuning& tuning, const char* name = "") { this->tuning = &tuning; this->name = name; }
        Scale(Tuning& tuning, std::initializer_list<int> notes, const char* name = "") : 
            notes(notes) { this->tuning = &tuning; this->name = name; }
        Scale(Tuning& tuning, std::initializer_list<int> notes, std::initializer_list<ChordDef> chordDef, const char* name = "") : 
            notes(notes),
            chordDefs({chordDef}) { this->tuning = &tuning; this->name = name; }
        Scale(Tuning& tuning, std::initializer_list<int> notes, ChordDef& chordDef, const char* name = "") : 
            notes(notes),
            chordDefs({chordDef}) { this->tuning = &tuning; this->name = name; }

        void setOffset(float offset) { this->offset = offset; }
        float getOffset() { return offset; }
        Tuning* getTuning() { return tuning; }
        Array<ChordDef, MAX_CHORD_DEFS>& getChordDefs() { return chordDefs; };

        void addNote(int note) { notes.add(note); }
        void addChordDef(std::initializer_list<int> chordDef) { chordDefs.add({chordDef}); }

        int size() { return notes.size(); }
        int getNote(int index);
        int getIndex(Note& note);

        Note getFirstNote(int cycle);
        Note getLastNote(int cycle);

        bool containsNote(int note);

    protected:
        const char* name;
        Tuning* tuning;

        Array<int, TUNING_MAX_NOTES> notes;
        Array<ChordDef, MAX_CHORD_DEFS> chordDefs;
        float offset = 0;
};


#endif