#include "TuningRepository.h"

void TuningRepository::clear() {
    scales.clear();
}

int TuningRepository::addScale(Scale& scale) {
    int scaleIndex = scales.add(scale);
    return scaleIndex;
}
