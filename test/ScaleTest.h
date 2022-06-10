#include <initializer_list>
#include "../src/lib/quantizer/model/Scale.h"
#include "../src/lib/quantizer/model/Tuning.h"

class ScaleTest {
    public:
        static Tuning tuning;
        static ChordDef chordDef;
        static Scale scale;

        static void test_firstLastNote(int offset, int cycle, int expectedFirstNote, int expectedLastNote);
        static void test_containsNote(int offset, int note, bool expectedContains);
        static void test_getNoteByIndex(int index, int expectedNote);
};

void test_Scale();
