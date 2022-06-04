#include "QuantizerChromatic.h"

Note QuantizerChromatic::quantize(float voltage) {
    int cycle = tuning->findCycle(voltage);
    Note prevNote = tuning->getFirstNote(cycle);
    Note nextNote;

    for(int i = 1; i <= tuning->size(); i++) {
        nextNote = tuning->createNote(cycle, i);
        if(nextNote.voltage > voltage) {
            return getClosestNote(voltage, prevNote, nextNote);
        }
        prevNote = nextNote;
    }
    
    nextNote = tuning->createNote(cycle+1, 0);
    return getClosestNote(voltage, prevNote, nextNote);
}

Note& QuantizerChromatic::getClosestNote(float voltage, Note& prevNote, Note& nextNote) {
    if((nextNote.voltage - voltage) < (voltage - prevNote.voltage)) {
        return nextNote;
    } else {
        return prevNote;
    }
}