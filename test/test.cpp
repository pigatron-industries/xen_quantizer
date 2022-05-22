#include <unity.h>

#include "TuningTest.h"
#include "ScaleTest.h"
#include "PitchQuantizerTest.h"

#include "../src/lib/quantizer/PitchQuantizer.cpp"
#include "../src/lib/quantizer/Scale.cpp"
#include "../src/lib/quantizer/Tuning.cpp"


int main() {
    UNITY_BEGIN();
    test_Tuning();
    test_Scale();
    test_PitchQuantizer();
    return UNITY_END();
}
