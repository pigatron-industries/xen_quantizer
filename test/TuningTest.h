#include <initializer_list>
#include "../src/lib/quantizer/model/Tuning.h"

class TuningTest {
    public:
        static Tuning tuning;

        static void test_createNote(int cycle, int note, float expectedVoltage);
        static void test_findCycle(float voltage, float offset, int expectedCycle);
};

void test_Tuning();
