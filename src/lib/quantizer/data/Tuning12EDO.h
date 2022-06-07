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
        static ChordDef Tuning12EDO::chord_triad;
};

#endif