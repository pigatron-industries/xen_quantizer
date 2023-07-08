#include "Hardware.h"

Hardware Hardware::hw = Hardware();

uint8_t Hardware::memPoolTuningBuffer[MEMPOOL_TUNING_SIZE];
EXTMEM uint8_t Hardware::memPoolModelBuffer[MEMPOOL_MODEL_SIZE];
EXTMEM uint8_t Hardware::tensorArena[TENSOR_ARENA_SIZE];

void Hardware::init() {
    NativeDevice::instance.init();

    display.init();
    dac8164Device1.init();
    dac8164Device2.init();
    dac8164Device1.setDeferredOutput(true);
    dac8164Device2.setDeferredOutput(true);
    fsTunings.init();
    fsModels.init();
    tuningsManager.init();

    for(int i = 0; i < CHANNEL_COUNT; i++) {
        cvOutputPins[i]->setPinType(PinType::ANALOG_OUTPUT);
        cvOutputPins[i]->loadCalibration();
    }
}
