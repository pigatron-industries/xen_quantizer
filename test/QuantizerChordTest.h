#include <initializer_list>
#include "../src/lib/quantizer/QuantizerChord.h"
#include "../src/lib/quantizer/Scale.h"
#include "../src/lib/quantizer/Tuning.h"

class QuantizerChordTest {
    public:
        static Tuning tuning;
        static Scale scale;
        static ChordDef chordDef;
        static QuantizerChord quantizer;
        static Chord chord;

        static void test_quantize(float input, Note expectedNote);
};

void test_QuantizerChord();
