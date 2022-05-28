#ifndef ScaleQuantizer_h
#define ScaleQuantizer_h

#include "Scale.h"

class ScaleQuantizer {
    public:
        ScaleQuantizer(Tuning& tuning) { this->tuning = &tuning; }
        ScaleQuantizer(Tuning& tuning, Scale& scale) { this->tuning = &tuning; this->scale = &scale; }
        void setTuning(Tuning& tuning) { this->tuning = &tuning; }
        void setScale(Scale& scale) { this->scale = &scale; }
        void setScaleOffset(float scaleOffset) { this->scale->setOffset(scaleOffset); }
        
        Note quantizeChromatic(float voltage);
        Note quantizeToScale(float voltage);
        Note quantizeToChord(float voltage);
        
        Chord& createChord(ChordDef& chordDef, Note& rootNote);

    private:
        Tuning* tuning;
        Scale* scale;

        Chord chord;
        
        Note& getClosestNote(float value, Note& prevNote, Note& nextNote);
        int getScaleIndex(Note& note);
};

#endif
