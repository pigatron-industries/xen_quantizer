#include "MainController.h"
#include "hwconfig.h"
#include "Hardware.h"

#include <Arduino.h>
#include <SPI.h>
#include <math.h>

#define TRANSMIT_TIME 10000

MainController* MainController::mainController = nullptr;

MainController::MainController(float sampleRate) : AbstractMainController(Hardware::hw.encoder) {
    MainController::mainController = this;
    this->sampleRate = sampleRate;
    // this->shortPress = &MainController::incrementMode;
    this->clockWise = &MainController::incrementValue;
    this->antiClockWise = &MainController::decrementValue;
    initOnModeSelect = false;
}

void MainController::init() {
    Hardware::hw.init();
    AbstractMainController::init();
}

void MainController::controllerInit() {
    interruptTimer.end();
    saveMode();

    if(controllers.getSelected()->getSampleRate() > 0) {
        controllers.getSelected()->init();
    } else {
        controllers.getSelected()->init(sampleRate);
    }

    int intervalMicros = 1000000/sampleRate;
    interruptTimer.begin(MainController::interruptHandler, intervalMicros);
    SPI.usingInterrupt(interruptTimer);
}

void MainController::interruptHandler() {
    mainController->process();
}

void MainController::update() {
    doEncoder1Event(Hardware::hw.encoder.getEncoderEvent());
    doEncoder2Event(Hardware::hw.encoder2.getEncoderEvent());

    controllers.getSelected()->update();

    PROFILE_PRINT
}

void MainController::doEncoder1Event(RotaryEncoderButton::EncoderEvent event) {
    switch(event) {
        case RotaryEncoderButton::EncoderEvent::EVENT_CLOCKWISE:
            incrementMode();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_ANTICLOCKWISE:
            decrementMode();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_HELD_CLOCKWISE:
            (this->*heldClockWise)();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_HELD_ANTICLOCKWISE:
            (this->*heldAntiClockWise)();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_SHORT_PRESS:
            //(this->*shortPress)();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_NONE:
            break;
    }
}

void MainController::doEncoder2Event(RotaryEncoderButton::EncoderEvent event) {
    switch(event) {
        case RotaryEncoderButton::EncoderEvent::EVENT_CLOCKWISE:
            incrementValue();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_ANTICLOCKWISE:
            decrementValue();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_HELD_CLOCKWISE:
            //(this->*heldClockWise)();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_HELD_ANTICLOCKWISE:
            //(this->*heldAntiClockWise)();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_SHORT_PRESS:
            //(this->*shortPress)();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_NONE:
            break;
    }
}

void MainController::process() {
    PROFILE_START
    controllers.getSelected()->process();
    Hardware::hw.dac8164Device1.send();
    Hardware::hw.dac8164Device2.send();
    PROFILE_END
}
