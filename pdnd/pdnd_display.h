#pragma once

#include <stdarg.h>
#include "display/ssd1306.h"
#include "display/FreeSans5pt7b.h"
#include "display/FreeSans9pt7b.h"

#define DEFAULT_FONT FreeSans9pt7b
#define DEFAULT_FONT_Y 15

typedef struct {
    ssd1306_context ctx;
} pdnd_display;

typedef struct {
    uint32_t width;
    uint32_t height;
    const uint8_t *data;
} pdnd_screen;

void pdnd_display_initialize();
void pdnd_display_create(pdnd_display *display);
void pdnd_display_screen(pdnd_display *d, pdnd_screen *s);
void pdnd_display_printf(pdnd_display *d, uint8_t x, uint8_t y, const char *format, va_list args);
void cls(bool display);
void pprintf(const char *format, ...);
void pprintfxy(uint8_t x, uint8_t y, const char *format, va_list args);
