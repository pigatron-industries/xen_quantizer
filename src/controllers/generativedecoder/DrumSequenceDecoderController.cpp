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
    for(int i = 0; i < NUM_NOTE_OUTPUTS; i++) {
        // Serial.print(" ");
        // Serial.print(notes[i].note);
        // Serial.print(" ");
        // Serial.print(notes[i].probability);
        if(notes[i].probability > threshold) {
            Serial.print(notes[i].note);
            uint8_t instrument = notes[i].note;
            int8_t output = getOutput(instrument);
            if(output < NUM_TRIGGER_OUTPUTS) {
                triggerOutputs[output].trigger();
            }
            int8_t accentOutput = getAccentOutput(output);
            if(accentOutput >= 0) {
                float accent = getAccent(output, instrument);
                Hardware::hw.cvOutputPins[accentOutput]->analogWrite(accent*2);
            }
        }
    }
}

int8_t DrumSequenceDecoderController::getOutput(uint8_t instrument) {
    if (instrument == 0)
        return 0;
    else if (instrument == 1)
        return 1;
    else if (instrument == 2)
        return 2;
    else if (instrument == 3 || instrument == 4)
        return 3;
    else if (instrument == 5)
        return 4;
    else
        return -1;
}

int8_t DrumSequenceDecoderController::getAccentOutput(int8_t output) {
    if (output == 3)
        return 5;
    else
        return -1;
}

float DrumSequenceDecoderController::getAccent(int8_t output, uint8_t instrument) {
    if(output == 3) {
        if (instrument == 4)
            return 1.0f;
        else
            return 0.0f;
    } else {
        return 0.0f;
    }
}