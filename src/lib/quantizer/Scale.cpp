#include "Scale.h"

// #include "debug.h"

bool Scale::containsNote(int note) {
    //TODO more efficient to negatively offset note paramter instead of offset each note?
    for(int i = 0; i < notes.size(); i++) {
        int offsetNote = getOffsetNote(notes[i]);
        if(offsetNote == note) {
            return true;
        }
    }
    return false;
}

Note Scale::getFirstNote(int cycle) {
    return tuning->createNote(cycle, getOffsetNote(notes[firstNoteIndex.value]));
}

Note Scale::getLastNote(int cycle) {
    return tuning->createNote(cycle, getOffsetNote(notes[firstNoteIndex-1]));
}

int Scale::getNote(int index) { 
    return getOffsetNote(notes[firstNoteIndex+index]);
}

int Scale::getOffsetNote(int note) {
    if(offset > 0) {
        return (note + offset) % tuning->size();
    } else {
        return note;
    }
}

void Scale::calcNoteOffsets() {
    CycleEnum<int> prevNoteIndex = CycleEnum<int>(0, notes.size()-1);
    for(int i = 0; i < notes.size(); i++) {
        prevNoteIndex = i-1;
        int prevNote = getOffsetNote(notes[prevNoteIndex.value]);
        int nextNote = getOffsetNote(notes[i]);
        if(prevNote > nextNote) {
            firstNoteIndex = i;
            return;
        }
    }
}