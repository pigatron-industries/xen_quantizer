#include "PitchQuantizer.h"

Note PitchQuantizer::quantizeChromatic(float voltage) {
    int repeat = tuning->findRepeatNumber(voltage);
    Note prevNote = tuning->createNote(repeat, 0);
    Note nextNote;

    for(int i = 1; i <= tuning->getNotes(); i++) {
        nextNote = tuning->createNote(repeat, i);
        if(nextNote.voltage > voltage) {
            return getClosestNote(voltage, prevNote, nextNote);
        }
        prevNote = nextNote;
    }
    
    nextNote = tuning->createNote(repeat+1, 0);
    return getClosestNote(voltage, prevNote, nextNote);
}

Note PitchQuantizer::quantizeToScale(float voltage, ScaleDef& scale) {
    int repeat = tuning->findRepeatNumber(voltage);
    Note prevNote = tuning->createNote(repeat, 0);
    Note nextNote;

    for(int i = 1; i <= tuning->getNotes(); i++) {
        nextNote = tuning->createNote(repeat, i);
        if(scale.contains(nextNote.note)) {
            if(nextNote.voltage > voltage) {
                return getClosestNote(voltage, prevNote, nextNote);
            }
            prevNote = nextNote;
        }
    }
    
    nextNote = tuning->createNote(repeat+1, 0);
    return getClosestNote(voltage, prevNote, nextNote);
}

Note& PitchQuantizer::getClosestNote(float voltage, Note& prevNote, Note& nextNote) {
    if((nextNote.voltage - voltage) < (voltage - prevNote.voltage)) {
        return nextNote;
    } else {
        return prevNote;
    }
}
