#include "NoteSequenceDecoderController.h"


void NoteSequenceDecoderController::process() {
    for(int i = 0; i < NUM_NOTE_OUTPUTS; i++) {
        triggerOutputs[i].update();
    }

    SequenceDecoderController::process();
}

void NoteSequenceDecoderController::decodeOutput(Array<OutputNote, MAX_NOTES_OUTPUT>& notes) {
    // Serial.print("notes: ");
    for(int i = 0; i < notes.size(); i++) {
        OutputNote& note = notes[i];
        // Serial.print(" ");
        // Serial.print(notes[i].note);
        // Serial.print(" ");
        // Serial.print(notes[i].probability);
        float voltage = note.note * 1.0f / 12.0f;  //TODO convert note number into voltage using scale
        Hardware::hw.cvOutputPins[i+4]->analogWrite(voltage);
        triggerOutputs[i].trigger(); //TODO gate or trigger?
    }
    // Serial.println();
}