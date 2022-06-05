#include <unity.h>
#include <math.h>
#include <initializer_list>

#include "QuantizerChordTest.h"
#include "../src/lib/quantizer/ScaleFactory.h"

Tuning QuantizerChordTest::tuning = Tuning({
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

Scale QuantizerChordTest::scale = Scale(QuantizerChordTest::tuning, {0, 2, 4, 5, 7, 9, 11});
ChordDef QuantizerChordTest::chordDef = ChordDef({0, 2, 4, 6});
Chord QuantizerChordTest::chord;

QuantizerChord QuantizerChordTest::quantizer = QuantizerChord(QuantizerChordTest::scale, QuantizerChordTest::chord);


void QuantizerChordTest::test_quantize(float input, Note expectedNote) {
    Note note = quantizer.quantize(input);
    TEST_ASSERT_EQUAL_INT(expectedNote.cycle, note.cycle);
    TEST_ASSERT_EQUAL_INT(expectedNote.note, note.note);
    TEST_ASSERT_FLOAT_WITHIN(0.000001, expectedNote.voltage, note.voltage);
}

void test_quantizeChord() {
    QuantizerChordTest::scale.setOffset(0);

    //C Major
    Note root = Note(0, 0);
    QuantizerChordTest::chord = ScaleFactory::createChord(QuantizerChordTest::scale, QuantizerChordTest::chordDef, root);

    QuantizerChordTest::test_quantize(0,    Note(0, 0,  0));
    QuantizerChordTest::test_quantize(0.33, Note(0, 4,  4/12.0));
    QuantizerChordTest::test_quantize(0.58, Note(0, 7,  7/12.0));
    QuantizerChordTest::test_quantize(0.91, Note(0, 11, 11/12.0));

    QuantizerChordTest::test_quantize(1,    Note(1, 0,  1));
    QuantizerChordTest::test_quantize(1.33, Note(1, 4,  1+4/12.0));
    QuantizerChordTest::test_quantize(1.58, Note(1, 7,  1+7/12.0));
    QuantizerChordTest::test_quantize(1.91, Note(1, 11, 1+11/12.0));

    QuantizerChordTest::test_quantize(-1,    Note(-1, 0,  -1));
    QuantizerChordTest::test_quantize(-0.67, Note(-1, 4,  -1+4/12.0));
    QuantizerChordTest::test_quantize(-0.42, Note(-1, 7,  -1+7/12.0));
    QuantizerChordTest::test_quantize(-0.09, Note(-1, 11, -1+11/12.0));

    // D Minor
    root = Note(0, 2);
    QuantizerChordTest::chord = ScaleFactory::createChord(QuantizerChordTest::scale, QuantizerChordTest::chordDef, root);

    QuantizerChordTest::test_quantize(0,    Note(0, 0, 0));
    QuantizerChordTest::test_quantize(0.16, Note(0, 2, 2/12.0));
    QuantizerChordTest::test_quantize(0.41, Note(0, 5, 5/12.0));
    QuantizerChordTest::test_quantize(0.75, Note(0, 9, 9/12.0));

    QuantizerChordTest::test_quantize(1,    Note(1, 0, 1));
    QuantizerChordTest::test_quantize(1.16, Note(1, 2, 1+2/12.0));
    QuantizerChordTest::test_quantize(1.41, Note(1, 5, 1+5/12.0));
    QuantizerChordTest::test_quantize(1.75, Note(1, 9, 1+9/12.0));

    // E Minor
    root = Note(0, 4);
    QuantizerChordTest::chord = ScaleFactory::createChord(QuantizerChordTest::scale, QuantizerChordTest::chordDef, root);

    QuantizerChordTest::test_quantize(0.16, Note(0, 2, 2/12.0));
    QuantizerChordTest::test_quantize(0.33, Note(0, 4, 4/12.0));
    QuantizerChordTest::test_quantize(0.58, Note(0, 7, 7/12.0));
    QuantizerChordTest::test_quantize(0.91, Note(0, 11, 11/12.0));

    QuantizerChordTest::test_quantize(1.16, Note(1, 2, 1+2/12.0));
    QuantizerChordTest::test_quantize(1.33, Note(1, 4, 1+4/12.0));
    QuantizerChordTest::test_quantize(1.58, Note(1, 7, 1+7/12.0));
    QuantizerChordTest::test_quantize(1.91, Note(1, 11, 1+11/12.0));

    //
    QuantizerChordTest::scale.setOffset(1/12.0);
    root = Note(0, 0, 1/12.0);
    QuantizerChordTest::chord = ScaleFactory::createChord(QuantizerChordTest::scale, QuantizerChordTest::chordDef, root);

    QuantizerChordTest::test_quantize(0, Note(-1, 11, 0));
    QuantizerChordTest::test_quantize(1/12.0, Note(0, 0, 1/12.0));

    //
    QuantizerChordTest::scale.setOffset(2/12.0);
    root = Note(0, 0, 2/12.0);
    QuantizerChordTest::chord = ScaleFactory::createChord(QuantizerChordTest::scale, QuantizerChordTest::chordDef, root);

    QuantizerChordTest::test_quantize(0, Note(-1, 11, 1/12.0));
    // QuantizerChordTest::test_quantize(1/12.0, Note(0, 0, 1/12.0));
}

void test_QuantizerChord() {
    RUN_TEST(test_quantizeChord);
}