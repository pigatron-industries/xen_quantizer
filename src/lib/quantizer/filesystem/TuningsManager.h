#ifndef TuningsRepository_h
#define TuningsRepository_h

#include <eurorack.h>
#include <eurorack_sd.h>
#include "../model/Note.h"
#include "../model/Scale.h"
#include "TuningData.h"

#define MAX_SCALES 10
#define MAX_CHORDS 10

class TuningsManager {
    public:
        TuningsManager(FileSystem& fs, MemPool<>& memPool) : fs(fs), memPool(memPool) {}
        void init();
        void clear();
        int getTuningCount();
        FileInfo& getFileInfo(int index);
        TuningData& loadTuningData(int index);

        Tuning* addTuning(Tuning& tuning);
        Scale* addScale(Scale& scale);

        Tuning* getTuning() { return &tuningsManager.get(0); }

    private:
        FileSystem& fs;

        // currently loaded tuning data
        TuningData tuningData;

        // memory management
        MemPool<>& memPool;
        LinkedList<Tuning> tuningsManager = LinkedList<Tuning>();
        LinkedList<Scale> scalesManager = LinkedList<Scale>();

};

#endif