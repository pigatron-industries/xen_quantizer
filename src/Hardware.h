#ifndef Hardware_h
#define Hardware_h

#include <Arduino.h>
#include <eurorack.h>
#include <eurorack_sd.h>
#include <eurorack_dac8164.h>
#include <eurorack_mcp23s17.h>
#include <USBHost_t36.h>

#include "hwconfig.h"
#include "interface/TFTDisplay.h"
#include "lib/quantizer/filesystem/TuningsManager.h"
#include "lib/neural/filesystem/TensorFlowModelManager.h"

#define MEMPOOL_TUNING_SIZE 48*1024
#define MEMPOOL_MODEL_SIZE 1024*1024
#define TENSOR_ARENA_SIZE 1024*1024

class Hardware {
    public:
        static Hardware hw;
        void init();

        // SD Card
        FileSystem fsTunings = FileSystem(SD_CS_PIN, "/tunings");
        FileSystem fsModels = FileSystem(SD_CS_PIN, "/models");

        // USB host
        USBHost usb;
        USBHub hub = USBHub(usb);
        MIDIDevice midiDevice = MIDIDevice(usb);

        // Memory pool
        static uint8_t memPoolTuningBuffer[MEMPOOL_TUNING_SIZE];
        MemPool<> memPoolTuning = MemPool<>(Hardware::memPoolTuningBuffer, MEMPOOL_TUNING_SIZE);

        static uint8_t memPoolModelBuffer[MEMPOOL_MODEL_SIZE];
        MemPool<> memPoolModel = MemPool<>(Hardware::memPoolModelBuffer, MEMPOOL_MODEL_SIZE);
        static uint8_t tensorArena[TENSOR_ARENA_SIZE];

        // Object management
        TuningsManager tuningsManager = TuningsManager(fsTunings, memPoolTuning);
        TensorflowModelManager modelManager = TensorflowModelManager(fsModels, memPoolModel);

        // Direct connections
        RotaryEncoderButton encoder1 = RotaryEncoderButton(ENCODER1_PIN1, ENCODER1_PIN2, ENCODER1_BTN_PIN);
        RotaryEncoderButton encoder2 = RotaryEncoderButton(ENCODER2_PIN1, ENCODER2_PIN2, ENCODER2_BTN_PIN);

        #define AnalogInputPinT AnalogInputPin<NativeDevice>
        #define AnalogInputSumPinT AnalogInputSumPin<NativeDevice>
        #define AnalogOutputDeviceT DAC8164Device
        #define DigitalOutputDeviceT NativeDevice

        AnalogInput(channel1PotPin, A7)
        AnalogInput(channel2PotPin, A2)
        AnalogInput(channel3PotPin, A3)
        AnalogInput(channel4PotPin, A6)

        AnalogInput(channel1CvPin, A11)  //CV5
        AnalogInput(channel2CvPin, A10)  //CV6
        AnalogInput(channel3CvPin, A1)   //CV7
        AnalogInput(channel4CvPin, A0)   //CV8

        AnalogInput(channel1InputPin, A16) //CV1
        AnalogInput(channel2InputPin, A17) //CV2
        AnalogInput(channel3InputPin, A12) //CV3
        AnalogInput(channel4InputPin, A13) //CV4

        DigitalInput(trigger1InputPin, 36)
        DigitalInput(trigger2InputPin, 35)
        DigitalInput(trigger3InputPin, 34)
        DigitalInput(trigger4InputPin, 33)
        DigitalInputPin<>* triggerInputPins[CHANNEL_COUNT] = {
            &trigger1InputPin,
            &trigger2InputPin,
            &trigger3InputPin,
            &trigger4InputPin
        }; 

        DigitalInput(button1InputPin, 28)
        DigitalInput(button2InputPin, 38)
        DigitalInput(button3InputPin, 39)
        DigitalInput(button4InputPin, 29)
        PushButton<> pushButtons[CHANNEL_COUNT] = {
            PushButton<>(button1InputPin),
            PushButton<>(button2InputPin),
            PushButton<>(button3InputPin),
            PushButton<>(button4InputPin),
        }; 

        DigitalOutput(led1OutputPin, 30)
        DigitalOutput(led2OutputPin, 31)
        DigitalOutput(led3OutputPin, 32)
        DigitalOutput(led4OutputPin, 37)

        DAC8164Device dac8164Device1 = DAC8164Device(-1, DAC1_CS_PIN);
        DAC8164Device dac8164Device2 = DAC8164Device(-1, DAC2_CS_PIN);
        AnalogOutputPin<DAC8164Device>* cvOutputPins[8] = {
            &dac8164Device2.pins[1],
            &dac8164Device2.pins[2],
            &dac8164Device2.pins[3],
            &dac8164Device2.pins[0],
            &dac8164Device1.pins[3],
            &dac8164Device1.pins[0],
            &dac8164Device1.pins[1],
            &dac8164Device1.pins[2],
        };

        TFTDisplay display;

};

#endif