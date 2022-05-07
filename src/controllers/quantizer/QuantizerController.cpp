#include "QuantizerController.h"

void QuantizerController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void QuantizerController::init() {
    Serial.println("Quantizer");

    for(ChordDef& chord : chordDefs) {
        scaleRepository.addChord(chord);
    }
    for(ScaleDef& scale : scaleDefs) {
        scaleRepository.addScale(scale);
    }
}

void QuantizerController::update() {
    if(chordQualityPot.update()) {
        chordQuality = chordQualityPot.getValue();
    }
}

void QuantizerController::process() {
    Hardware::hw.mcp23s17Device.receive();

    if(clockInput.update() && clockInput.rose()) {
        float voltage = Hardware::hw.channel1InputPin.analogRead();

        Note root = pitchQuantizer.quantizeToScale(voltage, scaleDefs[0]);
        Chord chord = tuning.createChord(root, chordDefs[chordQuality]);

        Hardware::hw.cvOutputPins[0]->analogWrite(chord[0].voltage);
        Hardware::hw.cvOutputPins[1]->analogWrite(chord[1].voltage);
        Hardware::hw.cvOutputPins[2]->analogWrite(chord[2].voltage);
        Hardware::hw.cvOutputPins[3]->analogWrite(chord[3].voltage);
    }
}
