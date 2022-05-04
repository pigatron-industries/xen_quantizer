#include "ScaleRepository.h"

void ScaleRepository::clear() {
    scales.clear();
    chords.clear();
    scaleChordLinks.clear();
    chordScaleLinks.clear();
}

void ScaleRepository::addScale(ScaleDef& scale) {
    int scaleIndex = scales.add(scale);
    ScaleDef& scaleDef = scales[scaleIndex];
    scaleChordLinks.add(Array<ChordDef*, MAX_CHORDS>());

    for(int chordIndex = 0; chordIndex < chords.size(); chordIndex++) {
        ChordDef& chordDef = chords[chordIndex];
        if(match(scaleDef, chordDef)) {
            scaleChordLinks[scaleIndex].add(&chordDef);
            chordScaleLinks[chordIndex].add(&scaleDef);
        }
    }    
}

void ScaleRepository::addChord(ChordDef& chord) {
    int chordIndex = chords.add(chord);
    ChordDef& chordDef = chords[chordIndex];
    chordScaleLinks.add(Array<ScaleDef*, MAX_SCALES>());

    for(int scaleIndex = 0; scaleIndex < scales.size(); scaleIndex++) {
        ScaleDef& scaleDef = scales[scaleIndex];
        if(match(scaleDef, chordDef)) {
            chordScaleLinks[chordIndex].add(&scaleDef);
            scaleChordLinks[scaleIndex].add(&chordDef);
        }
    }   
}

bool ScaleRepository::match(ScaleDef& scale, ChordDef& chord) {
    for(int note : chord) {
        if(!scale.contains(note)) {
            return false;
        }
    }
    return true;
}
