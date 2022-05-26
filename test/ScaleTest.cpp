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
    ScaleTest::test_firstLastNote(0, 0, 0, 11);
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
}

void ScaleTest::test_getNoteByIndex(int index, int expectedNote) {
    int note = scale.getNote(index);
    TEST_ASSERT_EQUAL_INT(expectedNote, note);
}

void test_getNoteByIndex() {
    ScaleTest::scale.setOffset(0);
    ScaleTest::test_getNoteByIndex(0, 0);
    ScaleTest::test_getNoteByIndex(1, 2);
    ScaleTest::test_getNoteByIndex(2, 4);
    ScaleTest::test_getNoteByIndex(3, 5);
    ScaleTest::test_getNoteByIndex(4, 7);
    ScaleTest::test_getNoteByIndex(5, 9);
    ScaleTest::test_getNoteByIndex(6, 11);
}

void test_Scale() {
    RUN_TEST(test_firstLastNote);
    RUN_TEST(test_containsNote);
    RUN_TEST(test_getNoteByIndex);
}
