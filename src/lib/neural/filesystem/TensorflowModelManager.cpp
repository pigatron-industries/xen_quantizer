#include "TensorflowModelManager.h"
#include "TensorflowFileReader.h"

void TensorflowModelManager::init() {
    fs.cd("/");
    FileList& files = fs.ls();
    for(int i = 0; i < files.size(); i++) {
        FileInfo& file = files.get(i);
    }
}

void TensorflowModelManager::clear() {
    memPool.reset();
}

int TensorflowModelManager::getModelCount() {
    return fs.ls().size();
}

TensorflowModel& TensorflowModelManager::loadModel(int index) {
    clear();

    FileInfo& file = fs.ls().get(index);
    Serial.print("Loading model: ");
    Serial.println(file.filename);
    name = file.filename;
    TensorflowFileReader fileReader = TensorflowFileReader(memPool, model);
    fs.read(file.filepath, &fileReader);
    return model;
}