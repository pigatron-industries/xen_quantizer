#include "Tuning.h"

void Tuning::enable(int note, bool enabled) { 
    if(note > 0) { 
        intervals[note-1].enabled = enabled; 
    }
}

void Tuning::enable(std::initializer_list<int> notes) {
    for(int i = 0; i < intervals.size(); i++) {
        intervals[i].enabled = false;
    }
    for(int note : notes) {
        enable(note);
    }
}