#ifndef TickCounter_h
#define TickCounter_h

#include <inttypes.h>

class TickCounter {
    public:
        TickCounter() {}
        TickCounter(int8_t ticksPerSequence) : ticksPerSequence(ticksPerSequence) {}

        int8_t tick() { 
            tickCount++; 
            if (tickCount >= ticksPerSequence) {
                tickCount = 0;
            }
            return tickCount;
        }

        void reset() { tickCount = -1; } 

        int8_t getTickCount() { return tickCount; }
        int8_t getTicksPerSequence() { return ticksPerSequence; }
        void setTicksPerSequence(int8_t ticksPerSequence) { this->ticksPerSequence = ticksPerSequence; }

    private:
        uint8_t tickCount = -1;
        uint8_t ticksPerSequence;
};

#endif