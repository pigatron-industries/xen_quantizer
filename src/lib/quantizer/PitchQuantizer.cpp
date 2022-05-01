#include "PitchQuantizer.h"

Note PitchQuantizer::quantizeChromatic(float voltage) {
    int repeat = tuning->findRepeatNumber(voltage);
    Note prevNote = tuning->getNote(repeat, 0);
    Note nextNote;

    for(int i = 1; i <= tuning->getNotes(); i++) {
        nextNote = tuning->getNote(repeat, i);
        if(nextNote.voltage > voltage) {
            return getClosestNote(voltage, prevNote, nextNote);
        }
        prevNote = nextNote;
    }
    
    nextNote = tuning->getNote(repeat+1, 0);
    return getClosestNote(voltage, prevNote, nextNote);
}

Note PitchQuantizer::quantizeToScale(float voltage, Scale& scale) {
    int repeat = tuning->findRepeatNumber(voltage);
    Note prevNote = tuning->getNote(repeat, 0);
    Note nextNote;

    for(int i = 1; i <= tuning->getNotes(); i++) {
        nextNote = tuning->getNote(repeat, i);
        if(scale.notes.contains(nextNote.note)) {
            if(nextNote.voltage > voltage) {
                return getClosestNote(voltage, prevNote, nextNote);
            }
            prevNote = nextNote;
        }
    }
    
    nextNote = tuning->getNote(repeat+1, 0);
    return getClosestNote(voltage, prevNote, nextNote);
}

Note& PitchQuantizer::getClosestNote(float voltage, Note& prevNote, Note& nextNote) {
    if((nextNote.voltage - voltage) < (voltage - prevNote.voltage)) {
        return nextNote;
    } else {
        return prevNote;
    }
}

