#pragma once

#include <stdint.h>
#include <stdbool.h>

// Out
extern const uint32_t PDND_SPI_CS;
// In
extern const uint32_t PDND_SPI_MISO;
// Out
extern const uint32_t PDND_SPI_WP;
extern const uint32_t PDND_SPI_HOLD;
extern const uint32_t PDND_SPI_CLK;
extern const uint32_t PDND_SPI_MOSI;

// Glitch
extern const uint32_t PDND_TRIG;
extern const uint32_t PDND_GLITCH;


void pdnd_initialize();
void pdnd_initialize_glitcher();
void pdnd_enable_buffers(bool enable);
bool pdnd_in(int i);
void pdnd_out(int i, bool value);
int pdnd_in_pin(int i);
int pdnd_out_pin(int i);

void pdnd_configure_input(int i);
void pdnd_configure_output(int i);
