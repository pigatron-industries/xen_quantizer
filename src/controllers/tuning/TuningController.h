#ifndef TuningController_h
#define TuningController_h

#include "Controller.h"
#include "lib/graphics/containers/Container.h"
#include "lib/graphics/components/TextComponent.h"

class TuningController : public Controller {
    public:
        TuningController() : Controller() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        IntegerInput<AnalogInputPinT> octavePot = IntegerInput<AnalogInputPinT>(Hardware::hw.channel1PotPin, -5, 5, -5, 5);

        int octave = 0;


        Container<TFTDisplay, 2> displayPage;
        TextComponent<TFTDisplay> text1;
        TextComponent<TFTDisplay> text2;

};

#endif
