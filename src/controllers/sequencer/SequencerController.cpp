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

int SequencerController::cycleMode(int amount) {
    parameters.cycle(amount);
    return parameters.getSelectedIndex(); 
}

void SequencerController::cycleValue(int amount) {
    parameters.getSelected().cycle(amount);
}

void SequencerController::update() {

    if(Hardware::hw.pushButtons[0].update()) {
        if(Hardware::hw.pushButtons[0].pressed()) {
            Serial.println("button 1 press");
            Hardware::hw.led1OutputPin.digitalWrite(!Hardware::hw.led1OutputPin.getDigitalValue());
        } else if(Hardware::hw.pushButtons[0].released()) {

        }
    }

    if(Hardware::hw.pushButtons[1].update() && Hardware::hw.pushButtons[1].pressed()) {
        Serial.println("button 2 press");
        Hardware::hw.led2OutputPin.digitalWrite(!Hardware::hw.led2OutputPin.getDigitalValue());
    }

    if(Hardware::hw.pushButtons[2].update() && Hardware::hw.pushButtons[2].pressed()) {
        Serial.println("button 3 press");
        Hardware::hw.led3OutputPin.digitalWrite(!Hardware::hw.led3OutputPin.getDigitalValue());
    }

    if(Hardware::hw.pushButtons[3].update() && Hardware::hw.pushButtons[3].pressed()) {
        Serial.println("button 4 press");
        Hardware::hw.led4OutputPin.digitalWrite(!Hardware::hw.led4OutputPin.getDigitalValue());
    }
}


void SequencerController::process() {
    if(triggerInputs[0].update() && triggerInputs[0].rose()) {
        delay(1);
        tick();
    }
}


void SequencerController::tick() {
    // Hardware::hw.cvOutputPins[0]->analogWrite(chord[0].voltage + transpose);
    // Hardware::hw.cvOutputPins[1]->analogWrite(chord[1].voltage + transpose);
    // Hardware::hw.cvOutputPins[2]->analogWrite(chord[2].voltage + transpose);
}
