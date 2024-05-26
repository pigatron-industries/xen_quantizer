#include "ScaleChordController.h"

#define CV_OUTPUT_START 4

void ScaleChordController::init(float sampleRate) {
    Controller::init(sampleRate);
    configParam(Parameter::TUNING, 0, Hardware::hw.tuningsManager.getTuningCount()-1, false);
    interface.init();
    interface.focusTuning();
    setTuning(parameters[Parameter::TUNING].value);
    init();
}

void ScaleChordController::init() {
    Serial.println("Chord Quantizer");
    interface.render();
    updateChord();
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
            updateChord();
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
    int scaleNote = (parameters[Parameter::OFFSET].value + scaleOffsetPot.getIntValue() + scaleOffsetCv.getIntValue()) % scale->size();
    if(scaleNote < 0) {
        scaleNote += scale->size();
    }
    int tuningNote = scale->getNote(scaleNote);
    Interval& interval = tuning->getInterval(tuningNote);

    scale->setOffset(-interval.voltage);
    interface.setScale(scale);
    interface.setOffset(scaleNote);
}


void ScaleChordController::setTuning(int index) {
    interface.showMessage("Loading");

    tuningData = &Hardware::hw.tuningsManager.loadTuningData(index);
    tuning = tuningData->tuning;

    Serial.print("Tuning: ");
    Serial.println(tuning->getName());
    interface.setTuning(tuning);

    configParam(Parameter::SCALE, 0, tuningData->scales.size() - 1);
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

    // update offset parameter range
    scaleOffsetPot.setRange(1 - scale->size(), scale->size() - 1);
    scaleOffsetCv.setRange(1 - scale->size(), scale->size() - 1);
    configParam(Parameter::OFFSET, 0, scale->size() - 1);

    // update chord parameter range
    configParam(Parameter::CHORD, 0, scale->getChordDefs().size() - 1);
    chordDef = &scale->getChordDefs()[parameters[Parameter::CHORD].value];
    interface.setChordDef(chordDef);

    updateOffset();

    Serial.print("Scale: ");
    Serial.println(scale->getName());
    Serial.print("Chord: ");
    Serial.println(chordDef->name);
}

void ScaleChordController::setChord(int index) {
    chordDef = &scale->getChordDefs()[parameters[Parameter::CHORD].value];

    Serial.print("Chord: ");
    Serial.println(chordDef->name);
    interface.setChordDef(chordDef);
}

void ScaleChordController::update() {
    for(int i = 0; i < 4; i++) {
        if(Hardware::hw.pushButtons[i].update()) {
            if(Hardware::hw.pushButtons[i].pressed()) {
                fixedOutput[i] = !fixedOutput[i];
                Hardware::hw.ledOutputPins[i]->digitalWrite(fixedOutput[i]);
            } 
        }
    }

    noQuantizeInput.update();

    // if(linearScaleOffsetPot.update()) {
    //     scaleQuantizer.getScale()->setOffset(linearScaleOffsetPot.getValue());
    // }
}


void ScaleChordController::process() {
    //transpose = Hardware::hw.channel1InputPin.analogRead();

    bool triggers[4];
    for(int i = 0; i < 4; i++) {
        triggerOutputs[i].update();
        triggers[i] = triggerInputs[i].update() && triggerInputs[i].rose();
    }
    bool anyTriggers = triggers[0] || triggers[1] || triggers[2] || triggers[3];
    if (anyTriggers) { // delay to allow for delays in cv input
        delay(1);
    }

    if(triggers[0]) {
        updateChord();
    }

    if(noQuantizeInput.isGateOn()) {
        // pass through outputs
        for(int i = 0; i < 4; i++) {
            float noteVoltage = Hardware::hw.channelCvInputPins[i]->analogRead();
            Hardware::hw.cvOutputPins[CV_OUTPUT_START + i]->analogWrite(noteVoltage);
            // TODO should triggers be passed through or not?
            // if(triggers[i]) {
            //     triggerOutputs[i].trigger();
            // }
        }
        return;
    } else {
        // quantized outputs
        for (int i = 0; i < 4; i++) {
            if (triggers[i]) {
                updateOutput(i);
            }
        }
    }

}

void ScaleChordController::updateChord() {
    if(scaleOffsetPot.update() || scaleOffsetCv.update()) {
        updateOffset();
    }

    // if(chordQuality.update()) {
    //     chordDef = &scale->getChordDefs()[chordQuality.getIntValue()];
    //     Serial.print("Chord: ");
    //     Serial.println(chordDef->name);
    // }

    //chordInversion.update();

    float chordVoltage = Hardware::hw.channel1InputPin.analogRead();

    // prevent chord going below root note
    // if(chordVoltage <= 0) {
    //     chordVoltage = 0;
    // }

    Note root = scaleQuantizer.quantize(chordVoltage);

    // chord = ScaleFactory::createChord(*scale, *chordDef, root, chordInversion.getIntValue(), 0);
    chord = ScaleFactory::createChord(*scale, *chordDef, root, 0, 0);

    // Hardware::hw.cvOutputPins[3]->analogWrite(chord[3].voltage);

    // Serial.println(root.cycle);
    // Serial.println(root.note);
    // Serial.println(root.voltage);
    interface.setChord(&chord);
}

void ScaleChordController::updateOutput(int i) {
    // Serial.print("Output ");
    // Serial.println(i);
    if (fixedOutput[i] && chord.size() > i) {
        Hardware::hw.cvOutputPins[CV_OUTPUT_START + i]->analogWrite(chord[i].voltage + transpose);
    } else {
        float noteVoltage = Hardware::hw.channelCvInputPins[i]->analogRead();
        Note note = chordQuantizer.quantize(noteVoltage);
        Hardware::hw.cvOutputPins[CV_OUTPUT_START + i]->analogWrite(note.voltage + transpose);
    }

    triggerOutputs[i].trigger();
}
