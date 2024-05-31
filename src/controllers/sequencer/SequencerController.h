#ifndef SequencerController_h
#define SequencerController_h

#include "Controller.h"
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
};


#endif