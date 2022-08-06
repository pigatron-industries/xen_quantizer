#include "ScaleChordInterface.h"

void ScaleChordInterface::init() {
    page.addComponent(&title);
    // page.addComponent(&outputField);
    // page.addComponent(&voltageField);
    // page.addComponent(&offsetField);

    page.setContext(&Hardware::hw.display);

    page.layout();
}

void ScaleChordInterface::render() {
    Hardware::hw.display.clear();
    page.render();
}
