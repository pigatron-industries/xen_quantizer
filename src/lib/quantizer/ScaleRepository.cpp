#include "ScaleRepository.h"

void ScaleRepository::clear() {
    scales.clear();
}

int ScaleRepository::addScale(Scale& scale) {
    int scaleIndex = scales.add(scale);
    return scaleIndex;
}
