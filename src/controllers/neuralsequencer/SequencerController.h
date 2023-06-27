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

        int cycleMode(int amount);
        virtual void cycleValue(int amount);

        virtual void update();
        virtual void process();

        

    private:

        GateInput<> triggerInputs[4] = {
            GateInput<>(*Hardware::hw.triggerInputPins[0]),
            GateInput<>(*Hardware::hw.triggerInputPins[1]),
            GateInput<>(*Hardware::hw.triggerInputPins[2]),
            GateInput<>(*Hardware::hw.triggerInputPins[3])
        };
        LinearInput<AnalogInputPinT> latent1Input = LinearInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, -1, 1);
        LinearInput<AnalogInputPinT> latent2Input = LinearInput<AnalogInputPinT>(Hardware::hw.channel2PotPin, -5, 5, -1, 1);
        LinearInput<AnalogInputPinT> latent3Input = LinearInput<AnalogInputPinT>(Hardware::hw.channel3PotPin, -5, 5, -1, 1);

        SequencerInterface interface;

        TensorflowModelManager modelManager = TensorflowModelManager(Hardware::hw.fsModels, Hardware::hw.memPoolModel);
        TensorflowModel& model = modelManager.getModel();
        SequenceDecoderModel sequenceDecoderModel = SequenceDecoderModel(model);
        
        
        void loadModel(int index);
        void tick();
        void runInference();
};

#endif
