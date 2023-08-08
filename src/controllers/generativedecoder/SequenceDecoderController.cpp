#include "SequenceDecoderController.h"


void SequenceDecoderController::init(float sampleRate) {
    Controller::init(sampleRate);
    interface.init();
    interface.focusModel();
    init();
}

void SequenceDecoderController::init() {
    Serial.println("Gen Note Decoder");
    Hardware::hw.fsModels.cd(modelDir);
    configParam(Parameter::MODEL, 0, Hardware::hw.modelManager.getModelCount()-1);
    setModel(parameters[Parameter::MODEL].value);
    interface.render();
}

int SequenceDecoderController::cycleParameter(int amount) {
    parameters.cycle(amount);
    switch(parameters.getSelectedIndex()) {
        case Parameter::MODEL:
            interface.focusModel();
            break;
    }

    return parameters.getSelectedIndex(); 
}

void SequenceDecoderController::cycleValue(int amount) {
    parameters.getSelected().cycle(amount);
    switch(parameters.getSelectedIndex()) {
        case Parameter::MODEL:
            setModel(parameters[Parameter::MODEL].value);
            break;
    }

    save();
}

void SequenceDecoderController::setModel(int index) {
    Serial.print("setModel:");
    Serial.println(index);
    Hardware::hw.modelManager.loadModel(index);
    if(model.checkType("seqdec")) {
        sequenceDecoderModel.init();
    } else if(model.checkType("perdec")) {
        sequenceDecoderModel.init();
    } else {
        Serial.println("ERROR: unknown model type");
    }

    interface.setModel(model.getName());
    interface.render();
}

void SequenceDecoderController::update() {

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


void SequenceDecoderController::process() {
    if(resetInput.update() && resetInput.rose()) {
        delay(1);
        reset();
    }

    if(clockInput.update() && clockInput.rose()) {
        delay(1);
        tick();
    }
}


void SequenceDecoderController::reset() {
    sequenceDecoderModel.reset();
}

void SequenceDecoderController::tick() {
    thresholdInput.update();
    thresholdCVInput.update();

    if (sequenceDecoderModel.tick() == 0) {
        runInference();
        // Serial.println("inference");
    }

    Array<OutputNote, MAX_NOTES_OUTPUT>& notes = sequenceDecoderModel.getOutputNotes();
    decodeOutput(notes);
}


void SequenceDecoderController::runInference() {
    latent1Input.update();
    latent2Input.update();
    latent3Input.update();
    latent1CVInput.update();
    latent2CVInput.update();
    latent3CVInput.update();
    // Serial.println(latent1Input.getValue());
    // Serial.println(latent2Input.getValue());
    // Serial.println(latent3Input.getValue());
    model.setInput(0, latent1Input.getValue() + latent1CVInput.getValue());
    model.setInput(1, latent2Input.getValue() + latent2CVInput.getValue());
    model.setInput(2, latent3Input.getValue() + latent3CVInput.getValue());
    model.runInference();
}