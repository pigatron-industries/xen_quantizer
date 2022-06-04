#include "QuantizerScale.h"

Note QuantizerScale::quantize(float voltage) {
    int cycle = tuning->findCycle(voltage, scale->getOffset());
    Note prevNote = scale->getLastNote(cycle-1);
    Note nextNote;

    for(int i = 0; i < scale->size(); i++) {
        nextNote = tuning->createNote(cycle, scale->getNote(i), scale->getOffset());
        if(nextNote.voltage > voltage) {
            return getClosestNote(voltage, prevNote, nextNote);
        }
        prevNote = nextNote;
    }
    
    nextNote = scale->getFirstNote(cycle+1);
    return getClosestNote(voltage, prevNote, nextNote);
}
