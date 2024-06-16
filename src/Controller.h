#ifndef Controller_h
#define Controller_h

#include <eurorack.h>
#include "Hardware.h"

class Controller : virtual public AbstractController {
    public:
        Controller() : AbstractController() {}
        virtual void init(float sampleRate) { this->sampleRate = sampleRate; }
        virtual void init() {};
        virtual void update() = 0;
        virtual void process() = 0;
        float getSampleRate() { return sampleRate; }
        bool isInited() { return sampleRate > 0; }
    
    protected: 
        float sampleRate = 0;
};


template<int N>
class ParameterizedController : public Controller, public AbstractParameterizedController<N> {
    public:
        void load() { AbstractParameterizedController<N>::load(); }
        void save() { AbstractParameterizedController<N>::save(); }
};

#endif
