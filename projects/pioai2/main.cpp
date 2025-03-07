#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "pio_blink.pio.h"

// Funzione per inizializzare il programma PIO
void pio_blink_program_init(PIO pio, uint sm, uint offset, uint pin) {
    // Configura il pin come output
    pio_gpio_init(pio, pin);
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);

    // Configura la macchina a stati
    pio_sm_config c = pio_blink_program_get_default_config(offset);
    sm_config_set_set_pins(&c, pin, 1); // Imposta il pin di output
    sm_config_set_clkdiv(&c, 125000000);   // Frequenza di 1 Hz (125 MHz / 31250 = 4000 Hz, poi diviso ulteriormente dal loop PIO)
    pio_sm_init(pio, sm, offset, &c);

    // Avvia la macchina a stati
    pio_sm_set_enabled(pio, sm, true);
}

int main() {
    // Inizializza la libreria standard (per printf)
    stdio_init_all();

    // Seleziona il programma PIO e lo carica nella memoria PIO
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &pio_blink_program);

    // Configura il pin 15 come output per il LED
    uint sm = pio_claim_unused_sm(pio, true);
    pio_blink_program_init(pio, sm, offset, 15);

    // Messaggio di debug
    printf("PIO program loaded and running. LED should blink on pin 15.\n");

    // Loop infinito
    while (true) {
        // Puoi aggiungere ulteriori operazioni di debug qui se necessario
        sleep_ms(1000);  // Attendi 1 secondo
    }
}