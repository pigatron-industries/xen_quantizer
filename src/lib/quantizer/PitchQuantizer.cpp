#include "PitchQuantizer.h"

bool PitchQuantizer::quantize(float voltage) {
    int repeat = tuning->findRepeatNumber(voltage);
    Note prevNote = tuning->getNote(repeat, 0);
    Note nextNote;

    for(int i = 1; i <= tuning->getNotes(); i++) {
        nextNote = tuning->getNote(repeat, i);
        if(tuning->isEnabled(nextNote)) {
            if(nextNote.voltage > voltage) {
                return setNote(getClosestNote(voltage, prevNote, nextNote));
            }
            prevNote = nextNote;
        }
    }
    
    nextNote = tuning->getNote(repeat+1, 0);
    return setNote(getClosestNote(voltage, prevNote, nextNote));
}

Note& PitchQuantizer::getClosestNote(float voltage, Note& prevNote, Note& nextNote) {
    if((nextNote.voltage - voltage) < (voltage - prevNote.voltage)) {
        return nextNote;
    } else {
        return prevNote;
    }
}

bool PitchQuantizer::setNote(Note& note) {
    if(this->note.note != note.note || this->note.repeat != note.repeat) {
        this->note = note;
        return true;
    }
    return false;
}
