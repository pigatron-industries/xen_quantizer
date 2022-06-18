#ifndef StaticTuningData_h
#define StaticTuningData_h

#include <eurorack.h>
#include "../model/Note.h"
#include "../model/Scale.h"
#include "../model/Tuning.h"


class StaticTuningData {
    public:
        StaticTuningData(Tuning& tuning, ArrayPtr<Scale> scales) : 
            tuning(&tuning), 
            scales(scales) {}

    public:
        Tuning* tuning;
        ArrayPtr<Scale> scales;

};

#endif