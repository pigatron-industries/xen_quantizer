#ifndef PitchQuantizer_h
#define PitchQuantizer_h

#include "Scale.h"

class PitchQuantizer {
    public:
        PitchQuantizer(Tuning& tuning) { this->tuning = &tuning; }
        PitchQuantizer(Tuning& tuning, Scale& scale) { this->tuning = &tuning; this->scale = &scale; }
        void setTuning(Tuning& tuning) { this->tuning = &tuning; }
        void setScale(Scale& scale) { this->scale = &scale; }
        void setScaleOffset(float scaleOffset) { this->scale->setOffset(scaleOffset); }
        
        Note quantizeChromatic(float voltage);
        Note quantizeToScale(float voltage);
        
        Chord& createChord(ChordDef& chordDef, Note& rootNote);

    private:
        Tuning* tuning;
        Scale* scale;

        Chord chord;
        
        Note& getClosestNote(float value, Note& prevNote, Note& nextNote);
        int getScaleIndex(Note& note);
};

#endif
