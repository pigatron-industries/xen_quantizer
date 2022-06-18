#include "ScaleChordController.h"

void ScaleChordController::init(float sampleRate) {
    Controller::init(sampleRate);
    mode.last = Hardware::hw.tuningsManager.getTuningCount()-1;
    init();
}

void ScaleChordController::init() {
    Serial.println("Quantizer");

    tuningData = &Hardware::hw.tuningsManager.loadTuningData(mode.value);
    tuning = tuningData->tuning;

    setScale(0);
    chordClock();
}

// int ScaleChordController::cycleMode(int amount) {

// }

void ScaleChordController::update() {
    // if(linearScaleOffsetPot.update()) {
    //     scaleQuantizer.getScale()->setOffset(linearScaleOffsetPot.getValue());
    // }
}

void ScaleChordController::setScale(int index) {
    if(tuningData == nullptr) {
        scale = &defaultTuningData->scales[index];
    } else {
        scale = tuningData->scales[index];
    }

    scaleQuantizer.setScale(*scale);

    chordQuality.setRange(0, scale->getChordDefs().size()-1);
    chordQuality.update();
    chordDef = &scale->getChordDefs()[chordQuality.getIntValue()];

    chordInversion.setRange(0, scale->getChordDefs().size()-1);

    Serial.print("Scale: ");
    Serial.println(scale->getName());
    Serial.print("Chord: ");
    Serial.println(chordDef->name);
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
        Note scaleRoot = tuning->createNote(0, quantizedScaleOffsetPot.getIntValue());
        scale->setOffset(scaleRoot.voltage);
    }

    if(chordQuality.update()) {
        chordDef = &scale->getChordDefs()[chordQuality.getIntValue()];

        Serial.print("Chord: ");
        Serial.println(chordDef->name);
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
