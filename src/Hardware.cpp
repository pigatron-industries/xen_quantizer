#include "Hardware.h"

Hardware Hardware::hw = Hardware();

char Hardware::memPoolBuffer[MEMPOOL_SIZE];

void Hardware::init() {
    NativeDevice::instance.init();

    dac8164Device.init();
    dac8164Device.setDeferredOutput(true);
    mcp23s17Device.init();

    for(int i = 0; i < CHANNEL_COUNT; i++) {
        cvOutputPins[i]->setPinType(PinType::ANALOG_OUTPUT);
    }
}
