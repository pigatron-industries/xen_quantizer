#ifndef QuantizerDifferential_h
#define QuantizerDifferential_h

#include "model/Tuning.h"

class QuantizerDifferential {
    public:
        QuantizerDifferential(Tuning& tuning) { this->tuning = &tuning; }
        void setTuning(Tuning& tuning) { this->tuning = &tuning; }
        
        float quantize(float root, float voltage, int interval);

    protected:
        Tuning* tuning;
        
        Note& getClosestNote(float value, Note& prevNote, Note& nextNote);
};

#endif
