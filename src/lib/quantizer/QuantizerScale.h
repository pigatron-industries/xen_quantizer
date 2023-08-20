#ifndef QuantizerScale_h
#define QuantizerScale_h

#include "QuantizerChromatic.h"
#include "model/Scale.h"

/**
 * Scale Quantizer
 * Quantizes voltage to the closest note in the given scale.
 */
class QuantizerScale : public QuantizerChromatic {
    public:
        QuantizerScale(Scale& scale) : QuantizerChromatic(*scale.getTuning()) { this->scale = &scale;}
        void setScale(Scale& scale) { this->scale = &scale; this->tuning = scale.getTuning(); }
        Scale* getScale() { return scale; }
        
        Note quantize(float voltage);

    protected:
        Scale* scale;
};

#endif
