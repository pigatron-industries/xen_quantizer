#include <unity.h>
#include <math.h>
#include <initializer_list>

#include "QuantizerScaleTest.h"

Tuning QuantizerScaleTest::tuning = Tuning({
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

Scale QuantizerScaleTest::scale = Scale(QuantizerScaleTest::tuning, {0, 2, 4, 5, 7, 9, 11});
QuantizerScale QuantizerScaleTest::quantizer = QuantizerScale(QuantizerScaleTest::scale);


void QuantizerScaleTest::test_quantize(float input, Note expectedNote) {
    Note note = quantizer.quantize(input);
    TEST_ASSERT_EQUAL_INT(expectedNote.cycle, note.cycle);
    TEST_ASSERT_EQUAL_INT(expectedNote.note, note.note);
    TEST_ASSERT_EQUAL_FLOAT(expectedNote.voltage, note.voltage);
}

void test_quantizeScale() {
    QuantizerScaleTest::scale.setOffset(0);

    // 1st octave positive voltages
    QuantizerScaleTest::test_quantize(0,     Note(0, 0,  0));
    QuantizerScaleTest::test_quantize(0.083, Note(0, 0,  0));
    QuantizerScaleTest::test_quantize(0.084, Note(0, 2,  0.1666667));
    QuantizerScaleTest::test_quantize(0.25,  Note(0, 2,  0.1666667));
    QuantizerScaleTest::test_quantize(0.251, Note(0, 4,  0.3333334));
    QuantizerScaleTest::test_quantize(0.375, Note(0, 4,  0.3333334));
    QuantizerScaleTest::test_quantize(0.376, Note(0, 5,  0.4166667));
    QuantizerScaleTest::test_quantize(0.958, Note(0, 11, 0.9166667));
    QuantizerScaleTest::test_quantize(0.959, Note(1, 0,  1));

    // 2nd octave positive voltages
    QuantizerScaleTest::test_quantize(1,     Note(1, 0,  1));
    QuantizerScaleTest::test_quantize(1.083, Note(1, 0,  1));
    QuantizerScaleTest::test_quantize(1.084, Note(1, 2,  1.1666667));
    QuantizerScaleTest::test_quantize(2,     Note(2, 0,  2));
    QuantizerScaleTest::test_quantize(5,     Note(5, 0,  5));

    // negative voltages
    QuantizerScaleTest::test_quantize(-0.041, Note(0,  0,  0));
    QuantizerScaleTest::test_quantize(-0.042, Note(-1, 11, -0.08333332));
    QuantizerScaleTest::test_quantize(-0.916, Note(-1,  2, -0.8333333));
    QuantizerScaleTest::test_quantize(-0.917, Note(-1,  0, -1));
    QuantizerScaleTest::test_quantize(-1,     Note(-1,  0, -1));
    QuantizerScaleTest::test_quantize(-2,     Note(-2,  0, -2));
    QuantizerScaleTest::test_quantize(-5,     Note(-5,  0, -5));

    //offset
    QuantizerScaleTest::scale.setOffset(0.5);
    QuantizerScaleTest::test_quantize(0.5,   Note(0, 0,  0.5));
    QuantizerScaleTest::test_quantize(0.667, Note(0, 2,  0.6666667));
    QuantizerScaleTest::test_quantize(0.99,  Note(0, 5,  0.9166667));
    QuantizerScaleTest::test_quantize(1.08,  Note(0, 7,  1.083333));
    QuantizerScaleTest::test_quantize(1.25,  Note(0, 9,  1.25));
    QuantizerScaleTest::test_quantize(1.5,   Note(1, 0,  1.5));

    QuantizerScaleTest::test_quantize(0.417, Note(-1, 11, 0.4166667));
    QuantizerScaleTest::test_quantize(0.25,  Note(-1, 9,  0.25));
    QuantizerScaleTest::test_quantize(0,     Note(-1, 7,  0.08333332));
    QuantizerScaleTest::test_quantize(-0.01, Note(-1, 5,  -0.08333332));
    QuantizerScaleTest::test_quantize(-0.16, Note(-1, 4,  -0.1666666));
}

void test_QuantizerScale() {
    RUN_TEST(test_quantizeScale);
}