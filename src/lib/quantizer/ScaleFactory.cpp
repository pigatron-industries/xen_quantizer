#include "ScaleFactory.h"

Tuning ScaleFactory::createEqualDivisionTuning(int divisions, float cycle) {
    return Tuning(divisions, cycle);
}

Scale ScaleFactory::createHarmonicScale(Tuning& tuning, int dissonance) {
    Scale scale = Scale(tuning);
    for(int i = 0; i < tuning.size(); i++) {
        int intervalDissonance = tuning.getInterval(i).dissonance;
        if(intervalDissonance <= dissonance) {
            scale.addNote(i);
        }
    }
    return scale;
}

Scale ScaleFactory::createHarmonicScale(Scale& scale, int dissonance) {
    Scale subScale = Scale(*scale.getTuning());
    for(int i = 0; i < scale.size(); i++) {
        int note = scale.getNote(i);
        int intervalDissonance = scale.getTuning()->getInterval(note).dissonance;
        if(intervalDissonance <= dissonance) {
            subScale.addNote(note);
        }
    }
    return subScale;
}

Chord ScaleFactory::createChord(Scale& scale, ChordDef& chordDef, Note& rootNote, int inversion, int drop) {
    Chord chord;
    int scaleIndexRoot = scale.getIndex(rootNote);
    for(int i = 0; i < chordDef.scaleNotes.size(); i++) {
        int chordDefNote = chordDef.scaleNotes[i];
        int scaleIndex = scaleIndexRoot + chordDefNote;
        int cycle = (scaleIndex / scale.size()) + rootNote.cycle;
        int note = scale.getNote(scaleIndex % scale.size());
        if(i < inversion) {
            cycle++;
        }
        if(drop > 0 && i == drop) {
            cycle--;
        }
        chord.add(scale.getTuning()->createNote(cycle, note, scale.getOffset()));
    }

    return chord;
}