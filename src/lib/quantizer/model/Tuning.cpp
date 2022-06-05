#include "Tuning.h"

int Tuning::findCycle(float voltage, float offset) {
    return floorf((voltage-offset) * cycleIntervalRecip);
}

Note Tuning::createNote(int cycle, int note, float offset) { 
    float voltage = getNoteVoltage(cycle, note, offset);
    return Note(cycle, note, voltage, offset);
}

Note Tuning::getFirstNote(int cycle, float offset) {
    return createNote(cycle, 0, offset);
}

Note Tuning::getLastNote(int cycle, float offset) {
    return createNote(cycle, intervals.size()-1, offset);
}

float Tuning::getNoteVoltage(int cycle, int note, float offset) { 
    return getCycleVoltage(cycle) + getIntervalVoltage(note) + offset;
}