#include "ScaleChordController.h"

void ScaleChordController::init(float sampleRate) {
    Controller::init(sampleRate);
    configParam(Parameter::TUNING, 0, Hardware::hw.tuningsManager.getTuningCount()-1, false);
    interface.init();
    interface.focusTuning();
    setTuning(parameters[Parameter::TUNING].value);
    init();
}

void ScaleChordController::init() {
    Serial.println("Quantizer");
    interface.render();
    chordUpdate();
}

int ScaleChordController::cycleParameter(int amount) {
    parameters.cycle(amount);

    switch(parameters.getSelectedIndex()) {
        case Parameter::TUNING:
            interface.focusTuning();
            break;
        case Parameter::SCALE:
            interface.focusScale();
            break;
        case Parameter::CHORD:
            interface.focusChord();
            break;
        case Parameter::OFFSET:
            interface.focusOffset();
            break;
    }

    return parameters.getSelectedIndex(); 
}

void ScaleChordController::cycleValue(int amount) {
    int value = parameters.getSelected().cycle(amount);
    switch(parameters.getSelectedIndex()) {
        case Parameter::TUNING: {
            FileInfo& file = Hardware::hw.tuningsManager.getFileInfo(value);
            interface.setTuningName(file.filename);
            break;
        }
        case Parameter::SCALE:
            setScale(parameters[Parameter::SCALE].getValue());
            break;
        case Parameter::CHORD:
            interface.focusChord();
            setChord(parameters[Parameter::CHORD].getValue());
            break;
        case Parameter::OFFSET:
            interface.focusOffset();
            updateOffset();
            interface.setScale(scale);
            chordUpdate();
    }

    save();
}

void ScaleChordController::selectValue() {
    int prevValue = parameters.getSelected().getValue();
    int newValue = parameters.getSelected().select();
    switch(parameters.getSelectedIndex()) {
        case Parameter::TUNING:
            if (newValue != prevValue) {
                setTuning(newValue);
            } else {
                interface.setTuning(tuning);
            }
            break;
        case Parameter::SCALE:
            break;
        case Parameter::CHORD:
            break;
        case Parameter::OFFSET:
            break;
    }
}

void ScaleChordController::updateOffset() {
    scale->setOffset(float(parameters[Parameter::OFFSET].value) / tuning->size());
}

void ScaleChordController::update() {

    if(Hardware::hw.pushButtons[0].update()) {
        if(Hardware::hw.pushButtons[0].pressed()) {
            Serial.println("button 1 press");
            Hardware::hw.led1OutputPin.digitalWrite(!Hardware::hw.led1OutputPin.getDigitalValue());
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
    interface.showMessage("Loading");

    tuningData = &Hardware::hw.tuningsManager.loadTuningData(index);
    tuning = tuningData->tuning;

    Serial.print("Tuning: ");
    Serial.println(tuning->getName());
    interface.setTuning(tuning);

    configParam(Parameter::SCALE, 0, tuningData->scales.size() - 1);
    configParam(Parameter::OFFSET, 0, tuning->size() - 1);
    setScale(parameters[Parameter::SCALE].value);
    interface.render();
}

void ScaleChordController::setScale(int index) {
    if(tuningData == nullptr) {
        scale = &defaultTuningData->scales[index];
    } else {
        scale = tuningData->scales[index];
    }

    scaleQuantizer.setScale(*scale);
    chordQuantizer.setScale(*scale);
    updateOffset();

    // update chord parameter range
    configParam(Parameter::CHORD, 0, scale->getChordDefs().size() - 1);
    chordDef = &scale->getChordDefs()[parameters[Parameter::CHORD].value];

    // chordQuality.setRange(0, scale->getChordDefs().size()-1);
    // chordQuality.update();

    Serial.print("Scale: ");
    Serial.println(scale->getName());
    interface.setScale(scale);

    Serial.print("Chord: ");
    Serial.println(chordDef->name);
    interface.setChordDef(chordDef);
}

void ScaleChordController::setChord(int index) {
    chordDef = &scale->getChordDefs()[parameters[Parameter::CHORD].value];

    Serial.print("Chord: ");
    Serial.println(chordDef->name);
    interface.setChordDef(chordDef);
}

void ScaleChordController::process() {
    //transpose = Hardware::hw.channel1InputPin.analogRead();

    if(triggerInputs[0].update() && triggerInputs[0].rose()) {
        delay(1);
        chordUpdate();
        // TODO only trigger if chord has changed and output to trigger output
        chordOutput();
    }

    if(triggerInputs[1].update() && triggerInputs[1].rose()) {
        delay(1);
        noteUpdate();
    }
}

void ScaleChordController::chordUpdate() {
    // if(quantizedScaleOffsetPot.update()) {
    //     Note scaleRoot = tuning->createNote(0, quantizedScaleOffsetPot.getIntValue());
    //     scale->setOffset(scaleRoot.voltage);
    //     Serial.print("Offset: ");
    //     Serial.println(quantizedScaleOffsetPot.getIntValue());
    // }

    // if(chordQuality.update()) {
    //     chordDef = &scale->getChordDefs()[chordQuality.getIntValue()];
    //     Serial.print("Chord: ");
    //     Serial.println(chordDef->name);
    // }

    //chordInversion.update();

    float chordVoltage = Hardware::hw.channel1InputPin.analogRead();

    Note root = scaleQuantizer.quantize(chordVoltage);

    // chord = ScaleFactory::createChord(*scale, *chordDef, root, chordInversion.getIntValue(), 0);
    chord = ScaleFactory::createChord(*scale, *chordDef, root, 0, 0);

    // Hardware::hw.cvOutputPins[3]->analogWrite(chord[3].voltage);

    // Serial.println(root.cycle);
    // Serial.println(root.note);
    // Serial.println(root.voltage);
    interface.setChord(&chord);
}

void ScaleChordController::chordOutput() {
    Hardware::hw.cvOutputPins[4]->analogWrite(chord[0].voltage + transpose);
    Hardware::hw.cvOutputPins[5]->analogWrite(chord[1].voltage + transpose);
    Hardware::hw.cvOutputPins[6]->analogWrite(chord[2].voltage + transpose);
}

void ScaleChordController::noteUpdate() {
    float noteVoltage = Hardware::hw.channel2InputPin.analogRead();
    Note note = chordQuantizer.quantize(noteVoltage);
    //Note note = scaleQuantizer.quantize(noteVoltage);

    Hardware::hw.cvOutputPins[7]->analogWrite(note.voltage + transpose);
}
