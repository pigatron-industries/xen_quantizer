#ifndef QuantizerChromatic_h
#define QuantizerChromatic_h

#include "Tuning.h"

class QuantizerChromatic {
    public:
        QuantizerChromatic(Tuning& tuning) { this->tuning = &tuning; }
        void setTuning(Tuning& tuning) { this->tuning = &tuning; }
        
        Note quantize(float voltage);

    protected:
        Tuning* tuning;
        
        Note& getClosestNote(float value, Note& prevNote, Note& nextNote);
};

#endif
