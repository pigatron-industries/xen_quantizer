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
        static Array<Scale, 4> scales;
        static Array<ChordDef, 1> chordDefs;
};

#endif