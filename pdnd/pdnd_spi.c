#include "pdnd_spi.h"

#include "pico/stdlib.h"
#include "pio/pio_spi.h"
#include "pdnd.h"

pio_spi_inst_t pdnd_spi_initialize() {
    // Initialize HOLD & WP
    gpio_init(pdnd_out_pin(PDND_SPI_HOLD));
    gpio_set_dir(pdnd_out_pin(PDND_SPI_HOLD), GPIO_OUT);
    gpio_put(pdnd_out_pin(PDND_SPI_HOLD), 1);
    gpio_init(pdnd_out_pin(PDND_SPI_WP));
    gpio_set_dir(pdnd_out_pin(PDND_SPI_WP), GPIO_OUT);
    gpio_put(pdnd_out_pin(PDND_SPI_WP), 1);

    // Initialize CS
    gpio_init(pdnd_out_pin(PDND_SPI_CS));
    gpio_put(pdnd_out_pin(PDND_SPI_CS), 1);
    gpio_set_dir(pdnd_out_pin(PDND_SPI_CS), GPIO_OUT);


    // We use PIO 1
    
    pio_spi_inst_t spi = {
            .pio = pio1,
            .sm = 0,
            .cs_pin = pdnd_out_pin(PDND_SPI_CS)
    };

    uint offset = pio_add_program(spi.pio, &spi_cpha0_program);

    pio_spi_init(spi.pio, spi.sm, offset,
                 8,       // 8 bits per SPI frame
                 31.25f,  // 1 MHz @ 125 clk_sys
                 false,   // CPHA = 0
                 false,   // CPOL = 0
                 pdnd_out_pin(PDND_SPI_CLK),
                 pdnd_out_pin(PDND_SPI_MOSI),
                 pdnd_in_pin(PDND_SPI_MISO)
    );

    return spi;
}

void pdnd_spi_read(const pio_spi_inst_t *spi, uint8_t *dst, size_t len) {
    pio_spi_read8_blocking(spi, dst, len);
}
void pdnd_spi_write(const pio_spi_inst_t *spi, uint8_t *dst, size_t len) {
    pio_spi_write8_blocking(spi, dst, len);
}

void pdnd_spi_write_read(const pio_spi_inst_t *spi, uint8_t *src, uint8_t *dst, size_t len) {
    pio_spi_write8_read8_blocking(spi, src, dst, len);
}

void pdnd_spi_cs(const pio_spi_inst_t *spi, bool enable) {
    asm volatile("nop \n nop \n nop"); // FIXME
    gpio_put(spi->cs_pin, 1);
    asm volatile("nop \n nop \n nop"); // FIXME
}