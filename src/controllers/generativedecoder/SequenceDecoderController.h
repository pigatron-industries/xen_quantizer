#ifndef SequenceDecoderController_h
#define SequenceDecoderController_h

#include "Controller.h"
#include "SequenceDecoderInterface.h"
#include "Hardware.h"
#include "lib/neural/filesystem/TensorflowModelManager.h"
#include "lib/neural/model/SequenceDecoderModel.h"
#include "TickCounter.h"

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
        GateInput<> inferenceInput = GateInput<>(*Hardware::hw.triggerInputPins[2]);

        LinearInput<AnalogInputPinT> latent1Input = LinearInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> latent2Input = LinearInput<AnalogInputPinT>(Hardware::hw.channel2PotPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> latent3Input = LinearInput<AnalogInputPinT>(Hardware::hw.channel3PotPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> thresholdInput = LinearInput<AnalogInputPinT>(Hardware::hw.channel4PotPin, -5, 5, 0, 0.3);

        LinearInput<AnalogInputPinT> latent1CVInput = LinearInput<AnalogInputPinT>(Hardware::hw.channel1CvPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> latent2CVInput = LinearInput<AnalogInputPinT>(Hardware::hw.channel2CvPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> latent3CVInput = LinearInput<AnalogInputPinT>(Hardware::hw.channel3CvPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> thresholdCVInput = LinearInput<AnalogInputPinT>(Hardware::hw.channel4CvPin, -5, 5, -0.3, 0.3);

        bool pauseClock = false;
        bool manualInference = false;

        SequenceDecoderInterface interface;

        TensorflowModel& model = Hardware::hw.modelManager.getModel();
        SequenceDecoderModel sequenceDecoderModel = SequenceDecoderModel(model);

        TickCounter tickCounter;
        
        
        void setModel(int index);
        void reset();
        void tick();
        void runInference();

        virtual void decodeOutput(Array<OutputNote, MAX_NOTES_OUTPUT>& notes) = 0;
};

#endif
