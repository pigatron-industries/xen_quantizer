#ifndef MidiProcessor_h
#define MidiProcessor_h

#include "Controller.h"

#define MAX_VOLTAGE 5
#define MAX_OUTPUT_CHANNELS 16

#define CHANNEL_ALL 16
#define CHANNEL_NONE 17

class OutputChannelState {
    public:
        OutputChannelState() {}
        //TODO assign usb controller to output channel
        int8_t midiChannel = CHANNEL_ALL;
        int8_t note = -1;
        int8_t mpeChannel = -1;
};

class MidiChannelData {
    public:
        MidiChannelData() {}
        int16_t rpnParam = -1;
        int16_t rpnValueCoarse = -1;
        int16_t rpnValueFine = -1;

        int16_t pitchBendRangeCents = 200;
};


class MidiProcessor {
    public:
        MidiProcessor(uint8_t numChannels);
        MidiProcessor() : MidiProcessor(MAX_OUTPUT_CHANNELS) {}
        void handleMessage(uint8_t command, uint8_t channel, uint8_t data1, uint8_t data2);
        void setRotateOutputChannels(bool rotateOutputChannels) { this->rotateOutputChannels = rotateOutputChannels; }

    protected:
        virtual void setPitch(uint8_t outputChannel, float pitch) = 0;
        virtual void setVelocity(uint8_t outputChannel, float velocity) = 0;
        void setOutputChannel(int8_t outputChannel, int8_t midiChannel);

    private:
        uint8_t numChannels = MAX_OUTPUT_CHANNELS;
        OutputChannelState outputChannelState[MAX_OUTPUT_CHANNELS];

        int8_t lastChannel = -1;
        bool rotateOutputChannels = false;

        MidiChannelData midiChannelData[16];
        
        void handleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
        void handlePitchBend(uint8_t channel, int16_t bend);
        void handleNoteOff(uint8_t channel, uint8_t note);

        void handleControlChange(uint8_t channel, uint8_t controlNumber, uint8_t value);
        void handleMuteChannel(uint8_t channel);

        void handleRPNParameterChange(uint8_t channel, uint16_t param, uint16_t valueCoarse, uint16_t valueFine);
        void handleNotePressure(uint8_t channel, uint8_t note, uint8_t pressure);
        void handleChannelPressure(uint8_t channel, uint8_t pressure);
        void handleClock();
        void handleStart();
        void handleStop();
        void handleReset();

        int8_t getOutputChannel(int8_t midiChannel);
        int8_t getOutputChannelForNote(int8_t midiChannel, int8_t note);
        int8_t getOutputChannelForMPE(int8_t midiChannel);

        virtual float convertNote(int8_t note);
        virtual float convertBend(uint8_t channel, int16_t bend);
        float convertVelocity(uint8_t velocity);
        float convertControl(uint16_t value);
};

#endif  