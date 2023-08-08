#ifndef SequenceDecoderModel_h
#define SequenceDecoderModel_h

#include "TensorflowModel.h"
#include <eurorack.h>

#define MAX_NOTES_OUTPUT 4
#define MAX_PERCUSSION_GROUPS 6

#define DECODER_TYPE_NOTE "seqdec"
#define DECODER_TYPE_PERCUSSION "perdec"

class OutputNote {
    public:
        uint8_t note = 0;
        float probability = 0;
};

class SequenceDecoderModel {

    public:
        SequenceDecoderModel(TensorflowModel& model): model(model) {}
        void init();
        uint8_t getInputSize() { return model.inputSize(); }

        uint8_t getNotesPerTick() { return notesPerTick; }
        uint8_t getTicksPerSequence() { return ticksPerSequence; }
        Array<uint8_t, MAX_PERCUSSION_GROUPS>& getPercussionGroups() { return percussionGroups; }

        uint8_t getTickCounter() { return tickCounter; }
        float getOutputThreshold() { return outputThreshold; }

        uint8_t tick();
        void reset() { tickCounter = -1; } 
        Array<OutputNote, MAX_NOTES_OUTPUT>& getOutputNotes();

    private:
        TensorflowModel& model;

        uint8_t notesPerTick = 0;
        uint8_t ticksPerSequence = 0;
        Array<uint8_t, MAX_PERCUSSION_GROUPS> percussionGroups;

        float outputThreshold = 0.1;

        uint8_t tickCounter = -1;
        Array<OutputNote, MAX_NOTES_OUTPUT> notes;
        // OutputNote notes[MAX_NOTES_OUTPUT];

        void addNote(uint8_t note, float output);
};

#endif
