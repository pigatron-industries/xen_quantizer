#include "CalibrationController.h"

void CalibrationController::init(float sampleRate) {
    displayPage.addComponent(&title);
    displayPage.addComponent(&outputField);
    displayPage.addComponent(&voltageField);
    displayPage.addComponent(&offsetField);
    displayPage.setContext(&Hardware::hw.display);
    displayPage.layout();

    ParameterizedController<8>::init(sampleRate);
    init();
}

void CalibrationController::init() {
    Serial.println("Calibration");
    displayPage.render();
    startCalibrate();
}

int CalibrationController::cycleMode(int amount) {
    Serial.println("cycleMode");
    saveCalibration();
    parameters.cycle(amount);
    startCalibrate();
    return parameters.getSelectedIndex();
}

void CalibrationController::cycleValue(int amount) {
    Serial.println("cycleValue");
    if(currentVoltage == 0) {
        calibration.offset(-amount);
    } else {
        calibration.scale(-amount);
    }
    updateOutput();
}

void CalibrationController::update() {
    if(octaveInput.update()) {
        octave = octaveInput.getIntValue();
    }
}

void CalibrationController::startCalibrate() {
    int output = parameters.getSelectedIndex();
    calibration.calibratePin(Hardware::hw.cvOutputPins[output]);

    updateOutput();

    outputField.setValue(output);
}

void CalibrationController::saveCalibration() {
    int output = parameters.getSelectedIndex();
    Hardware::hw.cvOutputPins[output]->saveCalibration();
}

void CalibrationController::updateOutput() {
    int output = parameters.getSelectedIndex();
    uint16_t binaryValue = calibration.convertReverse(currentVoltage);
    Hardware::hw.cvOutputPins[output]->analogWrite(currentVoltage);

    // voltageField.setValue(currentVoltage);
    // offsetField.setValue(binaryValue);
}

void CalibrationController::process() {
}