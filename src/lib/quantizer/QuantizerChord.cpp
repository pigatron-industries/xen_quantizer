#include "QuantizerChord.h"

Note QuantizerChord::quantize(float voltage) {
    int cycle = tuning->findCycle(voltage, scale->getOffset());

    // find start note of chord in cycle (chord may be transposed past the cycle)
    int chordCycleStart = 0;
    int prevChordCycle = (*chord)[0].cycle;
    for(int i = 1; i < chord->size(); i++) {
        if(prevChordCycle != (*chord)[i].cycle) {
            chordCycleStart = i;
            break;
        }
        prevChordCycle = (*chord)[i].cycle;
    }
    int chordCycleEnd = chordCycleStart == 0 ? chord->size()-1 : chordCycleStart-1;

    Note prevNote = tuning->createNote(cycle-1, (*chord)[chordCycleEnd].note, scale->getOffset());
    Note nextNote;

    for(int i = 0; i < (*chord).size(); i++) {
        nextNote = tuning->createNote(cycle, (*chord)[(chordCycleStart+i)%chord->size()].note, scale->getOffset());
        if(nextNote.voltage > voltage) {
            return getClosestNote(voltage, prevNote, nextNote);
        }
        prevNote = nextNote;
    }
    
    nextNote = tuning->createNote(cycle+1, (*chord)[chordCycleStart].note, scale->getOffset());
    return getClosestNote(voltage, prevNote, nextNote);
}