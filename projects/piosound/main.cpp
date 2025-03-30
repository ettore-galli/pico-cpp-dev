#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "pio_sound.pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pio_sound.h"

int main()
{

    // uint pins[] = {15};
    // uint number_of_pins = sizeof(pins) / sizeof(pins[0]);
    float base_step_frequency = 10000000.0f;

    PioConfigurationData pioConfigurationData = {
        PioConfigurationItem{
            .pio = pio0,
            .soundPins = {15, 16},
            .usedSoundPins = 2},
        PioConfigurationItem{
            .pio = pio0,
            .soundPins = {17, 18},
            .usedSoundPins = 2},
    };

    ADCConfigurationData adcConfigurationData{.adcPin = 26, .adcInput = 0};

    // Inizializza la libreria standard (per printf)
    stdio_init_all();

    PioEnvironment pioEnvironment = pio_sound_program_init(pioConfigurationData, pio_sound_program);
    set_pio_base_step_frequency(pioEnvironment, base_step_frequency);

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
        delay = calculate_delay(base_step_frequency, freq);

        printf("delay: %d\n", delay);
        pio_sm_put(pioEnvironment.items[0].pio, pioEnvironment.items[0].sm, delay);
        pio_sm_put(pioEnvironment.items[1].pio, pioEnvironment.items[1].sm, delay);
    }
}