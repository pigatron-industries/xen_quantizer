#include <unity.h>
#include <math.h>
#include <initializer_list>

#include "ScaleFactoryTest.h"

Tuning ScaleFactoryTest::tuning = Tuning({
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

ChordDef ScaleFactoryTest::chordDef = ChordDef({0, 2, 4, 6});
Scale ScaleFactoryTest::scale = Scale(ScaleFactoryTest::tuning, {0, 2, 4, 5, 7, 9, 11}, ScaleFactoryTest::chordDef);

void ScaleFactoryTest::test_createChord(Note rootNote, Note expectedNote1, Note expectedNote2, Note expectedNote3) {
    test_createChord(rootNote, 0, 0, expectedNote1, expectedNote2, expectedNote3);
}

void ScaleFactoryTest::test_createChord(Note rootNote, int inversion, int drop, Note expectedNote1, Note expectedNote2, Note expectedNote3) {
    Chord chord = ScaleFactory::createChord(scale, chordDef, rootNote, inversion, drop);
    TEST_ASSERT_EQUAL_INT(chord.size(), 4);
    TEST_ASSERT_EQUAL_INT(expectedNote1.cycle, chord[0].cycle);
    TEST_ASSERT_EQUAL_INT(expectedNote1.note,  chord[0].note);
    TEST_ASSERT_EQUAL_FLOAT(expectedNote1.voltage,  chord[0].voltage);
    TEST_ASSERT_EQUAL_INT(expectedNote2.cycle, chord[1].cycle);
    TEST_ASSERT_EQUAL_INT(expectedNote2.note,  chord[1].note);
    TEST_ASSERT_EQUAL_INT(expectedNote3.cycle, chord[2].cycle);
    TEST_ASSERT_EQUAL_INT(expectedNote3.note,  chord[2].note);
}

void test_createChord() {
    ScaleFactoryTest::scale.setOffset(0);

    ScaleFactoryTest::test_createChord(Note(0, 0),  Note(0, 0),  Note(0, 4),  Note(0, 7)); // C Major
    ScaleFactoryTest::test_createChord(Note(0, 2),  Note(0, 2, 2/12.0),  Note(0, 5),  Note(0, 9)); // D Minor
    ScaleFactoryTest::test_createChord(Note(0, 4),  Note(0, 4, 4/12.0),  Note(0, 7),  Note(0, 11));// E Minor
    ScaleFactoryTest::test_createChord(Note(0, 5),  Note(0, 5, 5/12.0),  Note(0, 9),  Note(1, 0)); // F Major
    ScaleFactoryTest::test_createChord(Note(0, 7),  Note(0, 7, 7/12.0),  Note(0, 11), Note(1, 2)); // G Major
    ScaleFactoryTest::test_createChord(Note(0, 9),  Note(0, 9, 9/12.0),  Note(1, 0),  Note(1, 4)); // A Minor
    ScaleFactoryTest::test_createChord(Note(0, 11), Note(0, 11, 11/12.0), Note(1, 2),  Note(1, 5)); // B Diminished
 
    // +1 octave
    ScaleFactoryTest::test_createChord(Note(1, 0),  Note(1, 0, 1),  Note(1, 4),  Note(1, 7)); // C Major
    ScaleFactoryTest::test_createChord(Note(1, 2),  Note(1, 2, 1+2/12.0),  Note(1, 5),  Note(1, 9)); // D Minor
    ScaleFactoryTest::test_createChord(Note(1, 4),  Note(1, 4, 1+4/12.0),  Note(1, 7),  Note(1, 11));// E Minor
    ScaleFactoryTest::test_createChord(Note(1, 5),  Note(1, 5, 1+5/12.0),  Note(1, 9),  Note(2, 0)); // F Major
    ScaleFactoryTest::test_createChord(Note(1, 7),  Note(1, 7, 1+7/12.0),  Note(1, 11), Note(2, 2)); // G Major
    ScaleFactoryTest::test_createChord(Note(1, 9),  Note(1, 9, 1+9/12.0),  Note(2, 0),  Note(2, 4)); // A Minor
    ScaleFactoryTest::test_createChord(Note(1, 11), Note(1, 11, 1+11/12.0), Note(2, 2),  Note(2, 5)); // B Diminished

    // -1 octave
    ScaleFactoryTest::test_createChord(Note(-1, 0),  Note(-1, 0, -1),  Note(-1, 4),  Note(-1, 7)); // C Major
    ScaleFactoryTest::test_createChord(Note(-1, 2),  Note(-1, 2, -1+2/12.0),  Note(-1, 5),  Note(-1, 9)); // D Minor
    ScaleFactoryTest::test_createChord(Note(-1, 4),  Note(-1, 4, -1+4/12.0),  Note(-1, 7),  Note(-1, 11));// E Minor
    ScaleFactoryTest::test_createChord(Note(-1, 5),  Note(-1, 5, -1+5/12.0),  Note(-1, 9),  Note(0, 0)); // F Major
    ScaleFactoryTest::test_createChord(Note(-1, 7),  Note(-1, 7, -1+7/12.0),  Note(-1, 11), Note(0, 2)); // G Major
    ScaleFactoryTest::test_createChord(Note(-1, 9),  Note(-1, 9, -1+9/12.0),  Note(0, 0),  Note(0, 4)); // A Minor
    ScaleFactoryTest::test_createChord(Note(-1, 11), Note(-1, 11, -1+11/12.0), Note(0, 2),  Note(0, 5)); // B Diminished

    ScaleFactoryTest::scale.setOffset(1/12.0);
    ScaleFactoryTest::test_createChord(Note(0, 0, 1/12.0),  Note(0, 0, 1/12.0),  Note(0, 4),  Note(0, 7)); // C Major
}

void test_createChordInversion() {
    ScaleFactoryTest::scale.setOffset(0);

    ScaleFactoryTest::test_createChord(Note(0, 0),  1, 0, Note(1, 0, 1),  Note(0, 4),  Note(0, 7)); // C Major
    ScaleFactoryTest::test_createChord(Note(0, 0),  2, 0, Note(1, 0, 1),  Note(1, 4, 1+4/12),  Note(0, 7)); // C Major
    ScaleFactoryTest::test_createChord(Note(0, 0),  3, 0, Note(1, 0, 1),  Note(1, 4, 1+4/12),  Note(1, 7, 1+7/12)); // C Major

    ScaleFactoryTest::test_createChord(Note(0, 0),  0, 1, Note(0, 0),  Note(-1, 4),  Note(0, 7)); // C Major

    ScaleFactoryTest::test_createChord(Note(0, 0),  1, 1, Note(1, 0, 1),  Note(-1, 4),  Note(0, 7)); // C Major
}

void test_ScaleFactory() {
    RUN_TEST(test_createChord);
    RUN_TEST(test_createChordInversion);
}
