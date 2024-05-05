#ifndef MidiController_h
#define MidiController_h

#include "Controller.h"
#include "MidiProcessor.h"
#include "MidiInterface.h"

#define MAX_VOLTAGE 5
#define OUTPUT_CHANNELS 4

class MidiController : public ParameterizedController<1>, public MidiProcessor {   
    public:
        MidiController() : ParameterizedController(), MidiProcessor(OUTPUT_CHANNELS) {}
        void init(float sampleRate);
        void init();
        void update();
        void process();

    protected:
        void setPitch(uint8_t outputChannel, float pitch);
        void setVelocity(uint8_t outputChannel, float velocity);

    private:
        enum Parameter {
            MODE
        };

        MidiInterface interface;

        GateInput<> triggerInputs[4] = {
            GateInput<>(*Hardware::hw.triggerInputPins[0]),
            GateInput<>(*Hardware::hw.triggerInputPins[1]),
            GateInput<>(*Hardware::hw.triggerInputPins[2]),
            GateInput<>(*Hardware::hw.triggerInputPins[3])
        };

        void readMidi();
        void sendMidi(int fromPort, uint8_t type, uint8_t data1, uint8_t data2, uint8_t channel);
};

#endif  