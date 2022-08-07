#include "ScaleChordInterface.h"

void ScaleChordInterface::init() {
    page.addComponent(&title);
    page.addComponent(&tuningField);
    page.addComponent(&scaleField);
    page.addComponent(&chordField);

    page.setContext(&Hardware::hw.display);
    page.layout();
}

void ScaleChordInterface::render() {
    Hardware::hw.display.clear();
    page.render();
}

void ScaleChordInterface::setTuning(const char* tuningName) {
    tuningField.setValue(tuningName);
}

void ScaleChordInterface::setScale(const char* scaleName) {
    scaleField.setValue(scaleName);
}

void ScaleChordInterface::setChord(const char* chordName) {
    chordField.setValue(chordName);
}

void ScaleChordInterface::focusTuning() {
    focusManager.setFocus(&tuningField);
}

void ScaleChordInterface::focusScale() {
    focusManager.setFocus(&scaleField);
}

void ScaleChordInterface::focusChord() {
    focusManager.setFocus(&chordField);
}
