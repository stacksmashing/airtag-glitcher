#include "pdnd.h"

#include "pico/stdlib.h"

const uint32_t PDND_OE = 0;
const uint32_t PDND_IN_BASE = 1;
const uint32_t PDND_OUT_BASE = 9;


const uint32_t PDND_TRIG = 18;
const uint32_t PDND_GLITCH = 19;

const uint32_t PDND_DISP_SDA = 20;
const uint32_t PDND_DISP_SCL = 21;



const uint32_t PDND_SPI_CS = 0;
const uint32_t PDND_SPI_MISO = 0;
const uint32_t PDND_SPI_WP = 1;
const uint32_t PDND_SPI_HOLD = 2;
const uint32_t PDND_SPI_CLK = 3;
const uint32_t PDND_SPI_MOSI = 4;

void pdnd_initialize() {
    gpio_init(PDND_OE);
    // Disable buffers so everything
    // is in high-z.
    pdnd_enable_buffers(false);
    gpio_set_dir(PDND_OE, GPIO_OUT);

    // Initialize inputs
    for(int i=0; i < 8; i++) {
        int pin = PDND_IN_BASE + i;
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
    }
    for(int i=0; i < 8; i++) {
        int pin = PDND_OUT_BASE + i;
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
    }
}

void pdnd_initialize_glitcher() {
    gpio_init(PDND_TRIG);
    gpio_set_dir(PDND_TRIG, GPIO_IN);
    gpio_pull_up(PDND_TRIG);
    gpio_init(PDND_GLITCH);
    gpio_put(PDND_GLITCH, 0);
    gpio_set_dir(PDND_GLITCH, GPIO_OUT);
}

void pdnd_enable_buffers(bool enable) {
    gpio_put(PDND_OE, !enable);
}

void pdnd_configure_input(int i) {
    int pin = pdnd_in(i);
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
}

void pdnd_configure_output(int i) {
    int pin = pdnd_in(i);
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
}

bool pdnd_in(int i) {
    return gpio_get(PDND_IN_BASE + i);
}

void pdnd_out(int i, bool value) {
    gpio_put(PDND_OUT_BASE + i, value);
}

int pdnd_in_pin(int i) {
    return PDND_IN_BASE + i;
}
int pdnd_out_pin(int i) {
    return PDND_OUT_BASE + i;
}