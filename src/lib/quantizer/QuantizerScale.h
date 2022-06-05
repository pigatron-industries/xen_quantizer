#ifndef QuantizerScale_h
#define QuantizerScale_h

#include "QuantizerChromatic.h"
#include "model/Scale.h"

class QuantizerScale : public QuantizerChromatic {
    public:
        QuantizerScale(Scale& scale) : QuantizerChromatic(*scale.getTuning()) { this->scale = &scale; }
        void setScale(Scale& scale) { this->scale = &scale; }
        Scale* getScale() { return scale; }
        
        Note quantize(float voltage);

    protected:
        Scale* scale;
};

#endif
