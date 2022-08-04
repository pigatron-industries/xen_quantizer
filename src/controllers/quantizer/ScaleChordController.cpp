#include "ScaleChordController.h"

void ScaleChordController::init(float sampleRate) {
    Controller::init(sampleRate);
    parameters[Parameter::TUNING].last = Hardware::hw.tuningsManager.getTuningCount()-1;
    setTuning(parameters[Parameter::TUNING].value);
    init();
}

void ScaleChordController::init() {
    Serial.println("Quantizer");
    chordClock();
}

void ScaleChordController::cycleValue(int amount) {
    parameters.getSelected().cycle(amount);
    switch(parameters.getSelectedIndex()) {
        case Parameter::TUNING:
            setTuning(parameters[Parameter::TUNING].value);
            break;
        case Parameter::SCALE:
            setScale(parameters[Parameter::SCALE].value);
            break;
    }
}

void ScaleChordController::update() {

    if(Hardware::hw.pushButtons[0].update()) {
        if(Hardware::hw.pushButtons[0].pressed()) {
            Serial.println("button 1 press");
            Hardware::hw.led1OutputPin.digitalWrite(!Hardware::hw.led1OutputPin.getDigitalValue());
            Hardware::hw.display.init();
        } else if(Hardware::hw.pushButtons[0].released()) {

        }
    }

    if(Hardware::hw.pushButtons[1].update() && Hardware::hw.pushButtons[1].pressed()) {
        Serial.println("button 2 press");
        Hardware::hw.led2OutputPin.digitalWrite(!Hardware::hw.led2OutputPin.getDigitalValue());
    }

    if(Hardware::hw.pushButtons[2].update() && Hardware::hw.pushButtons[2].pressed()) {
        Serial.println("button 3 press");
        Hardware::hw.led3OutputPin.digitalWrite(!Hardware::hw.led3OutputPin.getDigitalValue());
    }

    if(Hardware::hw.pushButtons[3].update() && Hardware::hw.pushButtons[3].pressed()) {
        Serial.println("button 4 press");
        Hardware::hw.led4OutputPin.digitalWrite(!Hardware::hw.led4OutputPin.getDigitalValue());
    }

    // if(linearScaleOffsetPot.update()) {
    //     scaleQuantizer.getScale()->setOffset(linearScaleOffsetPot.getValue());
    // }
}

void ScaleChordController::setTuning(int index) {
    tuningData = &Hardware::hw.tuningsManager.loadTuningData(index);
    tuning = tuningData->tuning;

    Serial.print("Tuning: ");
    Serial.println(tuning->getName());

    parameters[Parameter::SCALE].value = 0;
    parameters[Parameter::SCALE].last = tuningData->scales.size() - 1;
    setScale(0);
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
    //transpose = Hardware::hw.channel1InputPin.analogRead();

    if(triggerInputs[0].update() && triggerInputs[0].rose()) {
        chordClock();
    }

    if(triggerInputs[1].update() && triggerInputs[1].rose()) {
        noteClock();
    }
}

void ScaleChordController::chordClock() {
    delay(1);

    if(quantizedScaleOffsetPot.update()) {
        Note scaleRoot = tuning->createNote(0, quantizedScaleOffsetPot.getIntValue());
        scale->setOffset(scaleRoot.voltage);
        Serial.print("Offset: ");
        Serial.println(quantizedScaleOffsetPot.getIntValue());
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
