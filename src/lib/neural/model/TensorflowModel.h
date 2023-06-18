#ifndef TensorflowModel_h
#define TensorflowModel_h

#include <Arduino.h>
#include <eurorack.h>

#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"

// #include "tensorflow/lite/micro/micro_log.h"
// #include "tensorflow/lite/micro/system_setup.h"
// #include "tensorflow/lite/schema/schema_generated.h"

#define TENSOR_ARENA_SIZE 2 * 1024


class TensorflowModel {

    public:
        TensorflowModel(MemPool<>& memPool) : memPool(memPool) {}
        void init();
        void loadModel(unsigned char* data);

    private:
        MemPool<>& memPool;

        tflite::MicroMutableOpResolver<2> tflOpsResolver;
        const tflite::Model* tflModel = nullptr;

        uint8_t tensorArena[TENSOR_ARENA_SIZE];
        tflite::MicroInterpreter* tflInterpreter = nullptr;
        TfLiteTensor* input = nullptr;
        TfLiteTensor* output = nullptr;

        TfLiteStatus registerOps();

        // tflite::MicroInterpreter* tflInterpreter = nullptr;
        // TfLiteTensor* tflInputTensor = nullptr;
        // TfLiteTensor* tflOutputTensor = nullptr;


};

#endif