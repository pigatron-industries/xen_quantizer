#include "SequencerController.h"

void SequencerController::init(float sampleRate) {
    Controller::init(sampleRate);
    modelManager.init();
    interface.init();
    loadModel(0);  //TODO load last used model stored as controller parameter
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

void SequencerController::loadModel(int index) {
    modelManager.loadModel(index);
    if(model.checkType("seqdec")) {
        sequenceDecoderModel.init();
    } else {
        Serial.println("ERROR: unknown model type");
    }
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
    if (sequenceDecoderModel.tick() == 0) {
        runInference();
        Serial.println("inference");
    }

    OutputNote* notes = sequenceDecoderModel.getOutputNotes();
    Serial.print("notes: ");
    for(int i = 0; i < NUM_NOTE_OUTPUTS; i++) {
        Serial.print(" ");
        Serial.print(notes[i].note);
        Serial.print(" ");
        Serial.print(notes[i].probability);
        if(notes[i].probability > sequenceDecoderModel.getOutputThreshold()) {
            float voltage = notes[i].note * 1.0f / 12.0f;  //TODO convert note number into voltage using scale
            Hardware::hw.cvOutputPins[i]->analogWrite(voltage);
            //TODO trigger outputs
        }
    }
    Serial.println();
}


void SequencerController::runInference() {
    latent1Input.update();
    latent2Input.update();
    latent3Input.update();
    model.setInput(0, latent1Input.getValue());
    model.setInput(1, latent2Input.getValue());
    model.setInput(2, latent3Input.getValue());
    Serial.println(latent1Input.getValue());
    Serial.println(latent2Input.getValue());
    Serial.println(latent3Input.getValue());
    model.runInference();
}
