#ifndef TuningDataFileReader_h
#define TuningDataFileReader_h

#include <eurorack_sd.h>
#include "TuningsManager.h"
#include "../ScaleFactory.h"

#define MAX_GROUP_SCALES 20

class YamlLine {
    public:
        size_t linePosition;
        size_t lineLength;
        int level;
        bool endOfFile = false;
};

class Substring {
    public:
        char* start;
        char* end;
};

class TuningDataFileReader : public BufferFileReader {
    public:
        TuningDataFileReader(TuningsManager& tuningsManager) : BufferFileReader(), tuningsManager(tuningsManager) {}
        bool read(FsFile& file);

    private:
        TuningsManager& tuningsManager;
        Tuning* tuning;
        Array<Scale*, MAX_GROUP_SCALES> groupScales;

        void readTuning(FsFile& file);
        void readGroups(FsFile& file);
        void readGroup(FsFile& file);
        void readScales(FsFile& file);
        void readChords(FsFile& file);
        void readScale(FsFile& file);
        void readChord(FsFile& file);

        float arrayItemRatioToVoltage(int index);

    protected:
        YamlLine line;

        void readLine(FsFile& file);
        int getLevel();
        char* getValue();
        bool isObject(const char* name, int level);
        void back(FsFile& file);

        int arraySize();
        Substring arrayItem(int index);
        int arrayItemInt(int index);
        float arrayItemFloat(int index);
};

#endif