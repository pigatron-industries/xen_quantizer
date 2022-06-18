#ifndef TuningData_h
#define TuningData_h

#include <eurorack.h>
#include "../model/Note.h"
#include "../model/Scale.h"
#include "../model/Tuning.h"


class TuningData {
    public:
        void addScale(Scale* scale) { scales.add(scale); }

    public:
        Tuning* tuning;
        Array<Scale*, 20> scales;

};

#endif