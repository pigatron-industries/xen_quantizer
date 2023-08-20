#ifndef QuantizerChromatic_h
#define QuantizerChromatic_h

#include "model/Tuning.h"

/**
 * Chromatic Quantizer
 * Quantizes voltage to the closest note in the tuning.
 */
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
