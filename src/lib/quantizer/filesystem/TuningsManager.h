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
        static TuningsManager manager;

        TuningsManager(FileSystem& fs, MemPool<>& memPool) : fs(fs), memPool(memPool) {}
        void init();
        void clear();
        int getTuningCount();
        TuningData& loadTuningData(int index);

        Tuning* addTuning(Tuning& tuning);
        Scale* addScale(Scale& scale);

        Tuning* getTuning() { return &tuningsManager.getObjects().get(0); }

    private:
        FileSystem& fs;

        TuningData tuningData;

        // memory management
        MemPool<>& memPool;
        ObjectManager<Tuning> tuningsManager = ObjectManager<Tuning>(memPool);
        ObjectManager<Scale> scalesManager = ObjectManager<Scale>(memPool);

};

#endif