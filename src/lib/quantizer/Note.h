#ifndef Note_h
#define Note_h

class Note {
    public:
        Note() {}
        Note(int repeat, int note, float voltage = 0, int offset = 0) 
            { this->repeat = repeat; this->note = note; this->voltage = voltage; this->offset = offset; }
        int repeat = 0;
        int note = 0;
        int offset = 0;
        float voltage = 0;
};

class Interval {
    public:
        Interval() {}
        Interval(float voltage) { this->voltage = voltage; }
        float voltage = 0;
};

#endif