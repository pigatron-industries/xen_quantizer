#include "SequenceDecoderModel.h"

#define BYTE_NOTE_PER_TICK 0
#define BYTE_TICKS_PER_SEQUENCE 1
#define BYTE_LATENT_SCALE 2
#define BYTE_PERCUSSION_GROUPS_SIZE 3
#define BYTE_PERCUSSION_GROUPS 4

void SequenceDecoderModel::init() {
    notesPerTick = model.getMetadata().data[BYTE_NOTE_PER_TICK];
    ticksPerSequence = model.getMetadata().data[BYTE_TICKS_PER_SEQUENCE];
    
    percussionGroups.clear();
    if(model.checkType(DECODER_TYPE_PERCUSSION)) {
        uint8_t percussionGroupsSize = model.getMetadata().data[BYTE_PERCUSSION_GROUPS_SIZE];
        uint8_t groupStart = 0;
        for (uint8_t i = 0; i < percussionGroupsSize; i++) {
            uint8_t groupSize = model.getMetadata().data[BYTE_PERCUSSION_GROUPS + i];
            Serial.print("groupStart: ");
            Serial.println(groupStart);
            Serial.print("groupSize: ");
            Serial.println(groupSize);
            percussionGroups.add(PercussionGroup{groupStart, groupSize});
            groupStart += groupSize;
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

int8_t SequenceDecoderModel::getPercussionGroupIndex(uint8_t note) {
    for(uint8_t i = 0; i < percussionGroups.size(); i++) {
        PercussionGroup group = percussionGroups[i];
        if(note >= group.start && note < group.start + group.size) {
            return i;
        }
    }
    return -1;
}

PercussionGroup& SequenceDecoderModel::getPercussionGroup(uint8_t index) {
    return percussionGroups[index];
}

float SequenceDecoderModel::getPercussionGroupAccent(uint8_t groupIndex, uint8_t note) {
    PercussionGroup& group = percussionGroups[groupIndex];
    uint8_t groupOffset = note - group.start;
    return groupOffset / (group.size-1);
}