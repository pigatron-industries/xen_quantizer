#include "DrumSequenceDecoderController.h"


void DrumSequenceDecoderController::decodeOutput(OutputNote* notes) {
    float threshold = thresholdInput.getValue() + thresholdCVInput.getValue();
    // Serial.print("notes: ");
    for(int i = 0; i < NUM_NOTE_OUTPUTS; i++) {
        // Serial.print(" ");
        // Serial.print(notes[i].note);
        // Serial.print(" ");
        // Serial.print(notes[i].probability);
        if(notes[i].probability > threshold) {
            uint8_t note = notes[i].note;
            if(note < NUM_NOTE_OUTPUTS) {
                triggerOutputs[note].trigger();
            }
        }
    }
    // Serial.println();
}