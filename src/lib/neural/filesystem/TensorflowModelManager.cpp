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
    return fs.ls().getSize();
}

TensorflowModel& TensorflowModelManager::loadModel(int index) {
    clear();

    FileInfo& file = fs.ls().getFile(index);
    Serial.print("Loading model: ");
    Serial.println(file.filename);
    TensorflowFileReader fileReader = TensorflowFileReader(memPool, model);
    fs.read(file.filepath, &fileReader);
    // model.setName(file.filename);
    return model;
}