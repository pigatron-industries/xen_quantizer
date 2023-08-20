#include "HarmonicWalkController.h"

void HarmonicWalkController::init(float sampleRate) {
    Controller::init(sampleRate);
    configParam(Parameter::TUNING, 0, Hardware::hw.tuningsManager.getTuningCount()-1);
    configParam(Parameter::INTERVAL, 1, 7);
    interface.init();
    interface.focusTuning();
    setTuning(parameters[Parameter::TUNING].value);
    setInterval(parameters[Parameter::INTERVAL].value);
    init();
}

void HarmonicWalkController::init() {
    Serial.println("Harmonic Walk");
    interface.render();
}

int HarmonicWalkController::cycleParameter(int amount) {
    parameters.cycle(amount);

    switch(parameters.getSelectedIndex()) {
        case Parameter::TUNING:
            interface.focusTuning();
            break;
        case Parameter::INTERVAL:
            interface.focusInterval();
            break;
    }

    return parameters.getSelectedIndex(); 
}

void HarmonicWalkController::cycleValue(int amount) {
    parameters.getSelected().cycle(amount);
    switch(parameters.getSelectedIndex()) {
        case Parameter::TUNING:
            setTuning(parameters[Parameter::TUNING].value);
            break;
        case Parameter::INTERVAL:
            setInterval(parameters[Parameter::INTERVAL].value);
            break;
    }

    save();
}

void HarmonicWalkController::update() {
}

void HarmonicWalkController::setTuning(int index) {
    interface.showMessage("Loading");

    tuningData = &Hardware::hw.tuningsManager.loadTuningData(index);
    tuning = tuningData->tuning;
    quantizer.setTuning(*tuning);

    Serial.print("Tuning: ");
    Serial.println(tuning->getName());
    interface.setTuning(tuning);
    interface.render();
}

void HarmonicWalkController::setInterval(int interval) {
    this->interval = interval;
    interface.setInterval(interval);
}

void HarmonicWalkController::process() {
    for(int i = 0; i < NUM_TRIGGER_OUTPUTS; i++) {
        triggerOutputs[i].update();
    }

    if(triggerInputs[0].update() && triggerInputs[0].rose()) {
        delay(1);
        clock();
    }
}

void HarmonicWalkController::clock() {
    float inputVoltage = Hardware::hw.channel1InputPin.analogRead();
    outputVoltage = quantizer.quantize(outputVoltage, inputVoltage, interval);
    Hardware::hw.cvOutputPins[0]->analogWrite(outputVoltage);
    triggerOutputs[0].trigger();
}
