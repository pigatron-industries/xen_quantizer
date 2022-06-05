#ifndef TuningData_h
#define TuningData_h

#include <eurorack.h>
#include "../model/Note.h"
#include "../model/Scale.h"
#include "../model/Tuning.h"


class TuningData {
    public:
        TuningData(Tuning& tuning, ArrayPtr<Scale> scales, ArrayPtr<ChordDef> chordDefs) : 
            tuning(&tuning), 
            scales(scales), 
            chordDefs(chordDefs) {}

    public:
        Tuning* tuning;
        ArrayPtr<Scale> scales;
        ArrayPtr<ChordDef> chordDefs;

};

#endif