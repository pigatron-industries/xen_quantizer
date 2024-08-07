#ifndef SequencerController_h
#define SequencerController_h

#include "Controller.h"
#include "Sequencer.h"
#include "SequencerInterface.h"
#include "controllers/midi/MidiProcessor.h"

#define OUTPUT_CHANNELS 4
#define MAX_EVENTS_PER_TICK 16

class SequencerController : public ParameterizedController<1>, public MidiProcessor {
    public:

        enum Parameter {
            PATTERN,
        };

        SequencerController() : ParameterizedController(), MidiProcessor(OUTPUT_CHANNELS) {}
        void init(float sampleRate);
        void init();

        int cycleParameter(int amount);
        void cycleValue(int amount);


        void update();
        void process();

    private:
        SequencerInterface interface;
        Sequencer sequencer;

        AnalogGateInput<AnalogInputPinT> clockInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.channel1CvPin);
        AnalogGateInput<AnalogInputPinT> resetInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.channel2CvPin);

        LinearInput<AnalogInputPinT> valueInputs[4] = {
            LinearInput<AnalogInputPinT>(Hardware::hw.channel1InputPin, -5, 5, -5, 5),
            LinearInput<AnalogInputPinT>(Hardware::hw.channel2InputPin, -5, 5, -5, 5),
            LinearInput<AnalogInputPinT>(Hardware::hw.channel3InputPin, -5, 5, -5, 5),
            LinearInput<AnalogInputPinT>(Hardware::hw.channel4InputPin, -5, 5, -5, 5)
        };

        GateInput<> triggerInputs[4] = {
            GateInput<>(*Hardware::hw.triggerInputPins[0]),
            GateInput<>(*Hardware::hw.triggerInputPins[1]),
            GateInput<>(*Hardware::hw.triggerInputPins[2]),
            GateInput<>(*Hardware::hw.triggerInputPins[3])
        };

        AnalogGateOutput<DAC8164Device> gateOutputs[4] = {
            AnalogGateOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[0]),
            AnalogGateOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[1]),
            AnalogGateOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[2]),
            AnalogGateOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[3])
        };

        int sampleCounter = 0;
        int prevStep = 0;
        bool recording[OUTPUT_CHANNELS] = {false, false, false, false};
        Array<SequenceStepEvent, MAX_EVENTS_PER_TICK> recordedEvents[OUTPUT_CHANNELS] = {
            Array<SequenceStepEvent, MAX_EVENTS_PER_TICK>(),
            Array<SequenceStepEvent, MAX_EVENTS_PER_TICK>(),
            Array<SequenceStepEvent, MAX_EVENTS_PER_TICK>(),
            Array<SequenceStepEvent, MAX_EVENTS_PER_TICK>()
        };

        void setPitch(uint8_t outputChannel, float pitch);
        void setVelocity(uint8_t outputChannel, float velocity);

        void tick();
        void reset();
        float getInputValue(int channel);
        void recordEvent(int channel);
        void quantizeEvents(int channel);
        void outputSequenceStep(int channel);
};


#endif