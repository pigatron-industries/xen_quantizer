#include <unity.h>
#include <math.h>
#include <initializer_list>

#include "PitchQuantizerTest.h"

Tuning PitchQuantizerTest::tuning = Tuning(12);
ChordDef PitchQuantizerTest::chordDef = ChordDef({0, 2, 4, 6});
Scale PitchQuantizerTest::scale = Scale(PitchQuantizerTest::tuning, {0, 2, 4, 5, 7, 9, 11}, PitchQuantizerTest::chordDef);
PitchQuantizer PitchQuantizerTest::pitchQuantizer = PitchQuantizer(PitchQuantizerTest::tuning, PitchQuantizerTest::scale);


void PitchQuantizerTest::test_quantizeToScale(float input, int expectedRepeat, int expectedNote, float expectedOutput) {
    Note note = PitchQuantizerTest::pitchQuantizer.quantizeToScale(input);
    TEST_ASSERT_EQUAL_INT(expectedRepeat, note.cycle);
    TEST_ASSERT_EQUAL_INT(expectedNote, note.note);
    TEST_ASSERT_EQUAL_FLOAT(expectedOutput, note.voltage);
}

void test_quantizeToScale() {
    PitchQuantizerTest::pitchQuantizer.setScaleOffset(0);

    // 1st octave positive voltages
    PitchQuantizerTest::test_quantizeToScale(0,     0, 0,  0);
    PitchQuantizerTest::test_quantizeToScale(0.083, 0, 0,  0);
    PitchQuantizerTest::test_quantizeToScale(0.084, 0, 2,  0.1666667);
    PitchQuantizerTest::test_quantizeToScale(0.25,  0, 2,  0.1666667);
    PitchQuantizerTest::test_quantizeToScale(0.251, 0, 4,  0.3333334);
    PitchQuantizerTest::test_quantizeToScale(0.375, 0, 4,  0.3333334);
    PitchQuantizerTest::test_quantizeToScale(0.376, 0, 5,  0.4166667);
    PitchQuantizerTest::test_quantizeToScale(0.958, 0, 11, 0.9166667);
    PitchQuantizerTest::test_quantizeToScale(0.959, 1, 0,  1);

    // 2nd octave positive voltages
    PitchQuantizerTest::test_quantizeToScale(1,     1, 0,  1);
    PitchQuantizerTest::test_quantizeToScale(1.083, 1, 0,  1);
    PitchQuantizerTest::test_quantizeToScale(1.084, 1, 2,  1.1666667);
    PitchQuantizerTest::test_quantizeToScale(2,     2, 0,  2);
    PitchQuantizerTest::test_quantizeToScale(5,     5, 0,  5);

    // negative voltages
    PitchQuantizerTest::test_quantizeToScale(-0.041, 0,  0,  0);
    PitchQuantizerTest::test_quantizeToScale(-0.042, -1, 11, -0.08333332);
    PitchQuantizerTest::test_quantizeToScale(-0.916, -1,  2, -0.8333333);
    PitchQuantizerTest::test_quantizeToScale(-0.917, -1,  0, -1);
    PitchQuantizerTest::test_quantizeToScale(-1,     -1,  0, -1);
    PitchQuantizerTest::test_quantizeToScale(-2,     -2,  0, -2);
    PitchQuantizerTest::test_quantizeToScale(-5,     -5,  0, -5);

    //offset
    PitchQuantizerTest::pitchQuantizer.setScaleOffset(0.5);
    PitchQuantizerTest::test_quantizeToScale(0.5,   0, 0,  0.5);
    PitchQuantizerTest::test_quantizeToScale(0.667, 0, 2,  0.6666667);
    PitchQuantizerTest::test_quantizeToScale(1,     0, 5,  0.9166667);
    PitchQuantizerTest::test_quantizeToScale(1.08,  0, 7,  1.083333);
    PitchQuantizerTest::test_quantizeToScale(1.25,  0, 9,  1.25);
    PitchQuantizerTest::test_quantizeToScale(1.5,   1, 0,  1.5);

    PitchQuantizerTest::test_quantizeToScale(0.417, -1, 11, 0.4166667);
    PitchQuantizerTest::test_quantizeToScale(0.25,  -1, 9,  0.25);
    PitchQuantizerTest::test_quantizeToScale(0,     -1, 5,  -0.08333332);
    PitchQuantizerTest::test_quantizeToScale(-0.01, -1, 5,  -0.08333332);
    PitchQuantizerTest::test_quantizeToScale(-0.16, -1, 4,  -0.1666666);
}

void PitchQuantizerTest::test_createChord(Note rootNote, Note expectedNote1, Note expectedNote2, Note expectedNote3) {
    Chord chord = pitchQuantizer.createChord(chordDef, rootNote);
    TEST_ASSERT_EQUAL_INT(chord.size(), 4);
    TEST_ASSERT_EQUAL_INT(expectedNote1.cycle, chord[0].cycle);
    TEST_ASSERT_EQUAL_INT(expectedNote1.note,  chord[0].note);
    TEST_ASSERT_EQUAL_INT(expectedNote2.cycle, chord[1].cycle);
    TEST_ASSERT_EQUAL_INT(expectedNote2.note,  chord[1].note);
    TEST_ASSERT_EQUAL_INT(expectedNote3.cycle, chord[2].cycle);
    TEST_ASSERT_EQUAL_INT(expectedNote3.note,  chord[2].note);
}

void test_createChord() {
    PitchQuantizerTest::scale.setOffset(0);

    PitchQuantizerTest::test_createChord(Note(0, 0),  Note(0, 0),  Note(0, 4),  Note(0, 7)); // C Major
    PitchQuantizerTest::test_createChord(Note(0, 2),  Note(0, 2),  Note(0, 5),  Note(0, 9)); // D Minor
    PitchQuantizerTest::test_createChord(Note(0, 4),  Note(0, 4),  Note(0, 7),  Note(0, 11));// E Minor
    PitchQuantizerTest::test_createChord(Note(0, 5),  Note(0, 5),  Note(0, 9),  Note(1, 0)); // F Major
    PitchQuantizerTest::test_createChord(Note(0, 7),  Note(0, 7),  Note(0, 11), Note(1, 2)); // G Major
    PitchQuantizerTest::test_createChord(Note(0, 9),  Note(0, 9),  Note(1, 0),  Note(1, 4)); // A Minor
    PitchQuantizerTest::test_createChord(Note(0, 11), Note(0, 11), Note(1, 2),  Note(1, 5)); // B Diminished
 
    // +1 octave
    PitchQuantizerTest::test_createChord(Note(1, 0),  Note(1, 0),  Note(1, 4),  Note(1, 7)); // C Major
    PitchQuantizerTest::test_createChord(Note(1, 2),  Note(1, 2),  Note(1, 5),  Note(1, 9)); // D Minor
    PitchQuantizerTest::test_createChord(Note(1, 4),  Note(1, 4),  Note(1, 7),  Note(1, 11));// E Minor
    PitchQuantizerTest::test_createChord(Note(1, 5),  Note(1, 5),  Note(1, 9),  Note(2, 0)); // F Major
    PitchQuantizerTest::test_createChord(Note(1, 7),  Note(1, 7),  Note(1, 11), Note(2, 2)); // G Major
    PitchQuantizerTest::test_createChord(Note(1, 9),  Note(1, 9),  Note(2, 0),  Note(2, 4)); // A Minor
    PitchQuantizerTest::test_createChord(Note(1, 11), Note(1, 11), Note(2, 2),  Note(2, 5)); // B Diminished

    // -1 octave
    PitchQuantizerTest::test_createChord(Note(-1, 0),  Note(-1, 0),  Note(-1, 4),  Note(-1, 7)); // C Major
    PitchQuantizerTest::test_createChord(Note(-1, 2),  Note(-1, 2),  Note(-1, 5),  Note(-1, 9)); // D Minor
    PitchQuantizerTest::test_createChord(Note(-1, 4),  Note(-1, 4),  Note(-1, 7),  Note(-1, 11));// E Minor
    PitchQuantizerTest::test_createChord(Note(-1, 5),  Note(-1, 5),  Note(-1, 9),  Note(0, 0)); // F Major
    PitchQuantizerTest::test_createChord(Note(-1, 7),  Note(-1, 7),  Note(-1, 11), Note(0, 2)); // G Major
    PitchQuantizerTest::test_createChord(Note(-1, 9),  Note(-1, 9),  Note(0, 0),  Note(0, 4)); // A Minor
    PitchQuantizerTest::test_createChord(Note(-1, 11), Note(-1, 11), Note(0, 2),  Note(0, 5)); // B Diminished
}

void test_PitchQuantizer() {
    RUN_TEST(test_quantizeToScale);
    RUN_TEST(test_createChord);
}