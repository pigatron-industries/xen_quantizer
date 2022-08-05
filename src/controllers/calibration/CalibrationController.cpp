#include "CalibrationController.h"

void CalibrationController::init(float sampleRate) {
    Serial.println("init(float sampleRate)");

    displayPage.addComponent(&text1);
    displayPage.addComponent(&text2);
    displayPage.addComponent(&text3);
    displayPage.addComponent(&text4);
    text1.setText("CALIBRRATION");
    text2.setText("OUTPUT:");
    text3.setText("VOLTAGE:");
    text4.setText("OFFSET:");

    displayPage.layout();

    ParameterizedController<8>::init(sampleRate);
    init();
}

void CalibrationController::init() {
    Serial.println("Calibration");
    displayPage.render(Hardware::hw.display);
    startCalibrate();
}

int CalibrationController::cycleMode(int amount) {
    saveCalibration();
    parameters.cycle(amount);
    startCalibrate();
    return parameters.getSelectedIndex();
}

void CalibrationController::cycleValue(int amount) {
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

    //displayPage.setValue(1, output);
}

void CalibrationController::saveCalibration() {
    int output = parameters.getSelectedIndex();
    Hardware::hw.cvOutputPins[output]->saveCalibration();
}

void CalibrationController::updateOutput() {
    int output = parameters.getSelectedIndex();
    uint16_t binaryValue = calibration.convertReverse(currentVoltage);
    Hardware::hw.cvOutputPins[output]->analogWrite(currentVoltage);

    //displayPage.setValue(2, currentVoltage);
    //displayPage.setValue(3, binaryValue);
}

void CalibrationController::process() {
}