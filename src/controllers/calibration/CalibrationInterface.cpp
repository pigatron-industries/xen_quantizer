#include "CalibrationInterface.h"

void CalibrationInterface::init() {
    page.addComponent(&title);
    page.addComponent(&outputField);
    page.addComponent(&voltageField);
    page.addComponent(&offsetField);

    page.setContext(&Hardware::hw.display);

    page.layout();
}

void CalibrationInterface::render() {
    Hardware::hw.display.clear();
    page.render();
}

void CalibrationInterface::setOutput(int output) {
    outputField.setValue(output);
}

void CalibrationInterface::setVoltage(int voltage) {
    voltageField.setValue(voltage);
}

void CalibrationInterface::setOffset(int offset) {
    offsetField.setValue(offset);
}

void CalibrationInterface::focusOutput() {
    focusManager.setFocus(&outputField);
}

void CalibrationInterface::focusVoltage() {
    focusManager.setFocus(&voltageField);
}

void CalibrationInterface::focusOffset() {
    focusManager.setFocus(&offsetField);
}