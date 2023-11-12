#include "MidiInterface.h"

void MidiInterface::init() {
    page.addComponent(&title);
    // page.addComponent(&noteVisualiser);

    page.setContext(&Hardware::hw.display);
    page.layout();

    // noteVisualiser.setTop(TFTDisplay::HEIGHT - noteVisualiser.getHeight() - 2);
}

void MidiInterface::render() {
    Hardware::hw.display.clear();
    page.render();
}
