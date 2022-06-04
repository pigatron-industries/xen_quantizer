#include <initializer_list>
#include "../src/lib/quantizer/ScaleFactory.h"

class ScaleFactoryTest {
    public:
        static Tuning tuning;
        static ChordDef chordDef;
        static Scale scale;

        static void test_createChord(Note rootNote, Note expectedNote1, Note expectedNote2, Note expectedNote3);
};

void test_ScaleFactory();
