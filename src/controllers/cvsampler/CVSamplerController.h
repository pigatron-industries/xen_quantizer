#ifndef CVSamplerController_h
#define CVSamplerController_h

#include "Controller.h"


class CVSamplerController : public ParameterizedController<1> {
    public:
        CVSamplerController() {}
        void init(float sampleRate);
        void init();
        void update();
        void process();
};


#endif