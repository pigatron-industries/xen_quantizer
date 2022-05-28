#include <initializer_list>
#include "../src/lib/quantizer/ScaleQuantizer.h"
#include "../src/lib/quantizer/Scale.h"
#include "../src/lib/quantizer/Tuning.h"

class ScaleQuantizerTest {
    public:
        static Tuning tuning;
        static ChordDef chordDef;
        static Scale scale;
        static ScaleQuantizer scaleQuantizer;

        static void test_quantizeToScale(float input, int expectedRepeat, int expectedNote, float expectedOutput);
        static void test_createChord(Note rootNote, Note expectedNote1, Note expectedNote2, Note expectedNote3);
};

void test_ScaleQuantizer();
