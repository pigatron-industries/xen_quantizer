#ifndef SequenceDecoderController_h
#define SequenceDecoderController_h

#include "Controller.h"
#include "SequencerInterface.h"
#include "Hardware.h"
#include "lib/neural/filesystem/TensorflowModelManager.h"
#include "lib/neural/model/SequenceDecoderModel.h"


using namespace eurorack;

#define NUM_NOTE_OUTPUTS 4

class SequenceDecoderController : public ParameterizedController<1> {
    public:

        enum Parameter {
            MODEL
        };

        SequenceDecoderController(const char* modelDir, const char* titleText) : ParameterizedController(), interface(titleText) { this->modelDir = modelDir; }
        virtual void init(float sampleRate);
        virtual void init();

        int cycleParameter(int amount);
        virtual void cycleValue(int amount);

        virtual void update();
        virtual void process();

    
    protected:
        const char* modelDir = "/";

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

        SequencerInterface interface;

        TensorflowModel& model = Hardware::hw.modelManager.getModel();
        SequenceDecoderModel sequenceDecoderModel = SequenceDecoderModel(model);
        
        
        void setModel(int index);
        void reset();
        void tick();
        void runInference();

        virtual void decodeOutput(OutputNote* notes) = 0;
};

#endif
