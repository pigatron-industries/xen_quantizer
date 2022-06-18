#ifndef Tuning12EDO_h
#define Tuning12EDO_h

#include <eurorack.h>
#include "StaticTuningData.h"

class Tuning12EDO : public StaticTuningData {
    public:
        static StaticTuningData& getData() { return data; }

    public:
        static StaticTuningData data;
        static Tuning tuning;
        static Array<Scale, 5> scales;

    private:
        static ChordDef chord_heptatonic_tertian;
        static ChordDef chord_heptatonic_quartal;
        static ChordDef chord_heptatonic_quintal;
        
        static ChordDef chord_chromatic_major;
        static ChordDef chord_chromatic_minor;
        static ChordDef chord_chromatic_diminished;
        static ChordDef chord_chromatic_augmented;
};

#endif