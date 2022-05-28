#include <unity.h>

#include "TuningTest.h"
#include "ScaleTest.h"
#include "ScaleQuantizerTest.h"

#include "../src/lib/quantizer/ScaleQuantizer.cpp"
#include "../src/lib/quantizer/Scale.cpp"
#include "../src/lib/quantizer/Tuning.cpp"


int main() {
    UNITY_BEGIN();
    test_Tuning();
    test_Scale();
    test_ScaleQuantizer();
    return UNITY_END();
}
