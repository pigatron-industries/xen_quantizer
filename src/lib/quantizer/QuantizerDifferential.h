#ifndef QuantizerDifferential_h
#define QuantizerDifferential_h

#include "QuantizerChromatic.h"

/**
 * Quantize to specific interval within a tuning.
 * Starting at a root voltage, quantizes the input voltage to a multiple of the given interval in the tuning.
 */
class QuantizerDifferential : public QuantizerChromatic {
    public:
        QuantizerDifferential(Tuning& tuning) : QuantizerChromatic(tuning) {}
        
        float quantize(float root, float voltage, int intervalIndex);

    private:
        float offset = 0;

        float quantizeToMultiple(float input, float multiple, float offset);

};

#endif
