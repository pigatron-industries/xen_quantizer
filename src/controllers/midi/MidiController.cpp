#include "MidiController.h"
#include "MidiConstants.h"


void MidiController::init(float sampleRate) {
    Controller::init(sampleRate);
    interface.init();
    init();
}

void MidiController::init() {
    Serial.println("Midi");
    interface.render();
}

void MidiController::update() {
    if(Hardware::hw.midiDevice.read(0)) {
        byte command = HI_NYBBLE(Hardware::hw.midiDevice.getType());
        byte channel = Hardware::hw.midiDevice.getChannel() - 1;
        byte data1 = Hardware::hw.midiDevice.getData1();
        byte data2 = Hardware::hw.midiDevice.getData2();
        handleMessage(command, channel, data1, data2);
    }
}

void MidiController::process() {
}

void MidiController::setPitch(uint8_t outputChannel, float pitch) {
    Hardware::hw.cvOutputPins[4+outputChannel]->analogWrite(pitch);
}

void MidiController::setVelocity(uint8_t outputChannel, float velocity) {
    Hardware::hw.cvOutputPins[outputChannel]->analogWrite(velocity);
}
