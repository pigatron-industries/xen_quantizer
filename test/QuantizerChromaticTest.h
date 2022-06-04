#include <initializer_list>
#include "../src/lib/quantizer/QuantizerChromatic.h"
#include "../src/lib/quantizer/Scale.h"
#include "../src/lib/quantizer/Tuning.h"

class QuantizerChromaticTest {
    public:
        static Tuning tuning;
        static QuantizerChromatic quantizer;

        static void test_quantize(float input, Note expectedNote);
};

void test_QuantizerChromatic();
