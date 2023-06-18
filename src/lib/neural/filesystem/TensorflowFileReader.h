#ifndef TensorflowFileReader_h
#define TensorflowFileReader_h

#include <eurorack_sd.h>
#include "../model/TensorflowModel.h"

class TensorflowFileReader : public BufferFileReader {

    public:
        TensorflowFileReader(MemPool<>& memPool, TensorflowModel& model) : BufferFileReader(memPool), model(model) {};
        bool read(FsFile& file);
        TensorflowModel& getModel() { return model; }

    private:
        TensorflowModel& model;

};

#endif