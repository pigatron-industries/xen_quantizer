#ifndef SequencerController_h
#define SequencerController_h

#include "Controller.h"
#include "SequencerInterface.h"
#include "Hardware.h"
#include "lib/neural/filesystem/TensorflowModelManager.h"


using namespace eurorack;

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

        SequencerInterface interface;

        TensorflowModelManager modelManager = TensorflowModelManager(Hardware::hw.fsModels, Hardware::hw.memPoolModel);
        
        void loadModel(int index);
        void tick();
};

#endif
