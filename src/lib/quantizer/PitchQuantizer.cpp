#include "PitchQuantizer.h"

Note PitchQuantizer::quantizeChromatic(float voltage) {
    int cycle = tuning->findCycle(voltage);
    Note prevNote = scale->getFirstNote(cycle);
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

Note PitchQuantizer::quantizeToScale(float voltage) {
    //TODO get note before first note in scale (last note of previous repeat)
    int cycle = tuning->findCycle(voltage, scale->getOffset());
    Note prevNote = scale->getLastNote(cycle-1);
    Note nextNote;

    for(int i = 0; i < tuning->size(); i++) {
        nextNote = tuning->createNote(cycle, i, scale->getOffset());
        if(scale->containsNote(nextNote.note)) {
            if(nextNote.voltage > voltage) {
                return getClosestNote(voltage, prevNote, nextNote);
            }
            prevNote = nextNote;
        }
    }
    
    nextNote = scale->getFirstNote(cycle+1);
    return getClosestNote(voltage, prevNote, nextNote);
}

Note& PitchQuantizer::getClosestNote(float voltage, Note& prevNote, Note& nextNote) {
    if((nextNote.voltage - voltage) < (voltage - prevNote.voltage)) {
        return nextNote;
    } else {
        return prevNote;
    }
}

Chord& PitchQuantizer::createChord(ChordDef& chordDef, Note& root) {
    chord.clear();
    int scaleIndexRoot = getScaleIndex(root);
    for(int i = 0; i < chordDef.size(); i++) {
        int chordDefNote = chordDef[i];
        int scaleIndex = scaleIndexRoot + chordDefNote;
        int repeat = (scaleIndex / scale->size()) + root.cycle;
        int note = scale->getNote(scaleIndex % scale->size());
        chord.add(tuning->createNote(repeat, note, scale->getOffset()));
    }

    return chord;
}

int PitchQuantizer::getScaleIndex(Note& note) {
    for(int i = 0; i < scale->size(); i++) {
        if(scale->getNote(i) == note.note) {
            return i;
        }
    }
    return -1;
}