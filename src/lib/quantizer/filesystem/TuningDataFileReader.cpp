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
