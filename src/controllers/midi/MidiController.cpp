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
    readMidi();
}

void MidiController::readMidi() {
    int port = 0;
    for (MIDIDevice* midiDevice : Hardware::hw.midiDevice) {
        if (midiDevice->read()) {
            Serial.println("Midi read");
            uint8_t type =       midiDevice->getType();
            uint8_t data1 =      midiDevice->getData1();
            uint8_t data2 =      midiDevice->getData2();
            uint8_t channel =    midiDevice->getChannel();
            // const uint8_t *sys = midiDevice->getSysExArray();
            sendMidi(port, type, data1, data2, channel);
            handleMessage(type, channel-1, data1, data2);
        }
        port++;
    }
    #ifdef USB_MIDI
    if(usbMIDI.read(0)) {
        uint8_t type = usbMIDI.getType();
        uint8_t channel = usbMIDI.getChannel() - 1;
        uint8_t data1 = usbMIDI.getData1();
        uint8_t data2 = usbMIDI.getData2();
        sendMidi(port, type, data1, data2, channel, nullptr);
        handleMessage(type, data1, data2, channel);
    }
    #endif
}

void MidiController::sendMidi(int fromPort, uint8_t type, uint8_t data1, uint8_t data2, uint8_t channel) {
    int port = 0;
    for (MIDIDevice* midiDevice : Hardware::hw.midiDevice) {
        if (port != fromPort) {
            midiDevice->send(type, data1, data2, channel);
        }
        port++;
    }
    #ifdef USB_MIDI
    if (port != fromPort) {
        usbMIDI.send(type, data1, data2, channel);
    }
    #endif
}

void MidiController::process() {
    // trigger input to midi clock
    // if(triggerInputs[0].update() && triggerInputs[0].rose()) {
    //     usbMIDI.sendRealTime(usbMIDI.Clock);
    // }
}

void MidiController::setPitch(uint8_t outputChannel, float pitch) {
    Hardware::hw.cvOutputPins[4+outputChannel]->analogWrite(pitch);
}

void MidiController::setVelocity(uint8_t outputChannel, float velocity) {
    if(velocity > 0) {
        //TODO make velocity range
        velocity = 5;
    } else {
        velocity = 0;
    }
    Hardware::hw.cvOutputPins[outputChannel]->analogWrite(velocity);
}
