#ifndef MidiController_h
#define MidiController_h

#include "Controller.h"
#include "MidiProcessor.h"
#include "MidiInterface.h"
#include "controllers/TuningSelection.h"

#define MAX_VOLTAGE 5
#define OUTPUT_CHANNELS 4

class MidiController : public ParameterizedController<6>, public MidiProcessor, public TuningSelection {   
    public:

        static MidiController* getInstance() {
            return instance;
        }

        enum Parameter {
            TUNING,
            CHANNEL0,
            CHANNEL1,
            CHANNEL2,
            CHANNEL3,
            ROTATECHANNELS
        };

        MidiController() : ParameterizedController(), MidiProcessor(OUTPUT_CHANNELS) {
            instance = this;
        }
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
        static MidiController* instance;
    
        MidiInterface interface;

        GateInput<> triggerInputs[4] = {
            GateInput<>(*Hardware::hw.triggerInputPins[0]),
            GateInput<>(*Hardware::hw.triggerInputPins[1]),
            GateInput<>(*Hardware::hw.triggerInputPins[2]),
            GateInput<>(*Hardware::hw.triggerInputPins[3])
        };

        float convertNote(int8_t note);
};

#endif  