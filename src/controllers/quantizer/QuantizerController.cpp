#include "QuantizerController.h"

void QuantizerController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void QuantizerController::init() {
    Serial.println("Quantizer");
}

void QuantizerController::update() {

}

void QuantizerController::process() {
    Hardware::hw.mcp23s17Device.receive();

    if(clockInput.update() && clockInput.rose()) {
        float value = Hardware::hw.channel1InputPin.analogRead();
        //Note note = pitchQuantizer.quantizeChromatic(value);
        Note note = pitchQuantizer.quantizeToScale(value, scale);
        Hardware::hw.cvOutputPins[0]->analogWrite(note.voltage);
    }
}
