#include "TuningDataFileReader.h"
#include <eurorack.h>

#define MAX_LINE_SIZE 255
#define SPACES_PER_LEVEL 2

bool TuningDataFileReader::read(FsFile& file) {
    allocate(MAX_LINE_SIZE);

    do {
        readLine(file);
        if(isObject("tuning:", 0)) {
            readTuning(file);
        } else if(isObject("groups:", 0)) {
            readGroups(file);
        }
    } while(!line.endOfFile);

    Serial.println("fin");

    return true;
}



void TuningDataFileReader::readTuning(FsFile& file) {
    Serial.println("readTuning:");
    char nameBuffer[16] = {};

    do {
        readLine(file);
        if(isObject("name:", 1)) {
            strncpy(nameBuffer, getValue(), 16);
        } else if(isObject("eq:", 1)) {
            Serial.println("  Create equal division tuning");
            Tuning tuning = ScaleFactory::createEqualDivisionTuning(arrayItemInt(0), arrayItemFloat(1), nameBuffer);
            for(int i = 0; i < tuning.size(); i++) {
                Serial.println(tuning.getInterval(i).voltage);
            }
            this->tuning = tuningsManager.addTuning(tuning);
        } else if(isObject("cents:", 1)) {
            Serial.println("  Create cents tuning");
            uint8_t notes = arraySize();
            float cycle = arrayItemFloat(notes-1) / 1200;
            Tuning tuning = Tuning(notes, cycle, nameBuffer);
            for(int i = 0; i < notes; i++) {
                tuning.getInterval(i).voltage = arrayItemFloat(i) / 1200;
            }
            this->tuning = tuningsManager.addTuning(tuning);
        } else if(isObject("ratios:", 1)) {
            Serial.println("  Create ratios tuning");
            uint8_t intervalCount = arraySize();
            float cycle = arrayItemFloat(intervalCount-1);
            Tuning tuning = Tuning(intervalCount, cycle, nameBuffer);
            tuning.getInterval(0).voltage = 0;
            for(int i = 1; i < intervalCount; i++) {
                tuning.getInterval(i).voltage = arrayItemRatioToVoltage(i-1);
                Serial.println(tuning.getInterval(i).voltage);
            }
            this->tuning = tuningsManager.addTuning(tuning);
        } 
    } while(line.level >= 1);

    back(file);
}

void TuningDataFileReader::readGroups(FsFile& file) {
    do {
        readLine(file);
        if(isObject("- group:", 1)) {
            readGroup(file);
        }
    } while(line.level >= 1);

    back(file);
}

void TuningDataFileReader::readGroup(FsFile& file) {
    Serial.print("readGroup: ");
    Serial.println(getValue());

    groupScales.clear();

    do {
        readLine(file);
        if(isObject("scales:", 2)) {
            readScales(file);
        } else if(isObject("chords:", 2)) {
            readChords(file);
        }
    } while(line.level >= 2);

    back(file);
}

void TuningDataFileReader::readScales(FsFile& file) {
    do {
        readLine(file);
        if(isObject("- name:", 3)) {
            readScale(file);
        }
    } while(line.level >= 3);

    back(file);
}

void TuningDataFileReader::readChords(FsFile& file) {
    do {
        readLine(file);
        if(isObject("- name:", 3)) {
            readChord(file);
        }
    } while(line.level >= 3);

    back(file);
}

void TuningDataFileReader::readScale(FsFile& file) {
    Serial.print("  readScale: ");
    Serial.println(getValue());

    Scale scale = Scale(*tuning, getValue());

    do {
        readLine(file);
        if(isObject("notes:", 4)) {
            for(int i = 0; i < arraySize(); i++) {
                scale.addNote(arrayItemInt(i));
            }
        }
    } while(line.level >= 4);

    groupScales.add(tuningsManager.addScale(scale));

    back(file);
}

void TuningDataFileReader::readChord(FsFile& file) {
    Serial.print("  readChord: ");
    Serial.println(getValue());

    ChordDef chordDef = ChordDef(getValue());

    do {
        readLine(file);
        if(isObject("notes:", 4)) {
            for(int i = 0; i < arraySize(); i++) {
                chordDef.addNote(arrayItemInt(i));
            }
        }
    } while(line.level >= 4);

    for(Scale* groupScale : groupScales) {
        groupScale->addChordDef(chordDef);
    }

    back(file);
}


void TuningDataFileReader::readLine(FsFile& file) {
    line.linePosition = file.position();
    line.lineLength = file.readBytesUntil('\n', buffer, MAX_LINE_SIZE);
    line.endOfFile = line.lineLength == 0;
    line.level = getLevel();

    // remove comments
    char* hash = strchr(buffer, '#');
    if(hash != nullptr) {
        *hash = 0;
    }
}

int TuningDataFileReader::getLevel() {
    int spaces = strspn(buffer, " ");
    return spaces/SPACES_PER_LEVEL;
}

char* TuningDataFileReader::getValue() {
    return strchr(buffer, ':') + 2;
}

bool TuningDataFileReader::isObject(const char* name, int level) {
    return line.level == level && beginsWith(&buffer[line.level*SPACES_PER_LEVEL], name);
}

void TuningDataFileReader::back(FsFile& file) {
    file.seek(line.linePosition);
}

int TuningDataFileReader::arraySize() {
    char* start = strchr(buffer, '[');
    char* end = strchr(buffer, ']');
    int count = 0;
    for(char* i = start; i < end; i++) {
        if(*i == ',') {
            count++;
        }
    }
    return count+1;
}

Substring TuningDataFileReader::arrayItem(int index) {
    Substring substring;
    substring.start = strchr(buffer, '[') + 1;
    for(int i = 0; i < index; i++) {
        substring.start = strchr(substring.start, ',') + 1;
    }
    substring.end = strchr(substring.start, ',');
    if(substring.end == nullptr) {
        substring.end = strchr(substring.start, ']');
    }

    return substring;
}

int TuningDataFileReader::arrayItemInt(int index) {
    Substring substring = arrayItem(index);
    int value = strtol(substring.start, &substring.end, 10);
    return value;
}

float TuningDataFileReader::arrayItemFloat(int index) {
    Substring substring = arrayItem(index);
    float value = strtof(substring.start, &substring.end);
    return value;
}

float TuningDataFileReader::arrayItemRatioToVoltage(int index) {
    Substring substring = arrayItem(index);

    Substring topsubstring;
    topsubstring.start = substring.start;
    topsubstring.end = strchr(substring.start, '/');

    Substring bottomsubstring;
    bottomsubstring.start = topsubstring.end + 1;
    bottomsubstring.end = substring.end;

    int top = strtol(topsubstring.start, &topsubstring.end, 10);
    int bottom = strtol(bottomsubstring.start, &bottomsubstring.end, 10);

    float value = (float)top / (float)bottom;
    return log(value) / log(2);
}