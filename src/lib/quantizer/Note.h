#ifndef Note_h
#define Note_h

class Note {
    public:
        Note() {}
        Note(int cycle, int note, float voltage = 0, int offset = 0) 
            { this->cycle = cycle; this->note = note; this->voltage = voltage; this->offset = offset; }
        int cycle = 0;
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