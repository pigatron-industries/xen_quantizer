#include "SequencerInterface.h"

void SequencerInterface::init() {
    page.addComponent(&title);
    page.addComponent(&modelField);

    page.setContext(&Hardware::hw.display);

    page.layout();
}

void SequencerInterface::render() {
    Hardware::hw.display.clear();
    page.render();
}

void SequencerInterface::setModel(char* modelName) {
    modelField.setValue(modelName);
}

void SequencerInterface::focusModel() {
    focusManager.setFocus(&modelField);
}