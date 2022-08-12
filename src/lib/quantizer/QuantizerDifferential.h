#ifndef QuantizerDifferential_h
#define QuantizerDifferential_h

#include "QuantizerChromatic.h"

class QuantizerDifferential : public QuantizerChromatic {
    public:
        QuantizerDifferential(Tuning& tuning) : QuantizerChromatic(tuning) {}
        
        float quantize(float root, float voltage, int interval);

};

#endif
