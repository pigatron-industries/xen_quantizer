#include "Tuning12EDO.h"


TuningData Tuning12EDO::data = TuningData(tuning, ArrayPtr<Scale>(&scales[0], 4), ArrayPtr<ChordDef>(&chordDefs[0], 4));

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

Array<Scale, 4> Tuning12EDO::scales = Array<Scale, 4>({
    Scale(tuning, {0, 2, 4, 5, 7, 9, 11}, "Major"),
    Scale(tuning, {0, 2, 4, 6, 7, 9, 10}, "Melodic Minor"),
    Scale(tuning, {0, 2, 3, 5, 7, 8, 11}, "Harmonic Minor"),
    Scale(tuning, {0, 1, 4, 5, 7, 8, 11}, "Double Harmonic")
});

Array<ChordDef, 1> Tuning12EDO::chordDefs = Array<ChordDef, 1>({
    ChordDef({0, 2, 4}),   //Triad
    ChordDef({0, 2, 4, 6}) //Seventh
});
