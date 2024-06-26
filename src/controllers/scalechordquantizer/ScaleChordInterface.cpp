#include "ScaleChordInterface.h"

void ScaleChordInterface::init() {
    page.addComponent(&title);
    page.addComponent(&tuningField);
    page.addComponent(&scaleField);
    page.addComponent(&chordField);
    page.addComponent(&offsetField);
    page.addComponent(&noteVisualiser);

    page.setContext(&Hardware::hw.display);
    page.layout();

    noteVisualiser.setTop(TFTDisplay::HEIGHT - noteVisualiser.getHeight() - 2);

    messageBox.setContext(&Hardware::hw.display);
    messageBox.layout();
}

void ScaleChordInterface::render() {
    Hardware::hw.display.clear();
    page.render();
}

void ScaleChordInterface::setTuningName(char* name) {
    tuningField.setValue(name);
}

void ScaleChordInterface::setTuning(Tuning* tuning) {
    tuningField.setValue(tuning->getName());
    noteVisualiser.setTuning(tuning);
}

void ScaleChordInterface::setScale(Scale* scale) {
    scaleField.setValue(scale->getName());
    noteVisualiser.setScale(scale);
}

void ScaleChordInterface::setChordDef(ChordDef* chordDef) {
    chordField.setValue(chordDef->name);
}

void ScaleChordInterface::setChord(Chord* chord) {
    noteVisualiser.setChord(chord);
}

void ScaleChordInterface::setOffset(int offset) {
    offsetField.setValue(offset);
}

void ScaleChordInterface::focusTuning() {
    focusManager.setFocus(&tuningField);
}

void ScaleChordInterface::focusScale() {
    focusManager.setFocus(&scaleField);
}

void ScaleChordInterface::focusOffset() {
    focusManager.setFocus(&offsetField);
}

void ScaleChordInterface::focusChord() {
    focusManager.setFocus(&chordField);
}

void ScaleChordInterface::showMessage(const char* message) {
    messageBox.showMessage(message);
}