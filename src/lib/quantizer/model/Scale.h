#ifndef ScaleDef_h
#define ScaleDef_h

#include <eurorack.h>
#include "Note.h"
#include "Tuning.h"

#define CHORD_MAX_NOTES 5
#define MAX_CHORD_DEFS 6

typedef Array<Note, CHORD_MAX_NOTES> Chord;

class ChordDef {
    public:
        ChordDef(const char* name = "") { strncpy(this->name, name, 16); }
        ChordDef(std::initializer_list<int> scaleNotes, const char* name = "") : 
            scaleNotes(scaleNotes) { strncpy(this->name, name, 16); }

        void addNote(int note) { scaleNotes.add(note); }

    public:
        char name[16] = {0};
        Array<int, CHORD_MAX_NOTES> scaleNotes;
};

class Scale {
    public:
        Scale() {}
        Scale(Tuning& tuning, const char* name = "") { this->tuning = &tuning; strncpy(this->name, name, 16); }
        Scale(Tuning& tuning, std::initializer_list<int> notes, const char* name = "") : 
            notes(notes) { this->tuning = &tuning; strncpy(this->name, name, 16); }
        Scale(Tuning& tuning, std::initializer_list<int> notes, std::initializer_list<ChordDef> chordDef, const char* name = "") : 
            notes(notes),
            chordDefs({chordDef}) { this->tuning = &tuning; strncpy(this->name, name, 16); }
        Scale(Tuning& tuning, std::initializer_list<int> notes, ChordDef& chordDef, const char* name = "") : 
            notes(notes),
            chordDefs({chordDef}) { this->tuning = &tuning; strncpy(this->name, name, 16); }

        char* getName() { return name; }

        void setOffset(float offset) { this->offset = offset; }
        float getOffset() { return offset; }
        Tuning* getTuning() { return tuning; }
        Array<ChordDef, MAX_CHORD_DEFS>& getChordDefs() { return chordDefs; };

        void addNote(int note) { notes.add(note); }
        void addChordDef(std::initializer_list<int> chordDef) { chordDefs.add({chordDef}); }
        void addChordDef(ChordDef& chordDef) { chordDefs.add(chordDef); }

        int size() { return notes.size(); }
        int getNote(int index);
        int getIndex(Note& note);

        Note getFirstNote(int cycle);
        Note getLastNote(int cycle);

        bool containsNote(int note);

    protected:
        char name[16] = {0};
        Tuning* tuning;

        Array<int, TUNING_MAX_NOTES> notes;
        Array<ChordDef, MAX_CHORD_DEFS> chordDefs;
        float offset = 0;
};


#endif