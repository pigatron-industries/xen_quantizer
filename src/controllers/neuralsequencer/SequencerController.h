#ifndef SequencerController_h
#define SequencerController_h

#include "Controller.h"
#include "SequencerInterface.h"
#include "Hardware.h"
#include "lib/neural/filesystem/TensorflowModelManager.h"
#include "lib/neural/model/SequenceDecoderModel.h"


using namespace eurorack;

#define NUM_NOTE_OUTPUTS 4

class SequencerController : public ParameterizedController<1> {
    public:

        SequencerController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();

        int cycleParameter(int amount);
        virtual void cycleValue(int amount);

        virtual void update();
        virtual void process();

        

    private:

        GateInput<> clockInput = GateInput<>(*Hardware::hw.triggerInputPins[0]);
        GateInput<> resetInput = GateInput<>(*Hardware::hw.triggerInputPins[1]);

        LinearInput<AnalogInputPinT> latent1Input = LinearInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> latent2Input = LinearInput<AnalogInputPinT>(Hardware::hw.channel2PotPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> latent3Input = LinearInput<AnalogInputPinT>(Hardware::hw.channel3PotPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> thresholdInput = LinearInput<AnalogInputPinT>(Hardware::hw.channel4PotPin, -5, 5, 0, 0.3);

        LinearInput<AnalogInputPinT> latent1CVInput = LinearInput<AnalogInputPinT>(Hardware::hw.channel1CvPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> latent2CVInput = LinearInput<AnalogInputPinT>(Hardware::hw.channel2CvPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> latent3CVInput = LinearInput<AnalogInputPinT>(Hardware::hw.channel3CvPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> thresholdCVInput = LinearInput<AnalogInputPinT>(Hardware::hw.channel4CvPin, -5, 5, -0.3, 0.3);

        AnalogTriggerOutput<DAC8164Device> triggerOutputs[4] = {
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[4]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[5]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[6]),
            AnalogTriggerOutput<DAC8164Device>(*Hardware::hw.cvOutputPins[7])
        };

        SequencerInterface interface;

        TensorflowModelManager modelManager = TensorflowModelManager(Hardware::hw.fsModels, Hardware::hw.memPoolModel);
        TensorflowModel& model = modelManager.getModel();
        SequenceDecoderModel sequenceDecoderModel = SequenceDecoderModel(model);
        
        
        void loadModel(int index);
        void reset();
        void tick();
        void runInference();
};

#endif
