#ifndef QuantizerChord_h
#define QuantizerChord_h

#include "QuantizerScale.h"
#include "model/Scale.h"

class QuantizerChord : public QuantizerScale {
    public:
        QuantizerChord(Scale& scale, Chord& chord) : QuantizerScale(scale) { this->chord = &chord; }
        void setChord(Chord& chord) { this->chord = &chord; }
        
        Note quantize(float voltage);

    private:
        Chord* chord;
};

#endif
