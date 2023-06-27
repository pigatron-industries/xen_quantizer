#ifndef SequenceDecoderModel_h
#define SequenceDecoderModel_h

#include "TensorflowModel.h"

#define MAX_NOTES_OUTPUT 4

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
        uint8_t getTickCounter() { return tickCounter; }
        float getOutputThreshold() { return outputThreshold; }

        uint8_t tick();
        OutputNote* getOutputNotes();

    private:
        TensorflowModel& model;

        uint8_t notesPerTick = 0;
        uint8_t ticksPerSequence = 0;

        float outputThreshold = 0.1;

        uint8_t tickCounter = -1;
        OutputNote notes[MAX_NOTES_OUTPUT];

        void addNote(uint8_t note, float output);
};

#endif
