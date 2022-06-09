#ifndef Tuning12EDO_h
#define Tuning12EDO_h

#include <eurorack.h>
#include "TuningData.h"

class Tuning12EDO : public TuningData {
    public:
        static TuningData& getData() { return data; }

    public:
        static TuningData data;
        static Tuning tuning;
        static Array<Scale, 5> scales;

    private:
        static ChordDef chord_heptatonic_triad;
        static ChordDef chord_chromatic_major;
        static ChordDef chord_chromatic_minor;
        static ChordDef chord_chromatic_diminished;
        static ChordDef chord_chromatic_augmented;
};

#endif