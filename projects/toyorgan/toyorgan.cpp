#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "toyorgan.pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "toyorgan.h"

uint32_t calculate_delay(float base_step_freq, float freq)
{
    return (uint32_t)(base_step_freq / freq) / 2.0;
}

uint32_t calculate_divider(float base_step_freq, uint32_t clock_hz)
{
    return clock_hz / (base_step_freq * 2);
}

PioEnvironment toyorgan_program_init(const PioConfigurationData &configData, const pio_program &pio_pgm)
{

    PioEnvironment pioEnvironment;

    uint offset_pio0 = pio_add_program(pio0, &pio_pgm);
    uint offset_pio1 = pio_add_program(pio1, &pio_pgm);

    for (uint i = 0; i < NUMBER_OF_SM; i++)
    {

        if (configData[i].usedSoundPins == 0)
        {
            continue;
        }

        uint offset = configData[i].pio == pio0 ? offset_pio0 : offset_pio1;

        // uint sm = pio_claim_unused_sm(configData[i].pio, true);

        uint32_t mask = 0;
        uint32_t pindirs = 0;

        for (uint j = 0; j < configData[i].usedSoundPins; j++)
        {
            pio_gpio_init(configData[i].pio, configData[i].soundPins[j]);
            mask = mask | (1u << configData[i].soundPins[j]);
        }

        pio_sm_set_pindirs_with_mask(configData[i].pio, configData[i].sm, mask, mask);

        pio_sm_config c = toyorgan_program_get_default_config(offset);

        sm_config_set_set_pins(&c, configData[i].soundPins[0], configData[i].usedSoundPins);
        sm_config_set_clkdiv(
            &c,
            calculate_divider(configData[i].frequency * 32, clock_get_hz(clk_sys)));

        pio_sm_set_enabled(configData[i].pio, configData[i].sm, false);
        pio_sm_init(configData[i].pio, configData[i].sm, offset, &c);
        pio_sm_set_enabled(configData[i].pio, configData[i].sm, true);

        pioEnvironment.items[i] = PioEnvironmentItem{
            .pio = configData[i].pio,
            .sm = configData[i].sm,
            .frequency = configData[i].frequency,
        };
    }

    return pioEnvironment;
}

// void set_pio_base_step_frequency(PioEnvironment pioEnvironment, float base_step_frequency)
// {
//     for (uint i = 0; i < NUMBER_OF_SM; i++)
//     {
//         if (pioEnvironment.items[i].sm == -1)
//         {
//             continue;
//         }
//         uint32_t divider = calculate_divider(base_step_frequency, clock_get_hz(clk_sys));
//         pio_sm_set_clkdiv(pioEnvironment.items[i].pio, pioEnvironment.items[i].sm, divider);
//     }
// }

// uint16_t read_adc_average(uint8_t samples, uint8_t intra_sample_delay_ms)
// {
//     uint32_t sum = 0;
//     for (uint8_t i = 0; i < samples; i++)
//     {
//         sleep_ms(intra_sample_delay_ms);
//         sum += adc_read();
//     }
//     return sum / samples;
// }

// void configure_adc(const ADCConfigurationData &config)
// {
//     adc_init();
//     adc_gpio_init(configData[i].adcPin);
//     adc_select_input(configData[i].adcInput);
// }