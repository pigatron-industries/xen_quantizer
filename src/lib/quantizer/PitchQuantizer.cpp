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

Note PitchQuantizer::quantizeToScale(float voltage) {
    int repeat = tuning->findRepeatNumber(voltage);
    Note prevNote = tuning->createNote(repeat, 0);
    Note nextNote;

    for(int i = 1; i <= tuning->getNotes(); i++) {
        nextNote = tuning->createNote(repeat, i);
        if(scaleDef->contains(nextNote.note)) {
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

Chord& PitchQuantizer::createChord(ChordDef& chordDef, Note& root) {
    chord.clear();
    int scaleIndexRoot = getScaleIndex(root);
    for(int i = 0; i < chordDef.size(); i++) {
        int chordDefNote = chordDef[i];
        int scaleIndex = scaleIndexRoot + chordDefNote;
        int repeat = (scaleIndex / scaleDef->size()) + root.repeat;
        int note = scaleDef->getNote(scaleIndex % scaleDef->size());
        chord.add(tuning->createNote(repeat, note));
    }

    return chord;
}

int PitchQuantizer::getScaleIndex(Note& note) {
    for(int i = 0; i < scaleDef->size(); i++) {
        if(scaleDef->getNote(i) == note.note) {
            return i;
        }
    }
    return -1;
}