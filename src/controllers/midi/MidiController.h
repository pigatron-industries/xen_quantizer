#ifndef MidiController_h
#define MidiController_h

#include "Controller.h"
#include "MidiProcessor.h"
#include "MidiInterface.h"
#include "controllers/TuningSelection.h"

#define MAX_VOLTAGE 5
#define OUTPUT_CHANNELS 4

class MidiController : public ParameterizedController<5>, public MidiProcessor, public TuningSelection {   
    public:

        enum Parameter {
            TUNING,
            CHANNEL0,
            CHANNEL1,
            CHANNEL2,
            CHANNEL3
        };

        MidiController() : ParameterizedController(), MidiProcessor(OUTPUT_CHANNELS) {}
        void init(float sampleRate);
        void init();

        int cycleParameter(int amount);
        virtual void cycleValue(int amount);
        void selectValue();

        void update();
        void process();

    protected:
        void setTuning(int index);
        void setPitch(uint8_t outputChannel, float pitch);
        void setVelocity(uint8_t outputChannel, float velocity);

    private:
    
        MidiInterface interface;

        GateInput<> triggerInputs[4] = {
            GateInput<>(*Hardware::hw.triggerInputPins[0]),
            GateInput<>(*Hardware::hw.triggerInputPins[1]),
            GateInput<>(*Hardware::hw.triggerInputPins[2]),
            GateInput<>(*Hardware::hw.triggerInputPins[3])
        };

        void readMidi();
        void sendMidi(int fromPort, uint8_t type, uint8_t data1, uint8_t data2, uint8_t channel);

        float convertNote(int8_t note);
};

#endif  