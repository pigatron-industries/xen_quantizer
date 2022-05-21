#ifndef PitchQuantizer_h
#define PitchQuantizer_h

#include "Tuning.h"

class PitchQuantizer {
    public:
        PitchQuantizer(Tuning& tuning) { this->tuning = &tuning; }
        PitchQuantizer(Tuning& tuning, ScaleDef& scaleDef) { this->tuning = &tuning; this->scaleDef = &scaleDef; }
        void setTuning(Tuning& tuning) { this->tuning = &tuning; }
        void setScale(ScaleDef& scaleDef) { this->scaleDef = &scaleDef; }
        
        Note quantizeChromatic(float voltage);
        Note quantizeToScale(float voltage);
        
        Chord& createChord(ChordDef& chordDef, Note& rootNote);


    private:
        Tuning* tuning;
        ScaleDef* scaleDef;

        Chord chord;
        
        Note& getClosestNote(float value, Note& prevNote, Note& nextNote);
        int getScaleIndex(Note& note);
};

#endif
