#ifndef toyorgan_H
#define toyorgan_H

#include "toyorgan_base.h"

uint32_t calculate_delay(float base_step_freq, float freq);

uint32_t calculate_divider(float base_step_freq, uint32_t clock_hz);

PioEnvironment toyorgan_program_init(const PioConfigurationData &configData, const pio_program &pio_pgm);

void set_pio_base_step_frequency(PioEnvironment pioEnvironment, float base_step_frequency);

uint16_t read_adc_average(uint8_t samples, uint8_t intra_sample_delay_ms);

void configure_adc(const ADCConfigurationData &config);

#endif