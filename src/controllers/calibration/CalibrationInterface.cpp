#include "CalibrationInterface.h"

void CalibrationInterface::init() {
    page.addComponent(&title);
    page.addComponent(&outputField);
    page.addComponent(&voltageField);
    page.addComponent(&valueField);
    page.addComponent(&offsetField);
    page.addComponent(&scaleField);
    page.addComponent(&outputVisualiser);

    page.setContext(&Hardware::hw.display);

    page.layout();
}

void CalibrationInterface::render() {
    Hardware::hw.display.clear();
    page.render();
}

void CalibrationInterface::setOutput(int output) {
    outputField.setValue(output);
    outputVisualiser.setSelectedOutput(output);
}

void CalibrationInterface::setVoltage(int voltage) {
    voltageField.setValue(voltage);
}

void CalibrationInterface::setValue(int offset) {
    valueField.setValue(offset);
}

void CalibrationInterface::setOffset(int offset) {
    offsetField.setValue(offset);
}

void CalibrationInterface::setScale(int scale) {
    scaleField.setValue(scale);
}

void CalibrationInterface::focusOutput() {
    focusManager.setFocus(&outputField);
}

void CalibrationInterface::focusVoltage() {
    focusManager.setFocus(&voltageField);
}

void CalibrationInterface::focusValue() {
    focusManager.setFocus(&valueField);
}