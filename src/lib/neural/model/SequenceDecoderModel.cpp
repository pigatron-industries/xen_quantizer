#include "SequenceDecoderModel.h"

void SequenceDecoderModel::init() {
    notesPerTick = model.getMetadata().data[0];
    ticksPerSequence = model.getMetadata().data[1];
    tickCounter = -1;
    Serial.print("notesPerTick: ");
    Serial.println(notesPerTick);
    Serial.print("ticksPerSequence: ");
    Serial.println(ticksPerSequence);
}

uint8_t SequenceDecoderModel::tick() {
    tickCounter++;
    if(tickCounter >= ticksPerSequence) {
        tickCounter = 0;
    }
    return tickCounter;
}

OutputNote* SequenceDecoderModel::getOutputNotes() {
    for(uint8_t i = 0; i < MAX_NOTES_OUTPUT; i++) {
        notes[i].note = 0;
        notes[i].probability = 0;
    }
    
    for(uint8_t i = 0; i < notesPerTick; i++) {
        int outputIndex = tickCounter * notesPerTick + i;
        float output = model.getOutput(outputIndex);
        addNote(i, output);
    }
    return notes;
}

void SequenceDecoderModel::addNote(uint8_t note, float output) {
    // Serial.println(output);

    // get index of lowest output in list
    uint8_t lowestIndex = 0;
    float lowestOutput = 1;
    for(uint8_t i = 0; i < MAX_NOTES_OUTPUT; i++) {
        if(notes[i].probability < lowestOutput) {
            lowestIndex = i;
            lowestOutput = notes[i].probability;
        }
    }

    // if new note is higher than lowest note, replace it
    if(output > lowestOutput) {
        notes[lowestIndex].note = note;
        notes[lowestIndex].probability = output;
    }
}