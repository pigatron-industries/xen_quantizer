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
};

#endif  