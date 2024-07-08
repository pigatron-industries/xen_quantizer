#include "SequencerController.h"

#include "controllers/midi/MidiController.h"


void SequencerController::init(float sampleRate) {
    Controller::init(sampleRate);
    configParam(Parameter::PATTERN, 0, NUM_PATTERNS-1, false);
    interface.init();
    interface.setPattern(parameters[Parameter::PATTERN].getValue());
    sequencer.setCurrentPattern(parameters[Parameter::PATTERN].getValue());
    interface.setSequencer(&sequencer);
    if(!MidiController::getInstance()->isInited()) {
        MidiController::getInstance()->init(sampleRate);
    }
    init();
}

void SequencerController::init() {
    Serial.println("Sequencer");
    interface.render();
    // copy settings from MidiController
    setRotateOutputChannels(MidiController::getInstance()->getRotateOutputChannels());
    for(int outChannel = 0; outChannel < OUTPUT_CHANNELS; outChannel++) {
        setOutputChannelParam(outChannel, MidiController::getInstance()->getOutputChannelParam(outChannel));
    }
}


int SequencerController::cycleParameter(int amount) {
    parameters.cycle(amount);

    switch(parameters.getSelectedIndex()) {
        case Parameter::PATTERN:
            interface.focusPattern();
            break;
    }

    return parameters.getSelectedIndex();
}


void SequencerController::cycleValue(int amount) {
    int value = parameters.getSelected().cycle(amount);
    switch(parameters.getSelectedIndex()) {
        case Parameter::PATTERN:
            sequencer.setCurrentPattern(value);
            interface.setPattern(value);
            break;
    }
}


void SequencerController::update() {
    readMidi();

    for(int i = 0; i < NUM_TRACKS; i++) {
        Hardware::hw.pushButtons[i].update();
        if (Hardware::hw.pushButtons[i].released() && Hardware::hw.pushButtons[i].previousDuration() < 2000) {
            recording[i] = !recording[i];
            Hardware::hw.ledOutputPins[i]->digitalWrite(recording[i]);
            SequenceStepEvent event;
            recordedEvents[i].clear();
            recordedEvents[i].add(event);
        } else if (Hardware::hw.pushButtons[i].heldFor(2000)) {
            sequencer.clearTrack(i);
            interface.render();
        }
    }
}

void SequencerController::setPitch(uint8_t outputChannel, float pitch) {
    if(getOutputChannelState(outputChannel).noteOn()) {
        recordEvent(outputChannel);
    }
}

void SequencerController::setVelocity(uint8_t outputChannel, float velocity) {
    if(velocity > 0) {
        recordEvent(outputChannel);
    }
}


void SequencerController::process() {
    sampleCounter++;
    bool triggersOn[4];
    bool anyTriggers = false;
    for(int i = 0; i < NUM_TRACKS; i++) {
        triggersOn[i] = triggerInputs[i].update() && triggerInputs[i].rose();
        bool triggerOff = triggerInputs[i].update() && triggerInputs[i].fell();
        anyTriggers = anyTriggers || triggersOn[i];
        if (triggersOn[i] || triggerOff) {
            recordEvent(i);
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
    prevStep = sequencer.getCurrentStep();
    sequencer.reset();
    interface.setCurrentTick(sequencer.getCurrentStep());
}

void SequencerController::tick() {
    if(sequencer.getCurrentStep() >= 0) {
        prevStep = sequencer.getCurrentStep();
    }
    sequencer.tick();
    interface.setCurrentTick(sequencer.getCurrentStep());

    for(int i = 0; i < NUM_TRACKS; i++) {
        recordEvent(i);
        quantizeEvents(i);
        if(!triggerInputs[i].getValue() && !getOutputChannelState(i).noteOn()) {
            outputSequenceStep(i);
        }
    }

    sampleCounter = 0;
}

float SequencerController::getInputValue(int channel) {
    float value = 0;
    if(getOutputChannelState(channel).noteOn()) {
        value = getOutputChannelState(channel).pitch;
    } else {
        valueInputs[channel].update();
        value = valueInputs[channel].getVoltage();
    }
    return value;
}

void SequencerController::recordEvent(int channel) {
    bool gate = triggerInputs[channel].getValue() || getOutputChannelState(channel).noteOn();
    float value = getInputValue(channel);

    if(recording[channel]) {
        SequenceStepEvent& prevEvent = recordedEvents[channel].get(-1);

        // if(gate == prevEvent.step.gate) {
        //     prevEvent.step.voltage = value;
        // } else {
            SequenceStepEvent newEvent;
            newEvent.time = sampleCounter;
            newEvent.step.gate = gate;
            newEvent.step.voltage = value;
            recordedEvents[channel].add(newEvent);
            // Serial.println("record event");
            // Serial.println(sampleCounter);
            // Serial.println(gate);
            // Serial.println(value);
        // }
    }

    gateOutputs[channel].gate(gate);
    if(gate) {
        Hardware::hw.cvOutputPins[channel+4]->analogWrite(value);
    }
}


void SequencerController::quantizeEvents(int channel) {
    if(recording[channel]) {
        bool recordPrevStepEvent = false;
        bool recordThisStepEvent = false;
        SequenceStepEvent prevStepEvent;
        SequenceStepEvent thisStepEvent;
        int halfStepTime = sampleCounter/2;

        Serial.print("step ");
        Serial.println(sequencer.getCurrentStep());

        for(SequenceStepEvent& event : recordedEvents[channel]) {
            Serial.print("event ");
            Serial.print(event.time);
            Serial.print(" ");
            Serial.print(event.step.gate);
            Serial.print(" ");
            Serial.println(event.step.voltage);
            if(event.time < halfStepTime) {
                recordPrevStepEvent = event.step.gate;
                prevStepEvent = event;
            } else {
                recordThisStepEvent = event.step.gate;
                thisStepEvent = event;
            }
        }

        if(recordPrevStepEvent) {
            sequencer.getStep(channel, prevStep).gate = true;
            sequencer.getStep(channel, prevStep).voltage = prevStepEvent.step.voltage;
        }

        if(recordThisStepEvent) {
            sequencer.getStep(channel, sequencer.getCurrentStep()).gate = true;
            sequencer.getStep(channel, sequencer.getCurrentStep()).voltage = thisStepEvent.step.voltage;
        }

        if (recordPrevStepEvent || recordThisStepEvent) {
            interface.render();
        }

        recordedEvents[channel].clear();
        recordedEvents[channel].add(thisStepEvent);
    }
}

void SequencerController::outputSequenceStep(int channel) {
    SequenceStep& step = sequencer.getTrack(channel).get(sequencer.getCurrentStep());
    if(step.gate) {
        gateOutputs[channel].gate(true);
        Hardware::hw.cvOutputPins[channel+4]->analogWrite(step.voltage);
    } else {
        gateOutputs[channel].gate(false);
    }
}

