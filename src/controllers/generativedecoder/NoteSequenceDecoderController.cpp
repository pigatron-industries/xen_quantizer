#include "NoteSequenceDecoderController.h"


void NoteSequenceDecoderController::decodeOutput(OutputNote* notes) {
    float threshold = thresholdInput.getValue() + thresholdCVInput.getValue();
    // Serial.print("notes: ");
    for(int i = 0; i < NUM_NOTE_OUTPUTS; i++) {
        // Serial.print(" ");
        // Serial.print(notes[i].note);
        // Serial.print(" ");
        // Serial.print(notes[i].probability);
        if(notes[i].probability > threshold) {
            float voltage = notes[i].note * 1.0f / 12.0f;  //TODO convert note number into voltage using scale
            Hardware::hw.cvOutputPins[i]->analogWrite(voltage);
            triggerOutputs[i].trigger(); //TODO gate or trigger?
        }
    }
    // Serial.println();
}