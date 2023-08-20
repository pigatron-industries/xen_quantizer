#include "QuantizerDifferential.h"

float QuantizerDifferential::quantize(float root, float voltage, int intervalIndex) {
    Interval& interval = tuning->getInterval(intervalIndex);
    float quantized = quantizeToMultiple(voltage, interval.voltage, root);
    return quantized;
}

float QuantizerDifferential::quantizeToMultiple(float input, float multiple, float offset) {
    return round((input - offset) / multiple) * multiple + offset;
}