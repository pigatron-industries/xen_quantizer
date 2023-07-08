#include "TensorflowModel.h"
#include <eurorack.h>
#include "Hardware.h"


void TensorflowModel::init() {
    TfLiteStatus s = registerOps();
    if(s != kTfLiteOk) {
        Serial.println("registerOps failed!");
        return;
    }
}

TfLiteStatus TensorflowModel::registerOps() {
    TF_LITE_ENSURE_STATUS(tflOpsResolver.AddFullyConnected());
    TF_LITE_ENSURE_STATUS(tflOpsResolver.AddLogistic());
    TF_LITE_ENSURE_STATUS(tflOpsResolver.AddDequantize());
    return kTfLiteOk;
}

void TensorflowModel::loadModel(unsigned char* data) {
    Serial.println("TensorflowModel::loadModel");

    tflModel = tflite::GetModel(data);
    if(tflModel->version() != TFLITE_SCHEMA_VERSION) {
        Serial.println("Model schema version mismatch!");
        Serial.println(tflModel->version());
        Serial.println(TFLITE_SCHEMA_VERSION);
        return;
    }

    tflInterpreter = new tflite::MicroInterpreter(tflModel, tflOpsResolver, Hardware::tensorArena, TENSOR_ARENA_SIZE);
    TfLiteStatus s = tflInterpreter->AllocateTensors();
    if(s != kTfLiteOk) {
        Serial.println("AllocateTensors failed!");
        return;
    }

    input = tflInterpreter->input(0);
    output = tflInterpreter->output(0);

    loadMetadata();

    Serial.print("Loaded "); 
    Serial.write(metadata.type, 6);
    Serial.print(" model with ");
    Serial.print(input->dims->data[1]);
    Serial.print(" inputs and ");
    Serial.print(output->dims->data[1]);
    Serial.println(" outputs");
}

void TensorflowModel::loadMetadata() {
    for (uint32_t i=0; i < tflModel->metadata()->size(); i++) {
        const auto meta = tflModel->metadata()->Get(i);
        if (meta->name()->str() == "TFLITE_METADATA") {
            const flatbuffers::Vector<uint8_t> *pvec = tflModel->buffers()->Get(meta->buffer())->data();
            const char* buffer = reinterpret_cast<const char*>(pvec);
            const char* ptr = memmem(buffer, pvec->size(), "xen:", 4);
            if(ptr == nullptr) {
                Serial.println("xen metadata not found!");
                return;
            }
            ptr += 4;
            memcpy(metadata.type, ptr, 6);
            ptr += 6;
            memcpy(metadata.data, ptr, 6);
        }
    }
}

bool TensorflowModel::checkType(const char* type) {
    return memcmp(metadata.type, type, 6) == 0;
}

int TensorflowModel::inputSize() {
    return input->dims->data[1];
}

int TensorflowModel::outputSize() {
    return output->dims->data[1];
}

void TensorflowModel::setInput(int index, float value) {
    input->data.f[index] = value;
}

float TensorflowModel::getOutput(int index) {
    return output->data.f[index];
}

float* TensorflowModel::getOutput() {
    return output->data.f;
}

void TensorflowModel::runInference() {
    TfLiteStatus s = tflInterpreter->Invoke();
    if(s != kTfLiteOk) {
        Serial.println("Invoke failed!");
        return;
    }
}