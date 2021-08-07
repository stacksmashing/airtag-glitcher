#include "pdnd_display.h"

#include <stdlib.h>
#include <stdio.h>

#include "display/font_renderer.h"
#include "display/ssd1306.h"
#include "pio/pio_i2c.h"

#define PIN_SDA 20
#define PIN_SCL 21

pdnd_display *global_display = NULL;

void pdnd_display_initialize() {
    global_display = malloc(sizeof(pdnd_display));
    if(global_display == NULL) {
        return;
    }

    pdnd_display_create(global_display);
}

void pdnd_display_create(pdnd_display *display) {
    PIO pio = pio0;
    uint sm = 0;
    
    uint offset = pio_add_program(pio, &i2c_program);
    i2c_program_init(pio, sm, offset, PIN_SDA, PIN_SCL);


    ssd1306_context ctx;
    ctx.pio = pio;
    ctx.sm = sm;

    ssd1306_begin(&ctx, SSD1306_SWITCHCAPVCC);
    ssd1306_clear_display(&ctx);
    ssd1306_display(&ctx);

    display->ctx = ctx;
}

void pdnd_display_screen(pdnd_display *d, pdnd_screen *s) {
    if(d == NULL) {
        return;
    }
    if(s == NULL) {
        return;
    }
    ssd1306_clear_display(&d->ctx);
    void ssd1306_draw_sceen(ssd1306_context *ctx, int16_t x, int16_t y, pdnd_screen *screen);
    ssd1306_draw_bitmap(&d->ctx, 0, 0, s->data, s->width, s->height, 1);
    ssd1306_display(&d->ctx);
}

void pdnd_display_printf(pdnd_display *d, uint8_t x, uint8_t y, const char *format, va_list args) {
    if(d == NULL) {
        return;
    }
    char print_buffer[128];
    vsnprintf(print_buffer, 128, format, args);
    font_render_string(&d->ctx, x, y, &DEFAULT_FONT, print_buffer);
}

// Global helper functions
void cls(bool display) {
    ssd1306_clear_display(&global_display->ctx);
    if(display) {
        ssd1306_display(&global_display->ctx);
    }
}

void pprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    pdnd_display_printf(global_display, 0, DEFAULT_FONT_Y, format, args);
    va_end(args);
    
    ssd1306_display(&global_display->ctx);
}

void pprintfxy(uint8_t x, uint8_t y, const char *format, va_list args) {
    pdnd_display_printf(global_display, x, y, format, args);
    ssd1306_display(&global_display->ctx);
}
