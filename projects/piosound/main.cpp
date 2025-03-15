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
    // pio_gpio_init(pio, pin);
    // pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);

    // uint32_t mask = (1 << 1) | (1 << 3) | (1 << 7) | (1 << 12);    // Pin 1, 3, 7, 12
    // uint32_t pindirs = (1 << 1) | (1 << 3) | (1 << 7) | (1 << 12); // Output

    // Configura i pin come output utilizzando le maschere
    // pio_sm_set_pindirs_with_mask(pio, sm, mask, pindirs;

    // Configura la macchina a stati
    pio_sm_config c = pio_sound_program_get_default_config(offset);

    sm_config_set_set_pins(&c, pins[0], number_of_pins); // Imposta i pin di output

    pio_sm_init(pio, sm, offset, &c);

    // Avvia la macchina a stati
    pio_sm_set_enabled(pio, sm, true);
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
    uint pins[] = {15, 16, 17, 18};
    pio_sound_program_init(pio, sm, offset, pins, 4);

    // Imposta la frequenza desiderata (10 Hz)
    float base_step_freq = 100000.0f;                   // Frequenza in Hz
    uint32_t clock_hz = clock_get_hz(clk_sys);          // Frequenza di clock del sistema
    uint32_t divider = clock_hz / (base_step_freq * 2); // Divisore per ottenere la frequenza desiderata
    // pio_sm_set_clkdiv_int_frac(pio, sm, divider, 0);
    // sm_config_set_clkdiv(&pio->c, 1250000000.0);
    pio_sm_set_clkdiv(pio, sm, divider);

    // Loop infinito
    uint32_t delay = 1;

    float BASE = 55.0f;
    float freq = 0.0f;
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
        delay = (uint32_t)(base_step_freq / freq) / 2.0;

        pio_sm_put(pio, sm, delay);
    }
}