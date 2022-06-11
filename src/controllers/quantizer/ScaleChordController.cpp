#include "ScaleChordController.h"

void ScaleChordController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void ScaleChordController::init() {
    Serial.println("Quantizer");

    setScale(0);

    chordClock();
}

void ScaleChordController::update() {
    // if(linearScaleOffsetPot.update()) {
    //     scaleQuantizer.getScale()->setOffset(linearScaleOffsetPot.getValue());
    // }

    // if(chordQuality.update()) {
    //     Serial.println("chordQuality");
    //     Serial.println(chordQuality.getStableVoltage());
    //     Serial.println(chordQuality.getValue());
    //     Serial.println(chordQuality.getIntValue());
    //     chordDef = &scale->getChordDefs()[chordQuality.getIntValue()];
    // }
}

void ScaleChordController::setScale(int index) {
    scale = &tuningData->scales[index];
    scaleQuantizer.setScale(*scale);

    chordQuality.setRange(0, scale->getChordDefs().size()-1);
    chordQuality.update();
    chordDef = &scale->getChordDefs()[chordQuality.getIntValue()];

    chordInversion.setRange(0, scale->getChordDefs().size()-1);
}

void ScaleChordController::process() {
    Hardware::hw.mcp23s17Device.receive();

    transpose = Hardware::hw.channel3InputPin.analogRead();

    if(clockInputs[0].update() && clockInputs[0].rose()) {
        chordClock();
    }

    if(clockInputs[1].update() && clockInputs[1].rose()) {
        noteClock();
    }
}

void ScaleChordController::chordClock() {
    delay(1);

    if(quantizedScaleOffsetPot.update()) {
        Note scaleRoot = tuningData->tuning->createNote(0, quantizedScaleOffsetPot.getIntValue());
        scale->setOffset(scaleRoot.voltage);
    }

    if(chordQuality.update()) {
        Serial.println("chordQuality");
        Serial.println(chordQuality.getStableVoltage());
        Serial.println(chordQuality.getValue());
        Serial.println(chordQuality.getIntValue());
        chordDef = &scale->getChordDefs()[chordQuality.getIntValue()];
    }

    chordInversion.update();

    float chordVoltage = Hardware::hw.channel1InputPin.analogRead();

    Note root = scaleQuantizer.quantize(chordVoltage);

    chord = ScaleFactory::createChord(*scale, *chordDef, root, chordInversion.getIntValue(), 0);

    Hardware::hw.cvOutputPins[0]->analogWrite(chord[0].voltage + transpose);
    Hardware::hw.cvOutputPins[1]->analogWrite(chord[1].voltage + transpose);
    Hardware::hw.cvOutputPins[2]->analogWrite(chord[2].voltage + transpose);
    // Hardware::hw.cvOutputPins[3]->analogWrite(chord[3].voltage);
}

void ScaleChordController::noteClock() {
    delay(1);
    float noteVoltage = Hardware::hw.channel2InputPin.analogRead();
    Note note = chordQuantizer.quantize(noteVoltage);
    //Note note = scaleQuantizer.quantize(noteVoltage);

    Hardware::hw.cvOutputPins[3]->analogWrite(note.voltage + transpose);
}
