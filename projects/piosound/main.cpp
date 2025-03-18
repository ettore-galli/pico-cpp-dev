#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "pio_sound.pio.h"
#include "hardware/clocks.h"

// Funzione per inizializzare il programma PIO
void pio_sound_program_init(PIO pio, uint sm, uint offset, uint pins[], uint number_of_pins)
{

    uint32_t mask = 0;
    uint32_t pindirs = 0;

    for (uint i = 0; i < number_of_pins; i++)
    {
        pio_gpio_init(pio, pins[i]);
        mask = mask | (1u << pins[i]);
    }

    pio_sm_set_pindirs_with_mask(pio, sm, mask, mask);

    pio_sm_config c = pio_sound_program_get_default_config(offset);

    sm_config_set_set_pins(&c, pins[0], number_of_pins); // Imposta i pin di output

    pio_sm_init(pio, sm, offset, &c);

    pio_sm_set_enabled(pio, sm, true);
}

uint32_t calculate_delay(float base_step_freq, float freq)
{
    return (uint32_t)(base_step_freq / freq) / 2.0;
}

uint32_t calculate_divider(float base_step_freq, uint32_t clock_hz)
{
    return clock_hz / (base_step_freq * 2);
}

int main()
{
    // Inizializza la libreria standard (per printf)
    stdio_init_all();

    // Seleziona il programma PIO e lo carica nella memoria PIO
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &pio_sound_program);

    // Configura il pin 15 come output per il LED
    uint sm = pio_claim_unused_sm(pio, true);
    uint pins[] = {15, 16, 17};

    pio_sound_program_init(pio, sm, offset, pins, 3);

    float base_step_freq = 100000.0f;

    uint32_t divider =calculate_divider(base_step_freq, clock_get_hz(clk_sys));
    pio_sm_set_clkdiv(pio, sm, divider);

    // Loop infinito
    uint32_t delay = 1;

    float BASE = 55.0f;
    float freq = 3 * BASE;
    uint8_t harmonic = 1;
    const uint8_t NUM_OF_HARMONICS = 15;

    while (true)
    {
        sleep_ms(500);
        
        harmonic++;
        if (harmonic > NUM_OF_HARMONICS)
        {
            harmonic = 1;
        }
        freq = BASE * harmonic;

        delay = calculate_delay(base_step_freq, freq);
        pio_sm_put(pio, sm, delay);
    }
}