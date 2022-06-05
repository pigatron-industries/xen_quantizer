#include "HarmonicWalkController.h"

void HarmonicWalkController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void HarmonicWalkController::init() {
    Serial.println("Harmonic Walk");
    clock();
}

void HarmonicWalkController::update() {
}

void HarmonicWalkController::process() {
    Hardware::hw.mcp23s17Device.receive();

    if(clockInputs[0].update() && clockInputs[0].rose()) {
        clock();
    }

    // if(clockInputs[1].update() && clockInputs[1].rose()) {
    //     clock();
    // }
}

void HarmonicWalkController::clock() {
    delay(1);
    interval.update();

    float inputVoltage = Hardware::hw.channel1InputPin.analogRead();
    outputVoltage = quantizer.quantize(outputVoltage, inputVoltage, interval.getIntValue());

    Hardware::hw.cvOutputPins[0]->analogWrite(outputVoltage);
}
