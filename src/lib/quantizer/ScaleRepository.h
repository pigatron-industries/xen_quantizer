#ifndef ScaleRepository_h
#define ScaleRepository_h

#include <eurorack.h>
#include "Note.h"
#include "ScaleDef.h"

#define MAX_SCALES 10
#define MAX_CHORDS 10

class ScaleRepository {
    public:
        void clear();
        int addScale(ScaleDef& scaleDef);
        int getScaleCount() { return scales.size(); }
        ScaleDef& getScale(int scaleIndex) { return scales[scaleIndex]; }

    private:
        Array<ScaleDef, MAX_SCALES> scales;

        bool match(ScaleDef& scale, ChordDef& chord);
};

#endif