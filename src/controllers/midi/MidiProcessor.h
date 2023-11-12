#ifndef MidiProcessor_h
#define MidiProcessor_h

#include "Controller.h"

#define MAX_VOLTAGE 5
#define MAX_OUTPUT_CHANNELS 16

class OutputChannelState {
    public:
        OutputChannelState() {}
        int8_t channel = 0;
        int8_t note = -1;
};


class MidiProcessor {
    public:
        MidiProcessor(uint8_t numChannels) { numChannels = numChannels; }
        MidiProcessor() { numChannels = MAX_OUTPUT_CHANNELS; }
        void handleMessage(uint8_t command, uint8_t channel, uint8_t data1, uint8_t data2);

    protected:
        virtual void setPitch(uint8_t outputChannel, float pitch) = 0;
        virtual void setVelocity(uint8_t outputChannel, float velocity) = 0;

    private:
        uint8_t numChannels = MAX_OUTPUT_CHANNELS;
        OutputChannelState outputChannelState[MAX_OUTPUT_CHANNELS];
        
        void handleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
        void handleNoteOff(uint8_t channel, uint8_t note);
        void handleControlChange(uint8_t channel, uint8_t controlNumber, uint8_t value);
        void handleNotePressure(uint8_t channel, uint8_t note, uint8_t pressure);
        void handleChannelPressure(uint8_t channel, uint8_t pressure);
        void handlePitchBend(uint8_t channel, uint8_t bend);
        void handleClock();
        void handleStart();
        void handleStop();
        void handleReset();

        int8_t getOutputChannel(int8_t midiChannel);
        int8_t getOutputChannelForNote(int8_t channel, int8_t note);

        float convertNote(int8_t note);
        float convertBend(int16_t bend);
        float convertVelocity(uint8_t velocity);
        float convertControl(uint16_t value);
};

#endif  