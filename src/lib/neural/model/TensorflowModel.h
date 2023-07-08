#ifndef TensorflowModel_h
#define TensorflowModel_h

#include <Arduino.h>
#include <eurorack.h>

#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"

// #include "tensorflow/lite/micro/micro_log.h"
// #include "tensorflow/lite/micro/system_setup.h"
// #include "tensorflow/lite/schema/schema_generated.h"

class Metadata {
    public:
        Metadata() {}
        char type[6];
        uint8_t data[6];
};


class TensorflowModel {

    public:
        TensorflowModel(MemPool<>& memPool) : memPool(memPool) { init(); }
        void init();
        void loadModel(unsigned char* data);
        Metadata& getMetadata() { return metadata; }
        bool checkType(const char* type);
        int inputSize();
        int outputSize();
        void setInput(int index, float value);
        float getOutput(int index);
        float* getOutput();
        void runInference();

    private:
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