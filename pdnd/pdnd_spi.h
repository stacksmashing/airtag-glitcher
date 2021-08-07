#pragma once

#include "pio/pio_spi.h"

pio_spi_inst_t pdnd_spi_initialize();
void pdnd_spi_read(const pio_spi_inst_t *spi, uint8_t *dst, size_t len);
void pdnd_spi_write(const pio_spi_inst_t *spi, uint8_t *dst, size_t len);
void pdnd_spi_write_read(const pio_spi_inst_t *spi, uint8_t *src, uint8_t *dst, size_t len);
void pdnd_spi_cs(const pio_spi_inst_t *spi, bool enable);
