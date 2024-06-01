#include "MidiInterface.h"
#include "MidiProcessor.h"

void MidiInterface::init() {
    page.addComponent(&title);
    page.addComponent(&tuningField);
    page.addComponent(&channelsRow);
    channelsRow.addComponent(&channelFields[0]);
    channelsRow.addComponent(&channelFields[1]);
    channelsRow.addComponent(&channelFields[2]);
    channelsRow.addComponent(&channelFields[3]);

    page.setContext(&Hardware::hw.display);
    page.layout();

    // noteVisualiser.setTop(TFTDisplay::HEIGHT - noteVisualiser.getHeight() - 2);

    messageBox.setContext(&Hardware::hw.display);
    messageBox.layout();
}

void MidiInterface::render() {
    Hardware::hw.display.clear();
    page.render();
}


void MidiInterface::setTuningName(char* name) {
    tuningField.setValue(name);
}

void MidiInterface::setTuning(Tuning* tuning) {
    tuningField.setValue(tuning->getName());
}

void MidiInterface::setChannel(int outputChannel, int midiChannel) {
    switch (midiChannel) {
        case CHANNEL_NONE:
            channelFields[outputChannel].setValue("OFF");
            break;
        case CHANNEL_ALL:
            channelFields[outputChannel].setValue("ALL");
            break;
        default:
            channelFields[outputChannel].setValue(midiChannel);
            break;
    }
}

void MidiInterface::focusTuning() {
    focusManager.setFocus(&tuningField);
}

void MidiInterface::focusChannel(int outputChannel) {
    focusManager.setFocus(&channelFields[outputChannel]);
}

void MidiInterface::showMessage(const char* message) {
    messageBox.showMessage(message);
}