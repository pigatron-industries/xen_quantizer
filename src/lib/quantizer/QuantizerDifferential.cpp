#include "QuantizerDifferential.h"

float QuantizerDifferential::quantize(float root, float voltage, int intervalIndex) {
    float intervalVoltage = tuning->getIntervalVoltage(intervalIndex);
    float quantized = quantizeToMultiple(voltage, intervalVoltage, root);
    return quantized;
}

float QuantizerDifferential::quantizeToMultiple(float input, float multiple, float offset) {
    return round((input - offset) / multiple) * multiple + offset;
}