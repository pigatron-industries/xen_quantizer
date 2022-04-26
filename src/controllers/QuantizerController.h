#ifndef QuantizerController_h
#define QuantizerController_h

#include "Controller.h"

using namespace eurorack;

class QuantizerController : public Controller {
    public:

        QuantizerController() : Controller() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:

};

#endif
