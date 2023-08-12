#ifndef TensorflowModel_h
#define TensorflowModel_h

#include <Arduino.h>
#include <eurorack.h>

#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"

#define METADATA_TYPE_SIZE 6
#define METADATA_DATA_SIZE 12
#define MODEL_NAME_SIZE 16


class Metadata {
    public:
        Metadata() {}
        char type[METADATA_TYPE_SIZE] = {'p', 'e', 'r', 'd', 'e', 'c'};
        uint8_t data[METADATA_DATA_SIZE] = {11, 16, 3, 5, 1, 1, 6, 2, 2, 1, 1, 1};
        // uint8_t test[1];
};


class TensorflowModel {

    public:
        TensorflowModel(MemPool<>& memPool) : memPool(memPool) { init(); }
        void init();
        void loadModel(unsigned char* data);
        // void setName(const char* name) { strncpy(this->name, name, MODEL_NAME_SIZE); }
        // char* getName() { return name; }
        Metadata& getMetadata() { return metadata; }
        bool checkType(const char* type);
        int inputSize();
        int outputSize();
        void setInput(int index, float value);
        float getOutput(int index);
        float* getOutput();
        void runInference();

    private:
        // char name[MODEL_NAME_SIZE+1] = {0};

        MemPool<>& memPool;

        tflite::MicroMutableOpResolver<3> tflOpsResolver;
        const tflite::Model* tflModel = nullptr;
        Metadata metadata;

        tflite::MicroInterpreter* tflInterpreter = nullptr;
        TfLiteTensor* input = nullptr;
        TfLiteTensor* output = nullptr;

        TfLiteStatus registerOps();
        void loadMetadata();

};

#endif