#include "SequenceDecoderInterface.h"

void SequenceDecoderInterface::init() {
    page.addComponent(&title);
    page.addComponent(&modelField);
    page.addComponent(&sequenceVisualiser);

    page.setContext(&Hardware::hw.display);

    page.layout();

    sequenceVisualiser.setTop(TFTDisplay::HEIGHT - sequenceVisualiser.getHeight());
}

void SequenceDecoderInterface::render() {
    Hardware::hw.display.clear();
    page.render();
}

void SequenceDecoderInterface::setModel(char* modelName) {
    modelField.setValue(modelName);
}

void SequenceDecoderInterface::setSequence(OutputNotesSequence* sequence) {
    sequenceVisualiser.setSequence(sequence);
}

void SequenceDecoderInterface::setCurrentTick(int8_t tick) {
    sequenceVisualiser.setCurrentTick(tick);
}

void SequenceDecoderInterface::focusModel() {
    focusManager.setFocus(&modelField);
}