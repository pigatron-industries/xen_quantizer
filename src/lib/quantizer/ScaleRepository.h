#ifndef ScaleRepository_h
#define ScaleRepository_h

#include <eurorack.h>
#include "Note.h"
#include "Scale.h"

#define MAX_SCALES 10
#define MAX_CHORDS 10

class ScaleRepository {
    public:
        void clear();
        int addScale(Scale& scale);
        int getScaleCount() { return scales.size(); }
        Scale& getScale(int scaleIndex) { return scales[scaleIndex]; }

    private:
        Array<Scale, MAX_SCALES> scales;

        bool match(Scale& scale, ChordDef& chord);
};

#endif