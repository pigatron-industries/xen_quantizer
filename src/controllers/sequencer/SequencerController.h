#ifndef SequencerController_h
#define SequencerController_h

#include "Controller.h"
#include "Sequencer.h"
#include "SequencerInterface.h"
#include "controllers/midi/MidiProcessor.h"

#define OUTPUT_CHANNELS 4

class SequencerController : public ParameterizedController<1>, public MidiProcessor {
    public:
        SequencerController() : ParameterizedController(), MidiProcessor(OUTPUT_CHANNELS) {}
        void init(float sampleRate);
        void init();
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

        bool recording[4] = {false, false, false, false};

        void setPitch(uint8_t outputChannel, float pitch);
        void setVelocity(uint8_t outputChannel, float velocity);

        void tick();
        void reset();
        float getInputValue(int channel);
        void recordInputValue(int channel);
        void outputSequenceValue(int channel);
};


#endif