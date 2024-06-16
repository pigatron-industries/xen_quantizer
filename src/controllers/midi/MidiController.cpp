#include "MidiController.h"
#include "MidiConstants.h"


MidiController* MidiController::instance = nullptr;


void MidiController::init(float sampleRate) {
    Controller::init(sampleRate);
    configParam(Parameter::TUNING, 0, Hardware::hw.tuningsManager.getTuningCount()-1, false);
    configParam(Parameter::ROTATECHANNELS, 0, 1);
    interface.init();
    interface.focusTuning();
    for(int outChannel = 0; outChannel < OUTPUT_CHANNELS; outChannel++) {
        uint8_t parameterNum = outChannel + Parameter::CHANNEL0;
        configParam(parameterNum, outChannel, CHANNEL_NONE);
        setOutputChannelParam(outChannel, parameters[parameterNum].value);
        interface.setChannel(outChannel, parameters[parameterNum].value);
    }
    setTuning(parameters[Parameter::TUNING].value);
    setRotateOutputChannels(parameters[Parameter::ROTATECHANNELS].value == 1);
    interface.setRotate(parameters[Parameter::ROTATECHANNELS].value == 1);
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
        case Parameter::ROTATECHANNELS:
            interface.focusRotate();
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
            setOutputChannelParam(parameters.getSelectedIndex() - Parameter::CHANNEL0, value);
            interface.setChannel(parameters.getSelectedIndex() - Parameter::CHANNEL0, value);
            break;
        case Parameter::ROTATECHANNELS:
            setRotateOutputChannels(value == 1);
            interface.setRotate(value == 1);
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
    return tuning->getNoteVoltage(periodNum, noteNum);
}