#include "QuantizerController.h"

void QuantizerController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void QuantizerController::init() {
    Serial.println("Quantizer");

    tuning.enable({3, 5, 7, 10});
}

void QuantizerController::update() {

}

void QuantizerController::process() {
    Hardware::hw.mcp23s17Device.receive();

    if(clockInput.update() && clockInput.rose()) {
        float value = Hardware::hw.channel1InputPin.analogRead();
        Note note = pitchQuantizer.quantizeChromatic(value);
        Hardware::hw.cvOutputPins[0]->analogWrite(note.voltage);
    }
}
