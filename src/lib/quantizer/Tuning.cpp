#include "Tuning.h"

Note Tuning::createNote(int repeat, int note, int offset) { 
    float voltage = getNoteVoltage(repeat, note, offset);
    return Note(repeat, note, voltage); 
}

Chord Tuning::createChord(Note& root, ChordDef& chordDef) {
    Chord chord;
    for(int i = 0; i < chordDef.size(); i++) {
        Note note = createNote(root.repeat, chordDef[i], root.note);
        chord.add(note);
    }

    return chord;
}

float Tuning::getNoteVoltage(int repeat, int note, int offset) { 
    return getRepeatVoltage(repeat) + getIntervalVoltage(note) + getIntervalVoltage(offset);
}