#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "toyorgan.pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "toyorgan.h"

int main()
{

    PioConfigurationData pioConfigurationData = {
        PioConfigurationItem{
            .pio = pio0,
            .soundPins = {15, 16, 17},
            .usedSoundPins = 4,
        },
        PioConfigurationItem{
            .pio = pio0,
            .soundPins = {18, 19, 20},
            .usedSoundPins = 4},
    };

    ADCConfigurationData adcConfigurationData{.adcPin = 26, .adcInput = 0};

    // Inizializza la libreria standard (per printf)
    stdio_init_all();

    PioEnvironment pioEnvironment = toyorgan_program_init(pioConfigurationData, toyorgan_program);
    set_pio_base_step_frequency(pioEnvironment, 1000);

    configure_adc(adcConfigurationData);

    uint32_t delay = 1;

    float BASE = 55.0f;
    float freq = 3 * BASE;

    while (true)
    {
        sleep_ms(5);

        uint16_t pitch_input = read_adc_average(10, 1);

        // printf("adc: %d\n", pitch_input);

        freq = (uint16_t)(BASE * (1 + pitch_input / 256));
        // delay = calculate_delay(base_step_frequency, freq);

        set_pio_base_step_frequency(pioEnvironment, freq * 32);

        printf("delay: %d\n", delay);
        for (uint k = 0; k < 2; k++)
        {
            PioEnvironmentItem pioEnvironmentItem = pioEnvironment.items[k];
            pio_sm_put(pioEnvironmentItem.pio, pioEnvironmentItem.sm, delay);
        }
    }
}