#include "DrumSequenceDecoderController.h"


void DrumSequenceDecoderController::process() {
    for(int i = 0; i < NUM_TRIGGER_OUTPUTS; i++) {
        triggerOutputs[i].update();
    }

    SequenceDecoderController::process();
}

void DrumSequenceDecoderController::decodeOutput(Array<OutputNote, MAX_NOTES_OUTPUT>& notes) {
    float threshold = thresholdInput.getValue() + thresholdCVInput.getValue();
    // Serial.print("notes: ");
    for(int i = 0; i < notes.size(); i++) {
        OutputNote& note = notes[i];
        // Serial.print(" ");
        // Serial.print(notes[i].note);
        // Serial.print(" ");
        // Serial.print(notes[i].probability);
        int8_t output = getOutput(note.note);
        if(output < NUM_TRIGGER_OUTPUTS) {
            triggerOutputs[output].trigger();
        }
        int8_t accentOutput = getAccentOutput(output);
        if(accentOutput >= 0) {
            float accent = getAccent(output, note.note);
            Hardware::hw.cvOutputPins[accentOutput]->analogWrite(accent*3);
        }
    }

    // Serial.println();
}

int8_t DrumSequenceDecoderController::getOutput(uint8_t note) {
    return sequenceDecoderModel.getPercussionGroupIndex(note);
}

int8_t DrumSequenceDecoderController::getAccentOutput(int8_t output) {
    // hard coded for now
    if (output == 2)
        return 5;
    else if (output == 3)
        return 6;
    else if (output == 4)
        return 7;
    else
        return -1;
}

float DrumSequenceDecoderController::getAccent(int8_t output, uint8_t note) {
    return sequenceDecoderModel.getPercussionGroupAccent(output, note);
}