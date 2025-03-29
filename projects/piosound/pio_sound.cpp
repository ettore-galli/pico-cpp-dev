#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "pio_sound.pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pio_sound.h"

uint32_t calculate_delay(float base_step_freq, float freq)
{
    return (uint32_t)(base_step_freq / freq) / 2.0;
}

uint32_t calculate_divider(float base_step_freq, uint32_t clock_hz)
{
    return clock_hz / (base_step_freq * 2);
}

PioEnvironment pio_sound_program_init(const PioConfigurationData &config, const pio_program &pio_pgm)
{

    uint offset = pio_add_program(config.pio, &pio_pgm);
    uint sm = pio_claim_unused_sm(config.pio, true);

    uint32_t mask = 0;
    uint32_t pindirs = 0;

    for (uint i = 0; i < config.usedSoundPins; i++)
    {
        pio_gpio_init(config.pio, config.soundPins[i]);
        mask = mask | (1u << config.soundPins[i]);
    }

    pio_sm_set_pindirs_with_mask(config.pio, sm, mask, mask);

    pio_sm_config c = pio_sound_program_get_default_config(offset);

    sm_config_set_set_pins(&c, config.soundPins[0], config.usedSoundPins);

    pio_sm_init(config.pio, sm, offset, &c);

    pio_sm_set_enabled(config.pio, sm, true);

    return PioEnvironment{.pio = config.pio, .sm = sm};
}

void set_pio_base_step_frequency(PioEnvironment pioEnvironment, float base_step_frequency)
{
    uint32_t divider = calculate_divider(base_step_frequency, clock_get_hz(clk_sys));
    pio_sm_set_clkdiv(pioEnvironment.pio, pioEnvironment.sm, divider);
}

uint16_t read_adc_average(uint8_t samples, uint8_t intra_sample_delay_ms)
{
    uint32_t sum = 0;
    for (uint8_t i = 0; i < samples; i++)
    {
        sleep_ms(intra_sample_delay_ms);
        sum += adc_read();
    }
    return sum / samples;
}

void configure_adc(const ADCConfigurationData &config)
{
    adc_init();
    adc_gpio_init(config.adcPin);
    adc_select_input(config.adcInput);
}