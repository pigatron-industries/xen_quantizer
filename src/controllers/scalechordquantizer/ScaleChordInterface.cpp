#include "ScaleChordInterface.h"

void ScaleChordInterface::init() {
    page.addComponent(&title);
    page.addComponent(&tuningField);
    page.addComponent(&scaleField);
    page.addComponent(&chordField);
    page.addComponent(&noteVisualiser);

    page.setContext(&Hardware::hw.display);
    page.layout();
}

void ScaleChordInterface::render() {
    Hardware::hw.display.clear();
    page.render();
}

void ScaleChordInterface::setTuning(Tuning* tuning) {
    tuningField.setValue(tuning->getName());
    noteVisualiser.setTuning(tuning);
}

void ScaleChordInterface::setScale(Scale* scale) {
    scaleField.setValue(scale->getName());
    noteVisualiser.setScale(scale);
}

void ScaleChordInterface::setChord(ChordDef* chordDef) {
    chordField.setValue(chordDef->name);
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
