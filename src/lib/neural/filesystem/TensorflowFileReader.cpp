#include "TensorflowFileReader.h"


bool TensorflowFileReader::read(FsFile& file) {
    bool s = BufferFileReader::read(file);
    if(s) {
        model.loadModel(buffer);
    }
    return s;
}