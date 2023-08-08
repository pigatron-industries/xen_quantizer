#include "SequenceDecoderModel.h"

void SequenceDecoderModel::init() {
    notesPerTick = model.getMetadata().data[0];
    ticksPerSequence = model.getMetadata().data[1];
    
    if(model.checkType(DECODER_TYPE_PERCUSSION)) {
        uint8_t percussionGroupsSize = model.getMetadata().data[2];
        for (uint8_t i = 0; i < percussionGroupsSize; i++) {
            percussionGroups[i] = model.getMetadata().data[3 + i];
        }
    }

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

Array<OutputNote, MAX_NOTES_OUTPUT>& SequenceDecoderModel::getOutputNotes() {
    notes.clear();
   
    for(uint8_t i = 0; i < notesPerTick; i++) {
        int outputIndex = tickCounter * notesPerTick + i;
        float probability = model.getOutput(outputIndex);
        addNote(i, probability);
    }

    // TODO reorder notes by pitch


    return notes;
}

void SequenceDecoderModel::addNote(uint8_t note, float output) {

    if(!notes.isFull()) {
        notes.add(OutputNote{note, output});
    } else {
        // get index of lowest output probability in list
        uint8_t lowestIndex = 0;
        float lowestProbability = 1;
        for(uint8_t i = 0; i < MAX_NOTES_OUTPUT; i++) {
            if(notes[i].probability < lowestProbability) {
                lowestIndex = i;
                lowestProbability = notes[i].probability;
            }
        }

        // if new note has higher probability then replace it
        if(output > lowestProbability) {
            notes[lowestIndex] = OutputNote{note, output};
        }
    }

}