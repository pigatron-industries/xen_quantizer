#ifndef ScaleRepository_h
#define ScaleRepository_h

#include <eurorack.h>
#include "Note.h"

#define SCALE_MAX_NOTES 24
#define CHORD_MAX_NOTES 4

#define MAX_SCALES 10
#define MAX_CHORDS 10

typedef Array<int, SCALE_MAX_NOTES> ScaleDef;
typedef Array<int, CHORD_MAX_NOTES> ChordDef;

class ScaleRepository {
    public:
        void clear();
        void addScale(ScaleDef& scaleDef);
        void addChord(ChordDef& chordDef);

    private:
        Array<ScaleDef, MAX_SCALES> scales;
        Array<ChordDef, MAX_CHORDS> chords;

        Array<Array<bool, MAX_SCALES>, MAX_CHORDS> links;
};

#endif