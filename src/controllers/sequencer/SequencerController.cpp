#include "SequencerController.h"

#include "controllers/midi/MidiController.h"


void SequencerController::init(float sampleRate) {
    Controller::init(sampleRate);
    interface.init();
    interface.setSequencer(&sequencer);
    init();
}

void SequencerController::init() {
    Serial.println("Sequencer");
    interface.render();
    // TODO get parameters from MidiController and use them to set up midi processor for sequencer
    // MidiController::getInstance()->getParameterValue(MidiController::ROTATECHANNELS);
}


void SequencerController::update() {
    for(int i = 0; i < NUM_TRACKS; i++) {
        Hardware::hw.pushButtons[i].update();
        if (Hardware::hw.pushButtons[i].released() && Hardware::hw.pushButtons[i].previousDuration() < 2000) {
            recording[i] = !recording[i];
            Hardware::hw.ledOutputPins[i]->digitalWrite(recording[i]);
        } else if (Hardware::hw.pushButtons[i].heldFor(2000)) {
            sequencer.clearTrack(i);
            interface.render();
        }
    }
}

void SequencerController::process() {    
    bool triggers[4];
    bool anyTriggers = false;
    for(int i = 0; i < NUM_TRACKS; i++) {
        triggers[i] = triggerInputs[i].update() && triggerInputs[i].rose();
        anyTriggers = anyTriggers || triggers[i];
        if (triggers[i]) {
            recordInputValue(i);
        }
    }
    if (anyTriggers) { // delay to allow for delays in cv input
        delay(1);
    }

    if (resetInput.update() && resetInput.isTriggeredOn()) {
        reset();
        delay(1);
    }

    if (clockInput.update() && clockInput.isTriggeredOn()) {
        tick();
        delay(1);
    }
}

void SequencerController::reset() {
    sequencer.reset();
    interface.setCurrentTick(sequencer.getCurrentStep());
}

void SequencerController::tick() {
    sequencer.tick();
    interface.setCurrentTick(sequencer.getCurrentStep());

    for(int i = 0; i < NUM_TRACKS; i++) {
        if(triggerInputs[i].getValue()) {
            recordInputValue(i);
        } else {
            outputSequenceValue(i);
        }
    }
}

void SequencerController::recordInputValue(int channel) {
    valueInputs[channel].update();
    float value = valueInputs[channel].getVoltage();

    if(recording[channel]) {
        sequencer.getStep(channel, sequencer.getCurrentStep()).voltage = value;
        sequencer.getStep(channel, sequencer.getCurrentStep()).trigger = true;
        interface.render();
    }

    gateOutputs[channel].gate(true);
    Hardware::hw.cvOutputPins[channel+4]->analogWrite(value);
}

void SequencerController::outputSequenceValue(int channel) {
    SequenceStep& step = sequencer.getTrack(channel).get(sequencer.getCurrentStep());
    if(step.trigger) {
        gateOutputs[channel].gate(true);
        Hardware::hw.cvOutputPins[channel+4]->analogWrite(step.voltage);
    } else {
        gateOutputs[channel].gate(false);
    }
}

