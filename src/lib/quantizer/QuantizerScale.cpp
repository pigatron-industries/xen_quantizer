#include "QuantizerScale.h"

Note QuantizerScale::quantize(float voltage) {
    return quantize(voltage, scale->getOffset());
}


Note QuantizerScale::quantize(float voltage, float offset) {
    int cycle = tuning->findCycle(voltage, offset);
    Note prevNote = scale->getLastNote(cycle-1);
    Note nextNote;

    for(int i = 0; i < scale->size(); i++) {
        nextNote = tuning->createNote(cycle, scale->getNote(i), offset);
        if(nextNote.voltage > voltage) {
            return getClosestNote(voltage, prevNote, nextNote);
        }
        prevNote = nextNote;
    }
    
    nextNote = scale->getFirstNote(cycle+1);
    return getClosestNote(voltage, prevNote, nextNote);
}
