#include "TensorflowModelManager.h"
#include "TensorflowFileReader.h"

void TensorflowModelManager::init() {
    fs.cd("/");
    FileList& files = fs.ls();
    for(int i = 0; i < files.getSize(); i++) {
        FileInfo& file = files.getFile(i);
    }
}

void TensorflowModelManager::clear() {
    memPool.reset();
}

int TensorflowModelManager::getModelCount() {
    // TODO
    return 0;
}

TensorflowModel& TensorflowModelManager::loadModel(int index) {
    clear();

    FileInfo& file = fs.ls().getFile(index);
    Serial.print("Loading model: ");
    Serial.println(file.filepath);
    TensorflowFileReader fileReader = TensorflowFileReader(memPool, model);
    fs.read(file.filepath, &fileReader);
    return model;
}