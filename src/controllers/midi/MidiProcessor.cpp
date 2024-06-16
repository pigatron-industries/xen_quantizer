#include "MidiProcessor.h"
#include "MidiConstants.h"


MidiProcessor::MidiProcessor(uint8_t numChannels) { 
    this->numChannels = numChannels;
    // default midi channels 1-4 for output channels 1-4
    for(int8_t outputChannel = 0; outputChannel < numChannels; outputChannel++) {
        setOutputChannelParam(outputChannel, outputChannel);
    }
}


void MidiProcessor::readMidi() {
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

void MidiProcessor::sendMidi(int fromPort, uint8_t type, uint8_t data1, uint8_t data2, uint8_t channel) {
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


void MidiProcessor::handleMessage(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2) {
    uint8_t command = HI_NYBBLE(type);
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
            handlePitchBend(channel, data1 | (data2 << 7));
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
    outputChannelState[outputChannel].mpeChannel = channel;

    Serial.print("channel ");
    Serial.print(outputChannel);
    Serial.print(" note ");
    Serial.println(note);

    // pitch cv
    float notePitch = convertNote(outputChannelState[outputChannel].note) + pitchOffset;
    float totalPitch = notePitch + 0; //convertBend(channel, 0);
    outputChannelState[outputChannel].pitch = totalPitch;
    setPitch(outputChannel, totalPitch);

    // velocity cv
    float velocityVoltage = convertVelocity(velocity);
    setVelocity(outputChannel, velocityVoltage);
}

void MidiProcessor::handlePitchBend(uint8_t channel, int16_t bend) {
    int8_t outputChannel = getOutputChannelForMPE(channel);
    if(outputChannel == -1) {
        return;
    }

    Serial.print("channel ");
    Serial.print(outputChannel);
    Serial.print(" note ");
    Serial.println(outputChannelState[outputChannel].note);

    // pitch cv
    float notePitch = convertNote(outputChannelState[outputChannel].note) + pitchOffset;
    float totalPitch = notePitch + convertBend(channel, bend);
    outputChannelState[outputChannel].pitch = totalPitch;
    setPitch(outputChannel, totalPitch);
}

void MidiProcessor::handleNoteOff(uint8_t channel, uint8_t note) {
    int8_t outputChannel = getOutputChannelForNote(channel, note);
    if(outputChannel == -1) {
        return;
    }

    outputChannelState[outputChannel].note = -1;
    outputChannelState[outputChannel].mpeChannel = -1;
    setVelocity(outputChannel, 0);
}

void MidiProcessor::handleControlChange(uint8_t channel, uint8_t controlNumber, uint8_t value) {
    switch(controlNumber) {
        case CONTROL_MUTE:
            Serial.println("Mute");
            handleMuteChannel(channel);
            break;
        case CONTROL_RPN_PARAM_LSB:
            midiChannelData[channel].rpnParam = value;
            break;
        case CONTROL_RPN_PARAM_MSB:
            midiChannelData[channel].rpnParam |= (value << 7);
            break;
        case CONTROL_RPN_VALUE_COARSE:
            midiChannelData[channel].rpnValueCoarse = value;
            break;
        case CONTROL_RPN_VALUE_FINE:
            midiChannelData[channel].rpnValueFine = value;
            handleRPNParameterChange(channel, midiChannelData[channel].rpnParam, midiChannelData[channel].rpnValueCoarse, midiChannelData[channel].rpnValueFine);
            break;
        default:
            Serial.println("Unhandled Control Change");
            Serial.println(channel);
            Serial.println(controlNumber);
            Serial.println(value);
            break;
    }
}

void MidiProcessor::handleMuteChannel(uint8_t channel) {
    for (int8_t outputChannel = 0; outputChannel < numChannels; outputChannel++) {
        if(outputChannelState[outputChannel].midiChannel == channel) {
            outputChannelState[outputChannel].note = -1;
            setVelocity(outputChannel, 0);
        }
    }
}

void MidiProcessor::handleRPNParameterChange(uint8_t channel, uint16_t param, uint16_t valueCoarse, uint16_t valueFine) {
    switch (param) {
        case RPN_PARAM_PITCH_BEND_RANGE:
            Serial.println("Pitch bend range");
            midiChannelData[channel].pitchBendRangeCents = valueCoarse*100 + valueFine;
            break;
        default:
            Serial.println("Unhandled RPN Parameter Change");
            Serial.println(channel);
            Serial.println(param);
            Serial.println(valueCoarse);
            Serial.println(valueFine);
            break;
    }
}

void MidiProcessor::handleNotePressure(uint8_t channel, uint8_t note, uint8_t pressure) {

}

void MidiProcessor::handleChannelPressure(uint8_t channel, uint8_t pressure) {

}

void MidiProcessor::handleClock() {

}

void MidiProcessor::handleStart() {

}

void MidiProcessor::handleStop() {

}

void MidiProcessor::handleReset() {

}

void MidiProcessor::setOutputChannelParam(int8_t outputChannel, int8_t midiChannel) {
    outputChannelState[outputChannel].midiChannel = midiChannel;
}

int8_t MidiProcessor::getOutputChannelParam(int8_t outputChannel) {
    return outputChannelState[outputChannel].midiChannel;
}

int8_t MidiProcessor::getOutputChannel(int8_t midiChannel) {
    for(int8_t i = 0; i < numChannels; i++) {
        int8_t outputChannel = i;
        if (rotateOutputChannels) {
            outputChannel = (lastChannel + 1) % numChannels;
        }
        int8_t outputMidiChannel = outputChannelState[outputChannel].midiChannel;
        if((outputMidiChannel == CHANNEL_ALL || outputMidiChannel == midiChannel) && outputChannelState[outputChannel].note == -1) {
            lastChannel = outputChannel;
            return outputChannel;
        }
    }

    return -1;
}

int8_t MidiProcessor::getOutputChannelForMPE(int8_t midiChannel) {
    for(int8_t outputChannel = 0; outputChannel < numChannels; outputChannel++) {
        int8_t mpeChannel = outputChannelState[outputChannel].mpeChannel;
        if(mpeChannel == midiChannel && outputChannelState[outputChannel].note >= 0) {
            return outputChannel;
        }
    }
    return -1;
} 

int8_t MidiProcessor::getOutputChannelForNote(int8_t midiChannel, int8_t note) {
    for(int8_t outputChannel = 0; outputChannel < numChannels; outputChannel++) {
        int8_t outputMidiChannel = outputChannelState[outputChannel].midiChannel;
        if((outputMidiChannel == CHANNEL_ALL || outputMidiChannel == midiChannel) && outputChannelState[outputChannel].note == note) {
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

float MidiProcessor::convertBend(uint8_t channel, int16_t bend) {
    return (float(bend-8192) / 8192) * (float(midiChannelData[channel].pitchBendRangeCents) / 1200);
}

float MidiProcessor::convertVelocity(uint8_t velocity) {
    return (float(velocity) / 127) * MAX_VOLTAGE;
}

float MidiProcessor::convertControl(uint16_t value) {
    return (float(value) / 16384) * MAX_VOLTAGE;
}