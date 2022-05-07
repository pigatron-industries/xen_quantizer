#include "TuningController.h"

void TuningController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void TuningController::init() {
    Serial.println("Tuning");
}

void TuningController::update() {
    if(octavePot.update()) {
        octave = octavePot.getIntValue();
    }
}

void TuningController::process() {
    Hardware::hw.cvOutputPins[0]->analogWrite(octave);
    Hardware::hw.cvOutputPins[1]->analogWrite(octave);
    Hardware::hw.cvOutputPins[2]->analogWrite(octave);
    Hardware::hw.cvOutputPins[3]->analogWrite(octave);
}
