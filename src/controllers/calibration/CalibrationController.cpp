#include "CalibrationController.h"

void CalibrationController::init(float sampleRate) {
    ParameterizedController<8>::init(sampleRate);
    interface.init();
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
    Serial.println("cycleParameter");
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
        currentVoltage = octaveInput.getIntValue();
        updateOutput();
    }
}

void CalibrationController::startCalibrate() {
    int output = parameters.getSelectedIndex();
    calibration.calibratePin(Hardware::hw.cvOutputPins[output]);

    updateOutput();

    interface.setOutput(output);
}

void CalibrationController::saveCalibration() {
    int output = parameters.getSelectedIndex();
    Hardware::hw.cvOutputPins[output]->saveCalibration();
}

void CalibrationController::updateOutput() {
    int output = parameters.getSelectedIndex();
    uint16_t binaryValue = calibration.convertReverse(currentVoltage);
    Hardware::hw.cvOutputPins[output]->analogWrite(currentVoltage);

    interface.setVoltage(currentVoltage);
    interface.setOffset(binaryValue);
}

void CalibrationController::process() {
}