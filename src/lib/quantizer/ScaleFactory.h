#ifndef ScaleFactory_h
#define ScaleFactory_h

#include "model/Scale.h"

class ScaleFactory {
    public:
        ScaleFactory() {}

        static Scale createHarmonicScale(Tuning& tuning, int dissonance);
        static Scale createHarmonicScale(Scale& scale, int dissonance);

        static Chord createChord(Scale& scale, ChordDef& chordDef, Note& rootNote, int inversion = 0, int drop = 0);
};


#endif