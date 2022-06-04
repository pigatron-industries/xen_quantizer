#include <unity.h>
#include <math.h>
#include <initializer_list>

#include "QuantizerChromaticTest.h"

Tuning QuantizerChromaticTest::tuning = Tuning({
    Interval(0, 0), 
    Interval(1/12.0, 7),
    Interval(2/12.0, 6),
    Interval(3/12.0, 5),
    Interval(4/12.0, 3),
    Interval(5/12.0, 2),
    Interval(6/12.0, 5),
    Interval(7/12.0, 1),
    Interval(8/12.0, 5),
    Interval(9/12.0, 4),
    Interval(10/12.0, 5),
    Interval(11/12.0, 7)}, 
    1.0);

QuantizerChromatic QuantizerChromaticTest::quantizer = QuantizerChromatic(QuantizerChromaticTest::tuning);


void QuantizerChromaticTest::test_quantize(float input, Note expectedNote) {
    Note note = quantizer.quantize(input);
    TEST_ASSERT_EQUAL_INT(expectedNote.cycle, note.cycle);
    TEST_ASSERT_EQUAL_INT(expectedNote.note, note.note);
    TEST_ASSERT_EQUAL_FLOAT(expectedNote.voltage, note.voltage);
}

void test_quantizeChromatic() {
    // 1st octave positive voltages
    QuantizerChromaticTest::test_quantize(0,     Note(0, 0,  0));
    QuantizerChromaticTest::test_quantize(0.083, Note(0, 1,  0.08333334));
    QuantizerChromaticTest::test_quantize(0.25,  Note(0, 3,  0.25));
    QuantizerChromaticTest::test_quantize(0.375, Note(0, 4,  0.3333334));
    QuantizerChromaticTest::test_quantize(0.376, Note(0, 5,  0.4166667));
    QuantizerChromaticTest::test_quantize(0.916, Note(0, 11, 0.9166667));
    QuantizerChromaticTest::test_quantize(0.959, Note(1, 0,  1));

    // 2nd octave positive voltages
    QuantizerChromaticTest::test_quantize(1,     Note(1, 0,  1));
    QuantizerChromaticTest::test_quantize(1.083, Note(1, 1,  1.08333334));
    QuantizerChromaticTest::test_quantize(2,     Note(2, 0,  2));
    QuantizerChromaticTest::test_quantize(5,     Note(5, 0,  5));

    // negative voltages
    QuantizerChromaticTest::test_quantize(-0.041, Note(0,  0,  0));
    QuantizerChromaticTest::test_quantize(-0.916, Note(-1,  1, -0.9166667));
    QuantizerChromaticTest::test_quantize(-1,     Note(-1,  0, -1));
    QuantizerChromaticTest::test_quantize(-2,     Note(-2,  0, -2));
    QuantizerChromaticTest::test_quantize(-5,    Note( -5,  0, -5));
}

void test_QuantizerChromatic() {
    RUN_TEST(test_quantizeChromatic);
}