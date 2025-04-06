#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "toyorgan.pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "toyorgan.h"
#include <math.h>

float C3_FREQUENCY_HZ = 130.81;

int main()
{

    PioConfigurationData pioConfigurationData = {
        PioConfigurationItem{
            .pio = pio0,
            .sm = 0,
            .frequency = C3_FREQUENCY_HZ,
            .soundPins = {1, 2, 3},
            .usedSoundPins = 3,
        },
        PioConfigurationItem{
            .pio = pio0,
            .sm = 1,
            .frequency = C3_FREQUENCY_HZ * (pow(2.0, (1.0 / 12.0))),
            .soundPins = {4, 5, 6},
            .usedSoundPins = 3,
        },
        PioConfigurationItem{
            .pio = pio0,
            .sm = 2,
            .frequency = C3_FREQUENCY_HZ * (pow(2.0, (2.0 / 12.0))),
            .soundPins = {7, 8, 9},
            .usedSoundPins = 3,
        },
        PioConfigurationItem{
            .pio = pio0,
            .sm = 3,
            .frequency = C3_FREQUENCY_HZ * (pow(2.0, (3.0 / 12.0))),
            .soundPins = {10, 11, 12},
            .usedSoundPins = 3,
        },
        PioConfigurationItem{
            .pio = pio1,
            .sm = 0,
            .frequency = C3_FREQUENCY_HZ * (pow(2.0, (4.0 / 12.0))),
            .soundPins = {13, 14, 15},
            .usedSoundPins = 3,
        },
        PioConfigurationItem{
            .pio = pio1,
            .sm = 1,
            .frequency = C3_FREQUENCY_HZ * (pow(2.0, (5.0 / 12.0))),
            .soundPins = {16, 17, 18},
            .usedSoundPins = 3,
        },
        PioConfigurationItem{
            .pio = pio1,
            .sm = 2,
            .frequency = C3_FREQUENCY_HZ * (pow(2.0, (6.0 / 12.0))),
            .soundPins = {19, 20, 21},
            .usedSoundPins = 3,
        },
    };

    // ADCConfigurationData adcConfigurationData{.adcPin = 26, .adcInput = 0};

    // Inizializza la libreria standard (per printf)
    stdio_init_all();

    PioEnvironment pioEnvironment = toyorgan_program_init(pioConfigurationData, toyorgan_program);

    // set_pio_base_step_frequency(pioEnvironment, 1000);

    // configure_adc(adcConfigurationData);

    // uint16_t pitch_input = read_adc_average(10, 1);

    // while (true)
    // {
    //     sleep_ms(10);
    //     for (uint k = 0; k < NUMBER_OF_SM; k++)
    //     {

    //         // PioEnvironmentItem pioEnvironmentItem = pioEnvironment.items[k];

    //         //     pio_sm_set_clkdiv(
    //         //         pioEnvironmentItem.pio,
    //         //         pioEnvironmentItem.sm,
    //         //         calculate_divider(pioEnvironmentItem.frequency, clock_get_hz(clk_sys)));
    //     }
    // }
}