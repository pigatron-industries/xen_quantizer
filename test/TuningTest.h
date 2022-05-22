#include <initializer_list>
#include "../src/lib/quantizer/Tuning.h"

class TuningTest {
    public:
        static Tuning tuning;

        static void test_createNote(int cycle, int note, float expectedVoltage);
};

void test_Tuning();
