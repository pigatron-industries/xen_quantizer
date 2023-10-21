#include "SequencerInterface.h"

void SequencerInterface::init() {
    page.addComponent(&title);
    page.addComponent(&modelField);
    page.addComponent(&sequenceVisualiser);

    page.setContext(&Hardware::hw.display);

    page.layout();

    sequenceVisualiser.setTop(TFTDisplay::HEIGHT - sequenceVisualiser.getHeight() - 2);
}

void SequencerInterface::render() {
    Hardware::hw.display.clear();
    page.render();
}

void SequencerInterface::setModel(char* modelName) {
    modelField.setValue(modelName);
}

void SequencerInterface::setSequence(OutputNotesSequence* sequence) {
    sequenceVisualiser.setSequence(sequence);
}

void SequencerInterface::focusModel() {
    focusManager.setFocus(&modelField);
}