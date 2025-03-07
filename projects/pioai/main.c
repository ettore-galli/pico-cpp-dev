#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pio_pwm.pio.h"
#include <stdio.h>

#define PWM_PIN 15  // Pin GPIO per il LED
#define PROBE_PIN 16  // Pin GPIO per la verifica (debug)

// Funzione di inizializzazione per il programma PIO
void pio_pwm_program_init(PIO pio, uint sm, uint offset, uint pin) {
    // Configura il pin per il PIO
    pio_gpio_init(pio, pin);

    // Configura la macchina a stati (SM)
    pio_sm_config c = pio_pwm_program_get_default_config(offset);
    sm_config_set_sideset_pins(&c, pin);  // Imposta il pin per il side-set
    sm_config_set_set_pins(&c, pin, 1);   // Imposta il pin per il set
    sm_config_set_sideset(&c, 2, true, false);  // Configura il side-set
    pio_sm_init(pio, sm, offset, &c);     // Inizializza la SM
}

int main() {
    // Inizializza stdio per UART (debug)
    stdio_init_all();

    // Inizializza il pin di prova come input (debug)
    gpio_init(PROBE_PIN);
    gpio_set_dir(PROBE_PIN, GPIO_IN);

    // Inizializza il PIO
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &pio_pwm_program);
    if (offset == -1) {
        printf("Errore: impossibile caricare il programma PIO!\n");
        return -1;
    }

    uint sm = pio_claim_unused_sm(pio, true);
    if (sm == -1) {
        printf("Errore: nessuna SM disponibile!\n");
        return -1;
    }

    pio_pwm_program_init(pio, sm, offset, PWM_PIN);

    // Imposta la frequenza desiderata (10 Hz)
    float freq = 10.0f;  // Frequenza in Hz
    uint32_t clock_hz = clock_get_hz(clk_sys);  // Frequenza di clock del sistema
    uint32_t divider = clock_hz / (freq * 2);   // Divisore per ottenere la frequenza desiderata
    pio_sm_set_clkdiv_int_frac(pio, sm, divider, 0);

    // Avvia la macchina a stati
    pio_sm_set_enabled(pio, sm, true);

    // Debug
    printf("PIO stato: %d\n", pio_sm_is_claimed(pio, sm));
    printf("SM PC: %u\n", pio_sm_get_pc(pio, sm));
    printf("Frequenza desiderata: %.2f Hz\n", freq);
    printf("Divisore di clock: %lu\n", divider);

    // Loop infinito
    while (true) {
        // Debug: verifica lo stato del pin controllato dal PIO usando il pin di prova
        printf("Stato del pin %d (letto da %d): %d\n", PWM_PIN, PROBE_PIN, gpio_get(PROBE_PIN));
        sleep_ms(100);  // Attendi 100 ms per osservare il cambiamento
    }
}