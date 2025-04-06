#include "pico/stdlib.h"
#include "hardware/pio.h"

const uint NUMBER_OF_SM = 7;

struct HardwareConfiguration
{
    uint soundPins[5];
    uint usedSoundPins;
    uint adcPin;
};

struct PioConfigurationItem
{
    PIO pio;
    uint sm;
    double frequency;
    uint soundPins[5];
    uint usedSoundPins = 0;
};

typedef PioConfigurationItem PioConfigurationData[NUMBER_OF_SM];

struct PioEnvironmentItem
{
    PIO pio;
    uint sm = -1;
    double frequency;
};

struct PioEnvironment
{
    PioEnvironmentItem items[NUMBER_OF_SM];
};

struct ADCConfigurationData
{
    uint adcPin;
    uint adcInput;
};