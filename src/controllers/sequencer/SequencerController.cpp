#include "SequencerController.h"

void SequencerController::init(float sampleRate) {
    Controller::init(sampleRate);
    interface.init();
    init();
}

void SequencerController::init() {
    Serial.println("Sequencer");
    interface.render();
}


void SequencerController::update() {
    // Serial.println("update");
}

void SequencerController::process() {
    // Serial.println("process");
}

