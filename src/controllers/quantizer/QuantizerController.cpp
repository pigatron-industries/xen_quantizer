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
        Note root = pitchQuantizer.quantizeToScale(value, scaleDef);
        Chord chord = tuning.createChord(root, chordDef[0]);
        Hardware::hw.cvOutputPins[0]->analogWrite(chord[0].voltage);
        Hardware::hw.cvOutputPins[1]->analogWrite(chord[1].voltage);
        Hardware::hw.cvOutputPins[2]->analogWrite(chord[2].voltage);
        Hardware::hw.cvOutputPins[3]->analogWrite(chord[3].voltage);
    }
}
