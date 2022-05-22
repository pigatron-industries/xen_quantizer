#include <initializer_list>
#include "../src/lib/quantizer/PitchQuantizer.h"
#include "../src/lib/quantizer/Scale.h"
#include "../src/lib/quantizer/Tuning.h"

class PitchQuantizerTest {
    public:
        static Tuning tuning;
        static ChordDef chordDef;
        static Scale scale;
        static PitchQuantizer pitchQuantizer;

        static void test_quantizeToScale(float input, int expectedRepeat, int expectedNote, float expectedOutput);
};

void test_PitchQuantizer();
