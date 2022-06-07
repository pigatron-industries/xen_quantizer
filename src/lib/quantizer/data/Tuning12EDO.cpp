#include "Tuning12EDO.h"


TuningData Tuning12EDO::data = TuningData(tuning, ArrayPtr<Scale>(&scales[0], 4));

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

ChordDef Tuning12EDO::chord_triad = ChordDef({0, 2, 4});

Array<Scale, 5> Tuning12EDO::scales = Array<Scale, 5>({
    Scale(tuning, {0, 2, 4, 5, 7, 9, 11}, {chord_triad}, "Major"),
    Scale(tuning, {0, 2, 4, 6, 7, 9, 10}, {chord_triad}, "Melodic Minor"),
    Scale(tuning, {0, 2, 3, 5, 7, 8, 11}, {chord_triad}, "Harmonic Minor"),
    Scale(tuning, {0, 1, 4, 5, 7, 8, 11}, {chord_triad}, "Double Harmonic"),
    Scale(tuning, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, "Chromatic")
});

