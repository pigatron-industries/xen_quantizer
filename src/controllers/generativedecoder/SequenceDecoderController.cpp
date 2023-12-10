#include "SequenceDecoderController.h"

#define BTN_PAUSECLOCK 0  // Pause clock until next reset
#define BTN_INFERENCE 2  // Manual inference /  button


void SequenceDecoderController::init(float sampleRate) {
    Controller::init(sampleRate);
    interface.init();
    interface.focusModel();
    init();
}

void SequenceDecoderController::init() {
    Serial.println("Sequence Decoder");
    Hardware::hw.fsModels.cd(modelDir);
    configParam(Parameter::MODEL, 0, Hardware::hw.modelManager.getModelCount()-1);

    // if model doesn't exist reset model parameter to 0
    if(parameters[Parameter::MODEL].value >= Hardware::hw.modelManager.getModelCount()) {
        parameters[Parameter::MODEL].value = 0;
        save();
    }

    if(Hardware::hw.modelManager.getModelCount() > 0) {
        setModel(parameters[Parameter::MODEL].value);
    } else {
        Serial.println("No models found");
    }
    
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
    if(model.checkType("seqdec") || model.checkType("perdec")) {
        sequenceDecoderModel.init();
        tickCounter.setTicksPerSequence(sequenceDecoderModel.getTicksPerSequence());
    } else {
        Serial.println("ERROR: unknown model type");
    }

    interface.setModel(Hardware::hw.modelManager.getName());
    interface.render();
}



void SequenceDecoderController::update() {
    // Press button 1 to pause clock until next reset
    Hardware::hw.pushButtons[BTN_PAUSECLOCK].update();
    if (Hardware::hw.pushButtons[BTN_PAUSECLOCK].pressed()) {
        Serial.println("button 1 press");
        pauseClock = true;
        Hardware::hw.led1OutputPin.digitalWrite(true);
    }

    // Hold button 3 to toggle manual inference mode
    Hardware::hw.pushButtons[BTN_INFERENCE].update();
    if (Hardware::hw.pushButtons[BTN_INFERENCE].heldFor(1000)) {
        Serial.println("button 3 hold");
        manualInference = !manualInference;
        Hardware::hw.led3OutputPin.digitalWrite(manualInference);
    }

    // Press button 3 or send trigger signal while in manual inference mode to run inference
    if(Hardware::hw.pushButtons[BTN_INFERENCE].pressed()) {
        Serial.println("button 3 press");
        if (manualInference) {
            runInference();
        }
    }
}


void SequenceDecoderController::process() {
    if(resetInput.update() && resetInput.rose()) {
        delay(1);
        reset();
    }

    if(clockInput.update() && clockInput.rose() && !pauseClock) {
        delay(1);
        tick();
    }

    if(manualInference && inferenceInput.update() && inferenceInput.rose()) {
        runInference();
    }
}


void SequenceDecoderController::reset() {
    tickCounter.reset();
    pauseClock = false;
    Hardware::hw.led1OutputPin.digitalWrite(false);
    interface.setCurrentTick(tickCounter.getTickCount());
}

void SequenceDecoderController::tick() {
    if(!model.isLoaded()) {
        return;
    }

    tickCounter.tick();

    if (!manualInference && tickCounter.getTickCount() == 0) {
        runInference();
    }

    interface.setCurrentTick(tickCounter.getTickCount());

    OutputNotesSequence& notesSequence = sequenceDecoderModel.getOutputNotesSequence();
    decodeOutput(notesSequence[tickCounter.getTickCount()]);
}


void SequenceDecoderController::runInference() {
    thresholdInput.update();
    thresholdCVInput.update();
    latent1Input.update();
    latent2Input.update();
    latent3Input.update();
    latent1CVInput.update();
    latent2CVInput.update();
    latent3CVInput.update();
    // Serial.println(latent1Input.getValue());
    // Serial.println(latent2Input.getValue());
    // Serial.println(latent3Input.getValue());
    sequenceDecoderModel.setOutputThreshold(thresholdInput.getValue() + thresholdCVInput.getValue());
    model.setInput(0, latent1Input.getValue() + latent1CVInput.getValue());
    model.setInput(1, latent2Input.getValue() + latent2CVInput.getValue());
    model.setInput(2, latent3Input.getValue() + latent3CVInput.getValue());
    model.runInference();

    sequenceDecoderModel.decodeOutput();
    interface.setSequence(&sequenceDecoderModel.getOutputNotesSequence());
}
