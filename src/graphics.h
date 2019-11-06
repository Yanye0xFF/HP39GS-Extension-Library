#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <stdint.h>

extern uint8_t *__display_buf;

void draw_pixel(uint32_t x, uint32_t y);
void draw_pixel_ex(uint32_t x, uint32_t y, uint32_t len);

void draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);

void draw_rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void fill_rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

void draw_circle(uint32_t cx, uint32_t cy, uint32_t r);
void fill_circle(uint32_t cx, uint32_t cy, uint32_t r);

void draw_text(char *str, uint32_t x, uint32_t y);

#endif
