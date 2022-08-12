#ifndef MainController_h
#define MainController_h

#include <eurorack.h>
#include <inttypes.h>

#include "Controller.h"
#include "Hardware.h"
#include "apps.h"

class MainController : AbstractMainController<Controller, CONTROLLERS> {

public:
    MainController(float sampleRate);
    void init();
    void update();
    void process();

private:
    float sampleRate;

    void controllerInit();
    void doEncoder1Event(RotaryEncoderButton::EncoderEvent event);
    void doEncoder2Event(RotaryEncoderButton::EncoderEvent event);

    IntervalTimer interruptTimer;
    static MainController* mainController;
    static void interruptHandler();
};

#endif
