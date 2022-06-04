#include "QuantizerController.h"

void QuantizerController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void QuantizerController::init() {
    Serial.println("Quantizer");

    scaleQuantizer.setScale(scales[0]);
    scaleQuantizer.getScale()->setOffset(0);

    chordClock();
}

void QuantizerController::update() {
    if(linearScaleOffsetPot.update()) {
        scaleQuantizer.getScale()->setOffset(linearScaleOffsetPot.getValue());
    }
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
    // if(quantizedScaleOffsetPot.update()) {
    //     Note scaleRoot = tuning.createNote(0, quantizedScaleOffsetPot.getIntValue());
    //     scaleQuantizer.setScaleOffset(scaleRoot.voltage);
    // }

    float chordVoltage = Hardware::hw.channel1InputPin.analogRead();

    Note root = scaleQuantizer.quantize(chordVoltage);
    chord = ScaleFactory::createChord(*scaleQuantizer.getScale(), chordDefs[0], root);

    Hardware::hw.cvOutputPins[0]->analogWrite(chord[0].voltage);
    Hardware::hw.cvOutputPins[1]->analogWrite(chord[1].voltage);
    Hardware::hw.cvOutputPins[2]->analogWrite(chord[2].voltage);
    // Hardware::hw.cvOutputPins[3]->analogWrite(chord[3].voltage);
}

void QuantizerController::noteClock() {
    float noteVoltage = Hardware::hw.channel2InputPin.analogRead();
    Note note = chordQuantizer.quantize(noteVoltage);
    Hardware::hw.cvOutputPins[3]->analogWrite(note.voltage);
}
