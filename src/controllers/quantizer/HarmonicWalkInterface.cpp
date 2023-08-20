#include "HarmonicWalkInterface.h"

void HarmonicWalkInterface::init() {
    page.addComponent(&title);
    page.addComponent(&tuningField);
    page.addComponent(&intervalField);

    page.setContext(&Hardware::hw.display);
    page.layout();

    messageBox.setContext(&Hardware::hw.display);
    messageBox.layout();
}

void HarmonicWalkInterface::render() {
    Hardware::hw.display.clear();
    page.render();
}

void HarmonicWalkInterface::setTuning(Tuning* tuning) {
    tuningField.setValue(tuning->getName());
}

void HarmonicWalkInterface::setInterval(int interval) {
    intervalField.setValue(interval);
}

void HarmonicWalkInterface::focusTuning() {
    focusManager.setFocus(&tuningField);
}

void HarmonicWalkInterface::focusInterval() {
    focusManager.setFocus(&intervalField);
}

void HarmonicWalkInterface::showMessage(const char* message) {
    messageBox.showMessage(message);
}