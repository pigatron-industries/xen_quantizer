#ifndef SequencerController_h
#define SequencerController_h

#include "Controller.h"
#include "Sequencer.h"
#include "SequencerInterface.h"


class SequencerController : public ParameterizedController<1> {
    public:
        SequencerController() {}
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

        void tick();
        void reset();
        void recordInputValue(int channel);
        void outputSequenceValue(int channel);
};


#endif