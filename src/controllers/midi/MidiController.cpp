#include "MidiController.h"
#include "MidiConstants.h"


void MidiController::init(float sampleRate) {
    Controller::init(sampleRate);
    configParam(Parameter::TUNING, 0, Hardware::hw.tuningsManager.getTuningCount()-1, false);
    interface.init();
    interface.focusTuning();
    for(int outChannel = 0; outChannel < OUTPUT_CHANNELS; outChannel++) {
        uint8_t parameterNum = outChannel + Parameter::CHANNEL0;
        configParam(parameterNum, outChannel, CHANNEL_NONE);
        setOutputChannel(outChannel, parameters[parameterNum].value);
        interface.setChannel(outChannel, parameters[parameterNum].value);
    }
    setTuning(parameters[Parameter::TUNING].value);
    init();
}

void MidiController::init() {
    Serial.println("Midi");
    interface.render();
}

int MidiController::cycleParameter(int amount) {
    parameters.cycle(amount);
    switch(parameters.getSelectedIndex()) {
        case Parameter::TUNING:
            interface.focusTuning();
            break;
        case Parameter::CHANNEL0:
        case Parameter::CHANNEL1:
        case Parameter::CHANNEL2:
        case Parameter::CHANNEL3:
            interface.focusChannel(parameters.getSelectedIndex() - Parameter::CHANNEL0);
            break;
    }
    return parameters.getSelectedIndex();
}

void MidiController::cycleValue(int amount) {
    int value = parameters.getSelected().cycle(amount);
    switch(parameters.getSelectedIndex()) {
        case Parameter::TUNING: {
            FileInfo& file = Hardware::hw.tuningsManager.getFileInfo(value);
            interface.setTuningName(file.filename);
            break;
        }
        case Parameter::CHANNEL0:
        case Parameter::CHANNEL1:
        case Parameter::CHANNEL2:
        case Parameter::CHANNEL3:
            setOutputChannel(parameters.getSelectedIndex() - Parameter::CHANNEL0, value);
            interface.setChannel(parameters.getSelectedIndex() - Parameter::CHANNEL0, value);
            break;
    }
    save();
}

void MidiController::selectValue() {
    int prevValue = parameters.getSelected().getValue();
    int newValue = parameters.getSelected().select();
    switch(parameters.getSelectedIndex()) {
        case Parameter::TUNING:
            if (newValue != prevValue) {
                setTuning(newValue);
            } else {
                interface.setTuning(tuning);
            }
            break;
    }
}

void MidiController::setTuning(int index) {
    interface.showMessage("Loading");

    tuningData = &Hardware::hw.tuningsManager.loadTuningData(index);
    tuning = tuningData->tuning;

    Serial.print("Tuning: ");
    Serial.println(tuning->getName());
    interface.setTuning(tuning);

    interface.render();
}


void MidiController::update() {
    readMidi();
}

void MidiController::readMidi() {
    int port = 0;
    for (MIDIDevice* midiDevice : Hardware::hw.midiDevice) {
        if (midiDevice->read()) {
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

float MidiController::convertNote(int8_t note) {
    int periodNum = note / tuning->size();
    int noteNum = note - (periodNum * tuning->size());
    return tuning->getNoteVoltage(periodNum, noteNum) - 5;
}