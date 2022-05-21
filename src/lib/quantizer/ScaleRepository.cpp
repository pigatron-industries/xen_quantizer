#include "ScaleRepository.h"

void ScaleRepository::clear() {
    scales.clear();
}

int ScaleRepository::addScale(ScaleDef& scale) {
    int scaleIndex = scales.add(scale);
    return scaleIndex;
}
