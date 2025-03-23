#include "pico/stdlib.h"
#include "hardware/pio.h"

struct HardwareConfiguration
{
    uint soundPins[5];
    uint usedSoundPins;
    uint adcPin;
};

struct PioConfigurationData
{
    PIO pio;
    uint soundPins[5];
    uint usedSoundPins;
};

struct ADCConfigurationData
{
    uint adcPin;
    uint adcInput;
};

struct PioEnvironment
{
    PIO pio;
    uint sm;
};