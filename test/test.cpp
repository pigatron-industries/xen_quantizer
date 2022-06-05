#include <unity.h>

#include "TuningTest.h"
#include "ScaleTest.h"
#include "QuantizerChromaticTest.h"
#include "QuantizerScaleTest.h"
#include "QuantizerChordTest.h"
#include "ScaleFactoryTest.h"

#include "../src/lib/quantizer/Scale.cpp"
#include "../src/lib/quantizer/Tuning.cpp"
#include "../src/lib/quantizer/QuantizerChromatic.cpp"
#include "../src/lib/quantizer/QuantizerScale.cpp"
#include "../src/lib/quantizer/QuantizerChord.cpp"
#include "../src/lib/quantizer/ScaleFactory.cpp"


int main() {
    UNITY_BEGIN();
    test_Tuning();
    test_Scale();
    test_ScaleFactory();
    test_QuantizerChromatic();
    test_QuantizerScale();
    test_QuantizerChord();
    return UNITY_END();
}
