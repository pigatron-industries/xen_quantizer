#include "TuningsManager.h"
#include "TuningDataFileReader.h"

void TuningsManager::init() {
    fs.cd("/");
    FileList& files = fs.ls();
    for(int i = 0; i < files.getSize(); i++) {
        FileInfo& file = files.getFile(i);
        Serial.println(file.filepath);  
    }
}

void TuningsManager::clear() {
    tuningsManager.clear();
    scalesManager.clear();
    tuningData.scales.clear();
    tuningData.tuning = nullptr;
    memPool.reset();
}

int TuningsManager::getTuningCount() {
    return fs.ls().getSize();
}

TuningData& TuningsManager::loadTuningData(int index) {
    clear();

    FileInfo& file = fs.ls().getFile(index);
    TuningDataFileReader fileReader = TuningDataFileReader(*this);
    Serial.println(file.filepath);
    fs.read(file.filepath, &fileReader);

    return tuningData;
}

Tuning* TuningsManager::addTuning(Tuning& tuning) {
    tuningData.tuning = tuningsManager.add(tuning);
    return tuningData.tuning;
}

Scale* TuningsManager::addScale(Scale& scale) {
    Scale* newScale = scalesManager.add(scale);
    tuningData.addScale(newScale);
    return newScale;
}
