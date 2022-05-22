#include "Tuning.h"

Note Tuning::createNote(int cycle, int note, int offset) { 
    float voltage = getNoteVoltage(cycle, note, offset);
    return Note(cycle, note, voltage); 
}

// Chord Tuning::createChord(Note& root, ChordDef& chordDef) {
//     Chord chord;
//     for(int i = 0; i < chordDef.size(); i++) {
//         Note note = createNote(root.repeat, chordDef[i], root.note);
//         chord.add(note);
//     }

//     return chord;
// }

float Tuning::getNoteVoltage(int cycle, int note, int offset) { 
    return getCycleVoltage(cycle) + getIntervalVoltage(note) + getIntervalVoltage(offset);
}