#ifndef ScaleFactory_h
#define ScaleFactory_h

#include "model/Scale.h"

/**
 * Scale Factory
 * Useful function for creating scale sand chords
 */
class ScaleFactory {
    public:
        ScaleFactory() {}

        /**
         * Create an equally divided tuning with the given number of notes and cycle interval.
         * @param divisions The number of divisions or notes in the tuning.
         * @param cycle The voltage difference between two cycles or 'octave', standard octave is 1.
         */
        static Tuning createEqualDivisionTuning(int divisions, float cycle = 1.0, const char* name = "");

        /**
         * Creates a scale by taking the given tuning and selecting the least dissonant intervals.
         * @param tuning The tuning to use.
         * @param dissonance The amount of dissonance to allow, based on the dissonance ratings in the tuning.
         */
        static Scale createHarmonicScale(Tuning& tuning, int dissonance);

        /**
         * Creates a scale by taking the given scale and selecting the least dissonant intervals.
         * @param scale The scale to use.
         * @param dissonance The amount of dissonance to allow, based on the dissonance ratings in the tuning.
         */
        static Scale createHarmonicScale(Scale& scale, int dissonance);

        /**
         * Creates a chord which is on the given scale, using chord definition, root note, inversion and drop.
         * @param scale The scale to use.
         * @param chordDef The chord definition to use.
         * @param rootNote The root note of the chord.
         * @param inversion The number of notes to move up one cycle or 'octave'
         * @param drop The number of notes to drop down one cycle or 'octave'
         */
        static Chord createChord(Scale& scale, ChordDef& chordDef, Note& rootNote, int inversion = 0, int drop = 0);
};


#endif