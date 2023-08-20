#ifndef Note_h
#define Note_h

/**
 * Note
 * Represents a specific note played at a specific frequency.
 * cycle is the 'octave' number of the note.
 * note is the number of tuning intervals above the cycle number.
 * offset is the voltage offset of the whole tuning.
 * voltage is the actual calculated voltage or pitch of the note.
 */
class Note {
    public:
        Note() {}
        Note(int cycle, int note, float voltage = 0, float offset = 0) 
            { this->cycle = cycle; this->note = note; this->voltage = voltage; this->offset = offset; }
        int cycle = 0;
        int note = 0;
        float offset = 0;
        float voltage = 0;
};

/**
 * Interval
 * Represents an interval in a tuning.
 * voltage is the difference between two notes in a tuning.
 * dissonance is a rating of how dissonant the interval is compared to other intervals.
 */
class Interval {
    public:
        Interval() {}
        Interval(float voltage) { this->voltage = voltage; }
        Interval(float voltage, int dissonance) { this->voltage = voltage; this->dissonance = dissonance; }
        float voltage = 0;
        int dissonance = 0;
};

#endif