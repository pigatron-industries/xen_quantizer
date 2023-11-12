#include "MidiProcessor.h"
#include "MidiConstants.h"


void MidiProcessor::handleMessage(uint8_t command, uint8_t channel, uint8_t data1, uint8_t data2) {
    switch(command) {
        case COMMAND_NOTEOFF:
            Serial.println("Note off");
            handleNoteOff(channel, data1);
            break;
        case COMMAND_NOTEON:
            Serial.println("Note on");
            handleNoteOn(channel, data1, data2);
            break;
        case COMMAND_POLY_PRESSURE:
            Serial.println("Polyphonic aftertouch");
            handleNotePressure(channel, data1, data2);
            break;
        case COMMAND_CONTROL_CHANGE:
            Serial.println("Control change");
            handleControlChange(channel, data1, data2);
            break;
        case COMMAND_PROGRAM_CHANGE:
            Serial.println("Program change");
            break;
        case COMMAND_CHAN_PRESSURE:
            Serial.println("Channel aftertouch");
            handleChannelPressure(channel, data1);
            break;
        case COMMAND_PITCH_BEND:
            Serial.println("Pitch bend");
            handlePitchBend(channel, data1);
            break;
        case COMMAND_SYSTEM:
            if(channel == SYSTEM_EXCLUSIVE) {
                Serial.println("System");
                //handleSysex();
            }
            break;
    }
}

void MidiProcessor::handleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
    int8_t outputChannel = getOutputChannel(channel);
    if(outputChannel == -1) {
        return;
    }

    outputChannelState[outputChannel].note = note;

    // pitch cv
    float notePitch = convertNote(note);
    float totalPitch = notePitch; // + _channelPitchBend[channel]; //TODO add channel pitch bend
    setPitch(outputChannel, totalPitch);

    // velocity cv
    float velocityVoltage = convertVelocity(velocity);
    setVelocity(outputChannel, velocityVoltage);
}

void MidiProcessor::handleNoteOff(uint8_t channel, uint8_t note) {
    int8_t outputChannel = getOutputChannelForNote(channel, note);
    if(outputChannel == -1) {
        return;
    }

    outputChannelState[outputChannel].note = -1;
    setVelocity(outputChannel, 0);
}

void MidiProcessor::handleControlChange(uint8_t channel, uint8_t controlNumber, uint8_t value) {

}

void MidiProcessor::handleNotePressure(uint8_t channel, uint8_t note, uint8_t pressure) {

}

void MidiProcessor::handleChannelPressure(uint8_t channel, uint8_t pressure) {

}

void MidiProcessor::handlePitchBend(uint8_t channel, uint8_t bend) {

}

void MidiProcessor::handleClock() {

}

void MidiProcessor::handleStart() {

}

void MidiProcessor::handleStop() {

}

void MidiProcessor::handleReset() {

}

int8_t MidiProcessor::getOutputChannel(int8_t channel) {
    //TODO configure cv channels
    //TODO find output channel that doesn't have a note being output
    return 0;
}

int8_t MidiProcessor::getOutputChannelForNote(int8_t channel, int8_t note) {
    for(int8_t outputChannel = 0; outputChannel < numChannels; outputChannel++) {
        if(outputChannelState[outputChannel].note == note) {
            return outputChannel;
        }
    }
    return -1;
}

float MidiProcessor::convertNote(int8_t note) {
    float octaveNum = floor(note / 12);
    float noteNum = note - (octaveNum * 12);
    float cents = (octaveNum * 1200) + (noteNum * 100);
    return cents / 1200;
}

float MidiProcessor::convertBend(int16_t bend) {
    return (float(bend) / 8192) / 12;
}

float MidiProcessor::convertVelocity(uint8_t velocity) {
    return (float(velocity) / 127) * MAX_VOLTAGE;
}

float MidiProcessor::convertControl(uint16_t value) {
    return (float(value) / 16384) * MAX_VOLTAGE;
}