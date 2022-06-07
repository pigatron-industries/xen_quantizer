#ifndef TuningData_h
#define TuningData_h

#include <eurorack.h>
#include "../model/Note.h"
#include "../model/Scale.h"
#include "../model/Tuning.h"


class TuningData {
    public:
        TuningData(Tuning& tuning, ArrayPtr<Scale> scales) : 
            tuning(&tuning), 
            scales(scales) {}

    public:
        Tuning* tuning;
        ArrayPtr<Scale> scales;

};

#endif