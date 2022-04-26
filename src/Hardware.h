#ifndef Hardware_h
#define Hardware_h

#include <Arduino.h>
#include <eurorack.h>
#include <eurorack_dac8164.h>
#include "hwconfig.h"

#define MEMPOOL_SIZE 48*1024

class Hardware {
    public:
        static Hardware hw;
        void init();

        // Memory pool
        static float memPoolBuffer[MEMPOOL_SIZE];
        MemPool<float> memPool = MemPool<float>(Hardware::memPoolBuffer, MEMPOOL_SIZE);

        // Direct connections
        RotaryEncoderButton encoder = RotaryEncoderButton(ENCODER_PIN1, ENCODER_PIN2, ENCODER_BTN_PIN);

        #define AnalogInputPinT AnalogInputPin<NativeDevice>
        #define AnalogInputSumPinT AnalogInputSumPin<NativeDevice>
        #define AnalogOutputDeviceT DAC8164Device
        #define DigitalOutputDeviceT NativeDevice

        AnalogInput(channel1PotPin, A10)
        AnalogInput(channel2PotPin, A11)
        AnalogInput(channel3PotPin, A13)
        AnalogInput(channel4PotPin, A12)

        AnalogInput(channel1InputPin, A9)
        AnalogInput(channel2InputPin, A8)
        AnalogInput(channel3InputPin, A7)
        AnalogInput(channel4InputPin, A6)

        AnalogInput(channel1CvPin, A3)
        AnalogInput(channel2CvPin, A2)
        AnalogInput(channel3CvPin, A1)
        AnalogInput(channel4CvPin, A0)

        DAC8164Device dac8164 = DAC8164Device(-1, DAC_SYNC_PIN);
        AnalogOutputPin<DAC8164Device>* cvOutputPins[CHANNEL_COUNT] = {
            &dac8164.pins[0],
            &dac8164.pins[1],
            &dac8164.pins[2],
            &dac8164.pins[3],
        };

};

#endif