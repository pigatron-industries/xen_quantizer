#include <initializer_list>
#include "../src/lib/quantizer/QuantizerScale.h"
#include "../src/lib/quantizer/model/Scale.h"
#include "../src/lib/quantizer/model/Tuning.h"

class QuantizerScaleTest {
    public:
        static Tuning tuning;
        static Scale scale;
        static QuantizerScale quantizer;

        static void test_quantize(float input, Note expectedNote);
};

void test_QuantizerScale();
