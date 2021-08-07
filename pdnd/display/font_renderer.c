// This text renderer is terribly slow, but it works!

#include "font_renderer.h"
#include <stddef.h>
#include <string.h>

static inline uint8_t _get_bit(uint8_t *data, size_t bit) {
	size_t byte_index = bit/8;
	size_t byte_shift = 7-(bit%8);
	uint8_t glyph_byte = data[byte_index];
	return (glyph_byte >> byte_shift) & 0x01;
}

int font_get_glyph(const GFXfont *font, char c, GFXglyph **glyph) {
	if(c < font->first) {
		return -1;
		} if(c > font->last) {
		return -1;
	}
	
	size_t glyph_index = c - font->first;
	*glyph = &(font->glyph[glyph_index]);
	return 0;
}

int font_render(ssd1306_context *ctx, uint8_t x_in, uint8_t y_in, const GFXfont *font, char c) {

 GFXglyph *glyph = NULL;
    if(font_get_glyph(font, c, &glyph)) {
        // Couldn't find font.
        return -1;
    }

    uint8_t *glyph_data  = &(font->bitmap[glyph->bitmapOffset]);
    for(int y = glyph->yOffset; y < (glyph->yOffset+glyph->height); y++) {
		for(int x = 0; x < glyph->width; x++) {
            size_t y_index = y + -glyph->yOffset;
            size_t data_cursor = y_index * glyph->width;
            data_cursor += x;
            uint8_t bit = _get_bit(glyph_data, data_cursor);
            if(bit) {
                ssd1306_write_pixel(ctx, x_in+x+glyph->xOffset, y_in+y, 1);
            } else {
                ssd1306_write_pixel(ctx, x_in+x+glyph->xOffset, y_in+y, 0);
            }
        }
    }
}

int font_render_string(ssd1306_context *ctx, uint8_t x, uint8_t y, const GFXfont *font, char *s) {
    uint8_t original_x = x;
    size_t l = strlen(s);
    for(size_t i=0; i < l; i++) {
        char c = s[i];
        if(c == '\n') {
            x = original_x;
            y += font->yAdvance;
        } else {
            GFXglyph *glyph = NULL;
            if(font_get_glyph(font, c, &glyph)) {
                // Couldn't find font.
                return -1;
            }
            font_render(ctx, x, y, font, c);
            x += glyph->xAdvance;
        }
    }
}
