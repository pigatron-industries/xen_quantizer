#include "QuantizerController.h"

void QuantizerController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void QuantizerController::init() {
    Serial.println("Quantizer");

    scaleQuantizer.setScale(scales[0]);
    scaleQuantizer.setScaleOffset(0);

    for(Scale& scale : scales) {
        scaleRepository.addScale(scale);
    }
}

void QuantizerController::update() {
    // if(scaleOffsetPot.update()) {
    //     Serial.println(scaleOffsetPot.getIntValue());
    //     pitchQuantizer.setScaleOffset(scaleOffsetPot.getIntValue());
    // }
}

void QuantizerController::process() {
    Hardware::hw.mcp23s17Device.receive();

    if(clockInputs[0].update() && clockInputs[0].rose()) {
        chordClock();
    }

    if(clockInputs[1].update() && clockInputs[1].rose()) {
        noteClock();
    }
}

void QuantizerController::chordClock() {
    if(scaleOffsetPot.update()) {
        Note scaleRoot = tuning.createNote(0, scaleOffsetPot.getIntValue());
        scaleQuantizer.setScaleOffset(scaleRoot.voltage);
    }

    float chordVoltage = Hardware::hw.channel1InputPin.analogRead();

    Note root = scaleQuantizer.quantizeToScale(chordVoltage);
    Chord& chord = scaleQuantizer.createChord(chordDefs[0], root);

    Hardware::hw.cvOutputPins[0]->analogWrite(chord[0].voltage);
    Hardware::hw.cvOutputPins[1]->analogWrite(chord[1].voltage);
    Hardware::hw.cvOutputPins[2]->analogWrite(chord[2].voltage);
    // Hardware::hw.cvOutputPins[3]->analogWrite(chord[3].voltage);
}

void QuantizerController::noteClock() {
    float noteVoltage = Hardware::hw.channel2InputPin.analogRead();
    Note note =  scaleQuantizer.quantizeToChord(noteVoltage);
    Hardware::hw.cvOutputPins[3]->analogWrite(note.voltage);
}
