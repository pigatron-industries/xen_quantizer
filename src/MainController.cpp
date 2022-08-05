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
    this->shortPress = &MainController::incrementMode;
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
    RotaryEncoderButton::EncoderEvent event = encoder.getEncoderEvent();
    if(event == RotaryEncoderButton::EncoderEvent::EVENT_SHORT_PRESS) {
        
    }
    doEncoderEvent(event);
    controllers.getSelected()->update();

    PROFILE_PRINT
}

void MainController::process() {
    PROFILE_START
    controllers.getSelected()->process();
    Hardware::hw.dac8164Device1.send();
    Hardware::hw.dac8164Device2.send();
    PROFILE_END
}
