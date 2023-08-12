#ifndef TensorflowModelManager_h
#define TensorflowModelManager_h

#include <eurorack.h>
#include <eurorack_sd.h>
#include "../model/TensorflowModel.h"

class TensorflowModelManager {
    public:
        TensorflowModelManager(FileSystem& fs, MemPool<>& memPool) : fs(fs), memPool(memPool), model(memPool) {}
        void init();
        void clear();
        int getModelCount();
        TensorflowModel& loadModel(int index);
        TensorflowModel& getModel() { return model; }
        char* getName() { return name; }

    private:
        FileSystem& fs;
        MemPool<>& memPool;

        // curently loaded model
        TensorflowModel model;
        char* name = "";

};

#endif