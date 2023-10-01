#include "CalibrationController.h"

void CalibrationController::init(float sampleRate) {
    ParameterizedController::init(sampleRate);
    configParam(Parameter::OUTPUTNUM, 0, 7);
    interface.init();
    interface.focusOutput();
    init();
}

void CalibrationController::init() {
    Serial.println("Calibration");
    for(int i = 0; i < 8; i++) {
        Hardware::hw.cvOutputPins[i]->analogWrite(0);
    }

    interface.render();
    startCalibrate();
}

int CalibrationController::cycleParameter(int amount) {
    parameters.cycle(amount);

    switch(parameters.getSelectedIndex()) {
        case Parameter::OUTPUTNUM:
            interface.focusOutput();
            break;
        case Parameter::VOLTAGE:
            interface.focusVoltage();
            break;
        case Parameter::OFFSET:
            interface.focusOffset();
            break;
    }

    return parameters.getSelectedIndex(); 
}

void CalibrationController::cycleValue(int amount) {
    parameters.getSelected().cycle(amount);
    switch(parameters.getSelectedIndex()) {
        case Parameter::OUTPUTNUM:
            setOutput(parameters[Parameter::OUTPUTNUM].value);
            break;
        case Parameter::VOLTAGE:
            //TODO set voltage from encoder
            break;
        case Parameter::OFFSET:
            setOffset(amount);
            break;
    }
}

void CalibrationController::selectValue() {
    Serial.println("Reset");
    calibration.reset();
    startCalibrate();
}

void CalibrationController::setOutput(uint8_t output) {
    saveCalibration();
    currentOutput = output;
    startCalibrate();
}

void CalibrationController::setOffset(int8_t amount) {
    if(currentVoltage == 0) {
        calibration.offset(-amount);
    } else {
        calibration.scale(-amount);
    }
    updateOutput();
}

void CalibrationController::update() {
    if(octaveInput.update()) {
        currentVoltage = octaveInput.getIntValue();
        updateOutput();
    }
}

void CalibrationController::startCalibrate() {
    calibration.calibratePin(Hardware::hw.cvOutputPins[currentOutput]);
    updateOutput();
    interface.setOutput(currentOutput);
}

void CalibrationController::saveCalibration() {
    Hardware::hw.cvOutputPins[currentOutput]->saveCalibration();
}

void CalibrationController::updateOutput() {
    uint16_t binaryValue = calibration.convertReverse(currentVoltage);
    Hardware::hw.cvOutputPins[currentOutput]->analogWrite(currentVoltage);
    interface.setVoltage(currentVoltage);
    interface.setOffset(binaryValue);
}

void CalibrationController::process() {
}