#include "TensorflowModel.h"


void TensorflowModel::init() {

}

TfLiteStatus TensorflowModel::registerOps() {
    TF_LITE_ENSURE_STATUS(tflOpsResolver.AddFullyConnected());
    TF_LITE_ENSURE_STATUS(tflOpsResolver.AddLogistic());
    return kTfLiteOk;
}

void TensorflowModel::loadModel(unsigned char* data) {
    Serial.println("TensorflowModel::setData");

    tflModel = tflite::GetModel(data);
    if(tflModel->version() != TFLITE_SCHEMA_VERSION) {
        Serial.println("Model schema version mismatch!");
        Serial.println(tflModel->version());
        Serial.println(TFLITE_SCHEMA_VERSION);
        return;
    }

    TfLiteStatus s = registerOps();
    if(s != kTfLiteOk) {
        Serial.println("registerOps failed!");
        return;
    }

    tflInterpreter = new tflite::MicroInterpreter(tflModel, tflOpsResolver, tensorArena, TENSOR_ARENA_SIZE);
    s = tflInterpreter->AllocateTensors();
    if(s != kTfLiteOk) {
        Serial.println("AllocateTensors failed!");
        return;
    }

    input = tflInterpreter->input(0);
    output = tflInterpreter->output(0);

    Serial.print("Loaded model with ");
    Serial.print(input->dims->data[1]);
    Serial.print(" inputs and ");
    Serial.print(output->dims->data[1]);
    Serial.println(" outputs");




    // inference
    // input->data.f[0] = -1;
    // s = tflInterpreter->Invoke();
    // if(s != kTfLiteOk) {
    //     Serial.println("Invoke failed!");
    //     return;
    // }
    // float out1 = output->data.f[0];
    // float out2 = output->data.f[1];
    // Serial.println(out1);
    // Serial.println(out2);
}