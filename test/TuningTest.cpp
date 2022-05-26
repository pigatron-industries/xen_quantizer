#include <unity.h>
#include <math.h>
#include <initializer_list>
#include "TuningTest.h"

Tuning TuningTest::tuning = Tuning(12);

void TuningTest::test_createNote(int cycle, int note, float expectedVoltage) {
    Note createdNote = tuning.createNote(cycle, note);
    TEST_ASSERT_EQUAL_FLOAT(expectedVoltage, createdNote.voltage);
}

void test_createNote() {
    TuningTest::test_createNote(0, 0,  0);
    TuningTest::test_createNote(0, 1,  0.08333334);
    TuningTest::test_createNote(0, 2,  0.1666667);
    TuningTest::test_createNote(0, 3,  0.25);
    TuningTest::test_createNote(0, 4,  0.3333334);
    TuningTest::test_createNote(0, 5,  0.4166667);
    TuningTest::test_createNote(0, 6,  0.5);
    TuningTest::test_createNote(0, 7,  0.5833334);
    TuningTest::test_createNote(0, 8,  0.6666667);
    TuningTest::test_createNote(0, 9,  0.75);
    TuningTest::test_createNote(0, 10, 0.8333334);
    TuningTest::test_createNote(0, 11, 0.9166667);

    TuningTest::test_createNote(1, 0,  1);
    TuningTest::test_createNote(1, 1,  1.08333334);

    TuningTest::test_createNote(-1, 0,  -1);
    TuningTest::test_createNote(-1, 1,  -0.9166667);
    TuningTest::test_createNote(-1, 11, -0.08333334);
}

void TuningTest::test_findCycle(float voltage, float offset, int expectedCycle) {
    int cycle = tuning.findCycle(voltage, offset);
    TEST_ASSERT_EQUAL_INT(expectedCycle, cycle);
}

void test_findCycle() {
    TuningTest::test_findCycle(0,     0, 0);
    TuningTest::test_findCycle(0.5,   0, 0);
    TuningTest::test_findCycle(0.99,  0, 0);
    TuningTest::test_findCycle(1,     0, 1);
    TuningTest::test_findCycle(2,     0, 2);
    TuningTest::test_findCycle(-0.01, 0, -1);
    TuningTest::test_findCycle(-1,    0, -1);
    TuningTest::test_findCycle(-2,    0, -2);

    TuningTest::test_findCycle(0,     0.1, -1);
    TuningTest::test_findCycle(0.1,   0.1, 0);
    TuningTest::test_findCycle(1,     0.1, 0);
    TuningTest::test_findCycle(1.1,   0.1, 1);
    TuningTest::test_findCycle(-0.1,  0.1, -1);
    TuningTest::test_findCycle(-0.9,  0.1, -1);
    TuningTest::test_findCycle(-0.91, 0.1, -2);
    TuningTest::test_findCycle(-1,    0.1, -2);
}

void test_Tuning() {
    RUN_TEST(test_createNote);
    RUN_TEST(test_findCycle);
}
