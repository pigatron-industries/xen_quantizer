#include "HarmonicWalkController.h"

#define CV_OUTPUT_START 4

void HarmonicWalkController::init(float sampleRate) {
    Controller::init(sampleRate);
    configParam(Parameter::TUNING, 0, Hardware::hw.tuningsManager.getTuningCount()-1);
    interface.init();
    interface.focusTuning();
    setTuning(parameters[Parameter::TUNING].value);
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
    }

    return parameters.getSelectedIndex(); 
}

void HarmonicWalkController::cycleValue(int amount) {
    parameters.getSelected().cycle(amount);
    switch(parameters.getSelectedIndex()) {
        case Parameter::TUNING:
            setTuning(parameters[Parameter::TUNING].value);
            break;
    }

    save();
}

void HarmonicWalkController::update() {
    if(intervalInput.update() || intervalCVInput.update()) {
        float interval = intervalInput.getValue() + intervalCVInput.getValue();
        int intervalNum = int(interval * tuning->size()) % tuning->size() + 1;
        setInterval(intervalNum);
    }
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
    if(this->interval != interval) {
        this->interval = interval;
        interface.setInterval(interval);
    }
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
    Hardware::hw.cvOutputPins[CV_OUTPUT_START]->analogWrite(outputVoltage);
    triggerOutputs[0].trigger();
}
