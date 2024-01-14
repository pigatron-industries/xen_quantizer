#include "CalibrationController.h"

void CalibrationController::init(float sampleRate) {
    ParameterizedController::init(sampleRate);
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
        case Parameter::VALUE:
            interface.focusValue();
            break;
    }

    return parameters.getSelectedIndex(); 
}

void CalibrationController::cycleValue(int amount) {
    parameters.getSelected().cycle(amount);
    switch(parameters.getSelectedIndex()) {
        case Parameter::VALUE:
            setValue(amount);
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

void CalibrationController::setValue(int8_t amount) {
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

    if(channelInput.update()) {
        setOutput(channelInput.getIntValue());
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
    interface.setValue(binaryValue);
    interface.setOffset(calibration.getDigitalOffset());
    interface.setScale(calibration.getDigitalScale());

    // Serial.print(calibration.getDigitalOffset());
    // Serial.print(calibration.getDigitalScale());
}

void CalibrationController::process() {
}