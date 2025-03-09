#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "pio_blink.pio.h"
#include "hardware/clocks.h"

// Funzione per inizializzare il programma PIO
void pio_blink_program_init(PIO pio, uint sm, uint offset, uint pin)
{
    // Configura il pin come output
    pio_gpio_init(pio, pin);
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);

    // Configura la macchina a stati
    pio_sm_config c = pio_blink_program_get_default_config(offset);
    sm_config_set_set_pins(&c, pin, 1); // Imposta il pin di output
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
    uint offset = pio_add_program(pio, &pio_blink_program);

    // Configura il pin 15 come output per il LED
    uint sm = pio_claim_unused_sm(pio, true);
    pio_blink_program_init(pio, sm, offset, 15);

    // Imposta la frequenza desiderata (10 Hz)
    float freq = 10000.0f;                     // Frequenza in Hz
    uint32_t clock_hz = clock_get_hz(clk_sys); // Frequenza di clock del sistema
    uint32_t divider = clock_hz / (freq * 2);  // Divisore per ottenere la frequenza desiderata
    // pio_sm_set_clkdiv_int_frac(pio, sm, divider, 0);
    // sm_config_set_clkdiv(&pio->c, 1250000000.0);
    pio_sm_set_clkdiv(pio, sm, divider);

    // Messaggio di debug
    printf("PIO program loaded and running. LED should blink on pin 15.\n");

    // Loop infinito
    uint32_t delay = 15;

    while (true)
    {
        // Puoi aggiungere ulteriori operazioni di debug qui se necessario
        sleep_ms(100); // Attendi 1 secondo

        if (delay > 1)
        {
            delay = delay - 1;
        }
        else
        {
            delay = 30;
        }
        pio_sm_put(pio, sm, delay);
      }
}