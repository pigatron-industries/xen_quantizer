#include "Hardware.h"

Hardware Hardware::hw = Hardware();

float Hardware::memPoolBuffer[MEMPOOL_SIZE];

void Hardware::init() {
    NativeDevice::instance.init();

    dac8164.init();
    dac8164.setDeferredOutput(true);

    for(int i = 0; i < CHANNEL_COUNT; i++) {
        cvOutputPins[i]->setPinType(PinType::ANALOG_OUTPUT);
    }
}
