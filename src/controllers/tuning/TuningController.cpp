#include "TuningController.h"

void TuningController::init(float sampleRate) {
    Serial.println("init(float sampleRate)");

    displayPage.addComponent(&text1);
    //displayPage.addComponent(&text2);
    text1.setText("TEST");

    Controller::init(sampleRate);
    init();
}

void TuningController::init() {
    Serial.println("Tuning");
    displayPage.render(Hardware::hw.display);
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
