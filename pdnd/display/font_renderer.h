#pragma once

#include "gfxfont.h"
#include "ssd1306.h"

int font_get_glyph(const GFXfont *font, char c, GFXglyph **glyph);
int font_render(ssd1306_context *ctx, uint8_t x, uint8_t y, const GFXfont *font, char c);
int font_render_string(ssd1306_context *ctx, uint8_t x, uint8_t y, const GFXfont *font, char *s);
