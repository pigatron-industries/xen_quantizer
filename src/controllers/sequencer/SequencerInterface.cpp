#include "SequencerInterface.h"

void SequencerInterface::init() {
    page.addComponent(&title);

    page.setContext(&Hardware::hw.display);

    page.layout();
}

void SequencerInterface::render() {
    Hardware::hw.display.clear();
    page.render();
}
