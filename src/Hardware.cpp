#include "Hardware.h"

Hardware Hardware::hw = Hardware();

char Hardware::memPoolBuffer[MEMPOOL_SIZE];

void Hardware::init() {
    NativeDevice::instance.init();

    display.init();
    dac8164Device1.init();
    dac8164Device2.init();
    dac8164Device1.setDeferredOutput(true);
    dac8164Device2.setDeferredOutput(true);
    fs.init();
    tuningsManager.init();

    for(int i = 0; i < CHANNEL_COUNT; i++) {
        cvOutputPins[i]->setPinType(PinType::ANALOG_OUTPUT);
    }
}
