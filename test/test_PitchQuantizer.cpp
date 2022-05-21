#include <unity.h>
#include <math.h>
#include <initializer_list>
#include "../src/lib/quantizer/PitchQuantizer.cpp"
#include "../src/lib/quantizer/Tuning.cpp"

Tuning tuning = Tuning(12);

ChordDef chordDef = ChordDef({0, 2, 4, 6});
ScaleDef scaleDefs = ScaleDef({0, 2, 4, 5, 7, 9, 11}, chordDef);

PitchQuantizer pitchQuantizer = PitchQuantizer(tuning, scaleDefs);

void test_quantizeToScale(float input, int expectedRepeat, int expectedNote, float expectedOutput) {
    Note note = pitchQuantizer.quantizeToScale(input);
    TEST_ASSERT_EQUAL_INT(expectedRepeat, note.repeat);
    TEST_ASSERT_EQUAL_INT(expectedNote, note.note);
    TEST_ASSERT_EQUAL_FLOAT(expectedOutput, note.voltage);
}

void test_quantizeToScale() {
    pitchQuantizer.setScaleOffset(0);

    // 1st octave positive voltages
    test_quantizeToScale(0,     0, 0,  0);
    test_quantizeToScale(0.083, 0, 0,  0);
    test_quantizeToScale(0.084, 0, 2,  0.1666667);
    test_quantizeToScale(0.25,  0, 2,  0.1666667);
    test_quantizeToScale(0.251, 0, 4,  0.3333334);
    test_quantizeToScale(0.375, 0, 4,  0.3333334);
    test_quantizeToScale(0.376, 0, 5,  0.4166667);
    test_quantizeToScale(0.958, 0, 11, 0.9166667);
    test_quantizeToScale(0.959, 1, 0,  1);

    // 2nd octave positive voltages
    test_quantizeToScale(1,     1, 0,  1);
    test_quantizeToScale(1.083, 1, 0,  1);
    test_quantizeToScale(1.084, 1, 2,  1.1666667);
    test_quantizeToScale(2,     2, 0,  2);
    test_quantizeToScale(5,     5, 0,  5);

    // negative voltages
    test_quantizeToScale(-0.041, 0,  0,  0);
    test_quantizeToScale(-0.042, -1, 11, -0.08333332);
    test_quantizeToScale(-0.916, -1,  2, -0.8333333);
    test_quantizeToScale(-0.917, -1,  0, -1);
    test_quantizeToScale(-1,     -1,  0, -1);
    test_quantizeToScale(-2,     -2,  0, -2);
    test_quantizeToScale(-5,     -5,  0, -5);
}

void test_quantizeToScaleWithOffset() {
    pitchQuantizer.setScaleOffset(1);

    // 1st octave positive voltages
    test_quantizeToScale(0,     0, 0,  0);
    test_quantizeToScale(0.042, 0, 1,  0.08333334);
    test_quantizeToScale(0.083, 0, 1,  0.08333334);
    test_quantizeToScale(0.167, 0, 3,  0.25);
    test_quantizeToScale(0.333, 0, 3,  0.25);
    test_quantizeToScale(0.334, 0, 5,  0.4166667);
    test_quantizeToScale(0.458, 0, 5,  0.4166667);
    test_quantizeToScale(0.459, 0, 6,  0.5);
    test_quantizeToScale(0.459, 0, 6,  0.5);
    test_quantizeToScale(0.751, 0, 10, 0.8333334);
    test_quantizeToScale(0.916, 0, 10, 0.8333334);
    test_quantizeToScale(0.917, 1, 0,  1);
}

void test_createChord(Note rootNote, Note expectedNote1, Note expectedNote2, Note expectedNote3) {
    Chord chord = pitchQuantizer.createChord(chordDef, rootNote);
    TEST_ASSERT_EQUAL_INT(chord.size(), 4);
    TEST_ASSERT_EQUAL_INT(expectedNote1.repeat, chord[0].repeat);
    TEST_ASSERT_EQUAL_INT(expectedNote1.note,   chord[0].note);
    TEST_ASSERT_EQUAL_INT(expectedNote2.repeat, chord[1].repeat);
    TEST_ASSERT_EQUAL_INT(expectedNote2.note,   chord[1].note);
    TEST_ASSERT_EQUAL_INT(expectedNote3.repeat, chord[2].repeat);
    TEST_ASSERT_EQUAL_INT(expectedNote3.note,   chord[2].note);
}

void test_createChord() {
    test_createChord(Note(0, 0),  Note(0, 0),  Note(0, 4),  Note(0, 7)); // C Major
    test_createChord(Note(0, 2),  Note(0, 2),  Note(0, 5),  Note(0, 9)); // D Minor
    test_createChord(Note(0, 4),  Note(0, 4),  Note(0, 7),  Note(0, 11));// E Minor
    test_createChord(Note(0, 5),  Note(0, 5),  Note(0, 9),  Note(1, 0)); // F Major
    test_createChord(Note(0, 7),  Note(0, 7),  Note(0, 11), Note(1, 2)); // G Major
    test_createChord(Note(0, 9),  Note(0, 9),  Note(1, 0),  Note(1, 4)); // A Minor
    test_createChord(Note(0, 11), Note(0, 11), Note(1, 2),  Note(1, 5)); // B Diminished
 
    // +1 octave
    test_createChord(Note(1, 0),  Note(1, 0),  Note(1, 4),  Note(1, 7)); // C Major
    test_createChord(Note(1, 2),  Note(1, 2),  Note(1, 5),  Note(1, 9)); // D Minor
    test_createChord(Note(1, 4),  Note(1, 4),  Note(1, 7),  Note(1, 11));// E Minor
    test_createChord(Note(1, 5),  Note(1, 5),  Note(1, 9),  Note(2, 0)); // F Major
    test_createChord(Note(1, 7),  Note(1, 7),  Note(1, 11), Note(2, 2)); // G Major
    test_createChord(Note(1, 9),  Note(1, 9),  Note(2, 0),  Note(2, 4)); // A Minor
    test_createChord(Note(1, 11), Note(1, 11), Note(2, 2),  Note(2, 5)); // B Diminished

    // -1 octave
    test_createChord(Note(-1, 0),  Note(-1, 0),  Note(-1, 4),  Note(-1, 7)); // C Major
    test_createChord(Note(-1, 2),  Note(-1, 2),  Note(-1, 5),  Note(-1, 9)); // D Minor
    test_createChord(Note(-1, 4),  Note(-1, 4),  Note(-1, 7),  Note(-1, 11));// E Minor
    test_createChord(Note(-1, 5),  Note(-1, 5),  Note(-1, 9),  Note(0, 0)); // F Major
    test_createChord(Note(-1, 7),  Note(-1, 7),  Note(-1, 11), Note(0, 2)); // G Major
    test_createChord(Note(-1, 9),  Note(-1, 9),  Note(0, 0),  Note(0, 4)); // A Minor
    test_createChord(Note(-1, 11), Note(-1, 11), Note(0, 2),  Note(0, 5)); // B Diminished
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_quantizeToScale);
    RUN_TEST(test_quantizeToScaleWithOffset);
    RUN_TEST(test_createChord);
    return UNITY_END();
}
