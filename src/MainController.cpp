#include "MainController.h"
#include "hwconfig.h"
#include "Hardware.h"

#include <Arduino.h>
#include <SPI.h>
#include <math.h>

#define TRANSMIT_TIME 10000

MainController* MainController::mainController = nullptr;

MainController::MainController(float sampleRate) : DoubleEncoderController(Hardware::hw.encoder1, Hardware::hw.encoder2) {
    MainController::mainController = this;
    this->sampleRate = sampleRate;
    // this->shortPress = &MainController::incrementMode;
    // this->clockWise = &MainController::incrementValue;
    // this->antiClockWise = &MainController::decrementValue;
    initOnModeSelect = false;
}

void MainController::init() {
    Hardware::hw.init();
    DoubleEncoderController::init();
}

void MainController::controllerInit() {
    interruptTimer.end();
    saveState();

    if(controllers.getSelected()->isInited() > 0) {
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
    doEncoder1Event(Hardware::hw.encoder1.getEncoderEvent());
    doEncoder2Event(Hardware::hw.encoder2.getEncoderEvent());

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
