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

        int getScaleCount() { return scales.size(); }
        int getChordCount() { return chords.size(); }

        ScaleDef& getScale(int scaleIndex) { return scales[scaleIndex]; }
        ScaleDef& getChord(int chordIndex) { return scales[chordIndex]; }

        Array<ScaleDef*, MAX_SCALES>& getScalesForChord(int chordIndex) { return chordScaleLinks[chordIndex]; }
        Array<ChordDef*, MAX_CHORDS>& getChordsForScale(int scaleIndex) { return scaleChordLinks[scaleIndex]; }

    private:
        Array<ScaleDef, MAX_SCALES> scales;
        Array<ChordDef, MAX_CHORDS> chords;

        Array<Array<ChordDef*, MAX_CHORDS>, MAX_SCALES> scaleChordLinks;
        Array<Array<ScaleDef*, MAX_SCALES>, MAX_CHORDS> chordScaleLinks;

        bool match(ScaleDef& scale, ChordDef& chord);
};

#endif