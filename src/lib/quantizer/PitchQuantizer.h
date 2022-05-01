#ifndef PitchQuantizer_h
#define PitchQuantizer_h

#include "Tuning.h"

class PitchQuantizer {
    public:
        PitchQuantizer(Tuning& tuning) { this->tuning = &tuning; }
        void setScale(Tuning& tuning) { this->tuning = &tuning; }
        bool quantize(float voltage);

        Note& getNote() { return note; }

    private:
        Tuning* tuning;
        Note note;
        
        bool setNote(Note& note);
        Note& getClosestNote(float value, Note& prevNote, Note& nextNote);
};

#endif
