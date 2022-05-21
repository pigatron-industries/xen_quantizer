#ifndef Hardware_h
#define Hardware_h

#include <Arduino.h>
#include <eurorack.h>
#include <eurorack_dac8164.h>
#include <eurorack_mcp23s17.h>
#include "hwconfig.h"

#define MEMPOOL_SIZE 48*1024

class Hardware {
    public:
        static Hardware hw;
        void init();

        // Memory pool
        static char memPoolBuffer[MEMPOOL_SIZE];
        MemPool<char> memPool = MemPool<char>(Hardware::memPoolBuffer, MEMPOOL_SIZE);

        // Direct connections
        RotaryEncoderButton encoder = RotaryEncoderButton(ENCODER_PIN1, ENCODER_PIN2, ENCODER_BTN_PIN);

        #define AnalogInputPinT AnalogInputPin<NativeDevice>
        #define AnalogInputSumPinT AnalogInputSumPin<NativeDevice>
        #define AnalogOutputDeviceT DAC8164Device
        #define DigitalOutputDeviceT NativeDevice

        AnalogInput(channel1PotPin, A13)
        AnalogInput(channel2PotPin, A12)
        AnalogInput(channel3PotPin, A11)
        AnalogInput(channel4PotPin, A10)

        AnalogInput(channel1InputPin, A7)
        AnalogInput(channel2InputPin, A6)
        AnalogInput(channel3InputPin, A8)
        AnalogInput(channel4InputPin, A9)

        AnalogInput(channel1CvPin, A1)
        AnalogInput(channel2CvPin, A0)
        AnalogInput(channel3CvPin, A2)
        AnalogInput(channel4CvPin, A3)

        DAC8164Device dac8164Device = DAC8164Device(-1, DAC_SYNC_PIN);
        AnalogOutputPin<DAC8164Device>* cvOutputPins[CHANNEL_COUNT] = {
            &dac8164Device.pins[1],
            &dac8164Device.pins[2],
            &dac8164Device.pins[3],
            &dac8164Device.pins[0],
        };

        MCP23S17Device mcp23s17Device = MCP23S17Device(GPIO_CS_PIN, GPIO_ADDRESS);
        DigitalInputPin<MCP23S17Device>* clockInputPins[CHANNEL_COUNT] = {
            &mcp23s17Device.pins[7],
            &mcp23s17Device.pins[6],
            &mcp23s17Device.pins[5],
            &mcp23s17Device.pins[4]
        }; 

};

#endif