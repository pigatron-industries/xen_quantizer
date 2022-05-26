#include "Tuning.h"

int Tuning::findCycle(float voltage, float offset) {
    return floorf((voltage-offset) * cycleIntervalRecip);
}

Note Tuning::createNote(int cycle, int note, float offset) { 
    float voltage = getNoteVoltage(cycle, note, offset);
    return Note(cycle, note, voltage, offset);
}

float Tuning::getNoteVoltage(int cycle, int note, float offset) { 
    return getCycleVoltage(cycle) + getIntervalVoltage(note) + offset;
}