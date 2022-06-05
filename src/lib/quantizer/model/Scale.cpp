#include "Scale.h"

// #include "debug.h"

bool Scale::containsNote(int note) {
    //TODO more efficient to negatively offset note paramter instead of offset each note?
    for(int i = 0; i < notes.size(); i++) {
        if(notes[i] == note) {
            return true;
        }
    }
    return false;
}

Note Scale::getFirstNote(int cycle) {
    return tuning->createNote(cycle, notes[0], offset);
}

Note Scale::getLastNote(int cycle) {
    return tuning->createNote(cycle, notes[notes.size()-1], offset);
}

int Scale::getNote(int index) { 
    return notes[index];
}

int Scale::getIndex(Note& note) {
    for(int i = 0; i < notes.size(); i++) {
        if(notes[i] == note.note) {
            return i;
        }
    }
    return -1;
}