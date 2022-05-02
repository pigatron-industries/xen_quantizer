#ifndef PitchQuantizer_h
#define PitchQuantizer_h

#include "Tuning.h"

class PitchQuantizer {
    public:
        PitchQuantizer(Tuning& tuning) { this->tuning = &tuning; }
        void setTuning(Tuning& tuning) { this->tuning = &tuning; }

        Note quantizeChromatic(float voltage);
        Note quantizeToScale(float voltage, ScaleDef& scale);

    private:
        Tuning* tuning;
        
        Note& getClosestNote(float value, Note& prevNote, Note& nextNote);
};

#endif
