#include "TensorflowModelManager.h"
#include "TensorflowFileReader.h"

void TensorflowModelManager::init() {
    Serial.println("TensorflowModelManager::init");  
    fs.cd("/");
    FileList& files = fs.ls();
    for(int i = 0; i < files.getSize(); i++) {
        FileInfo& file = files.getFile(i);
        Serial.println(file.filepath);  
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
    // BufferFileReader fileReader = BufferFileReader(memPool);
    fs.read(file.filepath, &fileReader);

    
    // model.loadModel(fileReader.getBuffer());

    // model.setData(toy_decoder_tflite);

    return model;
}