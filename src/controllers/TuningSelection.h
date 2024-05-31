#ifndef TuningSelection_h
#define TuningSelection_h

#include "lib/quantizer/data/Tuning12EDO.h"
#include "lib/quantizer/filesystem/TuningsManager.h"


class TuningSelection {
    public:
        TuningSelection() {}


    protected:
        StaticTuningData* defaultTuningData = &Tuning12EDO::data;
        TuningData* tuningData = nullptr;
        Tuning* tuning = defaultTuningData->tuning;

};

#endif