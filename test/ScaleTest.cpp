#include <unity.h>
#include <math.h>
#include <initializer_list>
#include "ScaleTest.h"

Tuning ScaleTest::tuning = Tuning(12);
ChordDef ScaleTest::chordDef = ChordDef({0, 2, 4, 6});
Scale ScaleTest::scale = Scale(ScaleTest::tuning, {0, 2, 4, 5, 7, 9, 11}, ScaleTest::chordDef);

void ScaleTest::test_firstLastNote(int offset, int cycle, int expectedFirstNote, int expectedLastNote) {
    scale.setOffset(offset);
    Note firstNote = scale.getFirstNote(cycle);
    Note lastNote = scale.getLastNote(cycle);
    TEST_ASSERT_EQUAL_INT(expectedFirstNote, firstNote.note);
    TEST_ASSERT_EQUAL_INT(expectedLastNote, lastNote.note);
}

void test_firstLastNote() {
    ScaleTest::test_firstLastNote(0, 0, 0, 11); //Ionian
    ScaleTest::test_firstLastNote(1, 0, 0, 10); //Locrian
    ScaleTest::test_firstLastNote(2, 0, 1, 11);  
    ScaleTest::test_firstLastNote(3, 0, 0, 10); //Aeolian
    ScaleTest::test_firstLastNote(4, 0, 1, 11); 
    ScaleTest::test_firstLastNote(5, 0, 0, 10); //Mixolydian
    ScaleTest::test_firstLastNote(6, 0, 1, 11);
    ScaleTest::test_firstLastNote(7, 0, 0, 11); //Lydian
    ScaleTest::test_firstLastNote(8, 0, 0, 10); //Phrygian
    ScaleTest::test_firstLastNote(9, 0, 1, 11); 
    ScaleTest::test_firstLastNote(10, 0, 0, 10); //Dorian
    ScaleTest::test_firstLastNote(11, 0, 1, 11); 
}

void ScaleTest::test_containsNote(int offset, int note, bool expectedContains) {
    scale.setOffset(offset);
    bool contains = scale.containsNote(note);
    TEST_ASSERT_EQUAL_INT(expectedContains, contains);
}

void test_containsNote() {
    ScaleTest::test_containsNote(0, 0, true);
    ScaleTest::test_containsNote(0, 1, false);
    ScaleTest::test_containsNote(0, 2, true);
    ScaleTest::test_containsNote(0, 3, false);
    ScaleTest::test_containsNote(0, 4, true);
    ScaleTest::test_containsNote(0, 5, true);
    ScaleTest::test_containsNote(0, 6, false);
    ScaleTest::test_containsNote(0, 7, true);
    ScaleTest::test_containsNote(0, 8, false);
    ScaleTest::test_containsNote(0, 9, true);
    ScaleTest::test_containsNote(0, 10, false);
    ScaleTest::test_containsNote(0, 11, true);

    ScaleTest::test_containsNote(1, 0, true);
    ScaleTest::test_containsNote(1, 1, true);
    ScaleTest::test_containsNote(1, 2, false);
    ScaleTest::test_containsNote(1, 3, true);
    ScaleTest::test_containsNote(1, 4, false);
    ScaleTest::test_containsNote(1, 5, true);
    ScaleTest::test_containsNote(1, 6, true);
    ScaleTest::test_containsNote(1, 7, false);
    ScaleTest::test_containsNote(1, 8, true);
    ScaleTest::test_containsNote(1, 9, false);
    ScaleTest::test_containsNote(1, 10, true);
    ScaleTest::test_containsNote(1, 11, false);

    ScaleTest::test_containsNote(2, 0, false);
    ScaleTest::test_containsNote(2, 1, true);
    ScaleTest::test_containsNote(2, 2, true);
    ScaleTest::test_containsNote(2, 3, false);
    ScaleTest::test_containsNote(2, 4, true);
    ScaleTest::test_containsNote(2, 5, false);
    ScaleTest::test_containsNote(2, 6, true);
    ScaleTest::test_containsNote(2, 7, true);
    ScaleTest::test_containsNote(2, 8, false);
    ScaleTest::test_containsNote(2, 9, true);
    ScaleTest::test_containsNote(2, 10, false);
    ScaleTest::test_containsNote(2, 11, true);
}

void test_Scale() {
    RUN_TEST(test_firstLastNote);
    RUN_TEST(test_containsNote);
}
