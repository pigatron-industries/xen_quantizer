#ifndef ScaleFactory_h
#define ScaleFactory_h

#include "Scale.h"

class ScaleFactory {
    public:
        ScaleFactory() {}

        static Scale createHarmonicScale(Tuning& tuning, int dissonance);

        static Chord createChord(Scale& scale, ChordDef& chordDef, Note& rootNote);
};


#endif