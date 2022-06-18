#include "Tuning12EDO.h"


StaticTuningData Tuning12EDO::data = StaticTuningData(tuning, scales.ptr());

Tuning Tuning12EDO::tuning = Tuning({
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

ChordDef Tuning12EDO::chord_heptatonic_tertian = ChordDef({0, 2, 4});
ChordDef Tuning12EDO::chord_heptatonic_quartal = ChordDef({0, 3, 7});
ChordDef Tuning12EDO::chord_heptatonic_quintal = ChordDef({0, 4, 8});
ChordDef Tuning12EDO::chord_chromatic_major = ChordDef({0, 4, 7});
ChordDef Tuning12EDO::chord_chromatic_minor = ChordDef({0, 3, 7});
ChordDef Tuning12EDO::chord_chromatic_diminished = ChordDef({0, 3, 6});
ChordDef Tuning12EDO::chord_chromatic_augmented = ChordDef({0, 4, 8});

Array<Scale, 5> Tuning12EDO::scales = Array<Scale, 5>({
    Scale(tuning, {0, 2, 4, 5, 7, 9, 11}, 
        {chord_heptatonic_tertian, chord_heptatonic_quartal, chord_heptatonic_quintal}, "Major"),
    Scale(tuning, {0, 2, 4, 6, 7, 9, 10}, 
        {chord_heptatonic_tertian, chord_heptatonic_quartal, chord_heptatonic_quintal}, "Melodic Minor"),
    Scale(tuning, {0, 2, 3, 5, 7, 8, 11}, 
        {chord_heptatonic_tertian, chord_heptatonic_quartal, chord_heptatonic_quintal}, "Harmonic Minor"),
    Scale(tuning, {0, 1, 4, 5, 7, 8, 11}, 
        {chord_heptatonic_tertian, chord_heptatonic_quartal, chord_heptatonic_quintal}, "Double Harmonic"),
    Scale(tuning, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, 
        {chord_chromatic_major, chord_chromatic_minor, chord_chromatic_diminished, chord_chromatic_augmented}, "Chromatic")
});

