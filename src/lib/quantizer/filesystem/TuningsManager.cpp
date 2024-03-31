#include "TuningsManager.h"
#include "TuningDataFileReader.h"

void TuningsManager::init() {
    Serial.println("TuningsManager::init");  
    fs.cd("/");
    FileList& files = fs.ls();
    for(int i = 0; i < files.size(); i++) {
        FileInfo& file = files.get(i);
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
    return fs.ls().size();
}

FileInfo& TuningsManager::getFileInfo(int index) {
    fs.cd("/");
    return fs.ls().get(index);
}

TuningData& TuningsManager::loadTuningData(int index) {
    clear();

    fs.cd("/");
    FileInfo& file = fs.ls().get(index);
    Serial.print("Loading tuning: ");
    Serial.println(file.filepath);
    TuningDataFileReader fileReader = TuningDataFileReader(*this);
    fs.read(file.filepath, &fileReader);

    return tuningData;
}

Tuning* TuningsManager::addTuning(Tuning& tuning) {
    tuningData.tuning = tuningsManager.add(tuning, &memPool);
    return tuningData.tuning;
}

Scale* TuningsManager::addScale(Scale& scale) {
    Scale* newScale = scalesManager.add(scale, &memPool);
    tuningData.addScale(newScale);
    return newScale;
}
