#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "pio_sound.pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"

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

struct PioEnvironment
{
    PIO pio;
    uint sm;
};

PioEnvironment pio_sound_program_init(const PioConfigurationData &config)
{

    uint offset = pio_add_program(config.pio, &pio_sound_program);
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

uint32_t calculate_delay(float base_step_freq, float freq)
{
    return (uint32_t)(base_step_freq / freq) / 2.0;
}

uint32_t calculate_divider(float base_step_freq, uint32_t clock_hz)
{
    return clock_hz / (base_step_freq * 2);
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

uint get_pio_state_machine()
{
    return 0;
}

int main()
{

    uint pins[] = {15};
    uint number_of_pins = sizeof(pins) / sizeof(pins[0]);

    // Inizializza la libreria standard (per printf)
    stdio_init_all();

    PioConfigurationData pioConfigurationData{
        .pio = pio0,
        .soundPins = {15},
        .usedSoundPins = 1};

    PioEnvironment pioEnvironment = pio_sound_program_init(pioConfigurationData);

    float base_step_freq = 100000.0f;

    uint32_t divider = calculate_divider(base_step_freq, clock_get_hz(clk_sys));
    pio_sm_set_clkdiv(pioEnvironment.pio, pioEnvironment.sm, divider);

    uint32_t delay = 1;

    float BASE = 55.0f;
    float freq = 3 * BASE;

    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);

    while (true)
    {
        sleep_ms(5);

        uint16_t pitch_input = read_adc_average(10, 1);

        printf("adc: %d\n", pitch_input);

        freq = (uint16_t)(BASE + 1000.0 * (pitch_input / 4096.0));

        delay = calculate_delay(base_step_freq, freq);
        pio_sm_put(pioEnvironment.pio, pioEnvironment.sm, delay);
    }
}