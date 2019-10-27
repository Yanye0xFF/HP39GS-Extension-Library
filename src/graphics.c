#include "graphics.h"

void draw_pixel(uint32_t x, uint32_t y) {
    uint32_t line = (y << 4) + (y << 2);
    uint32_t idx = (x >> 3), pos = (x % 8);
    *(__display_buf + line + idx) |= (0x1 << pos);
}

void draw_pixel_ex(uint32_t x, uint32_t y, uint32_t len) {
    for(uint32_t i = 0; i < len; i++) {
        draw_pixel((x + i), y);
    }
}

void draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
    if (y1 == y2) {
        uint32_t sx = (x1 > x2) ? x2 : x1;
        uint32_t len = (x1 > x2) ? (x1 - x2 + 1) : (x2 - x1 + 1);
        draw_pixel_ex(sx, y1, len);

    }else {
        uint32_t dx, dy, numpixels;
        int32_t dinc1, dinc2, xinc1, xinc2, yinc1, yinc2;

        int32_t x, y, d;
        int32_t px, py, sx;

        dx = (x1 > x2) ? (x1 - x2) : (x2 - x1);
        dy = (y1 > y2) ? (y1 - y2) : (y2 - y1);

        if(dx > dy) {
            numpixels = dx + 1;
            d = (2 * dy) - dx;
            dinc1 = 2 * dy;
            dinc2 = (dy - dx) * 2;
            xinc1 = 1; xinc2 = 1;
            yinc1 = 0; yinc2 = 1;
        }else {
            numpixels = dy + 1;
            d = (2 * dx) - dy;
            dinc1 = 2 * dx;
            dinc2 = (dx - dy) * 2;
            xinc1 = 0; xinc2 = 1;
            yinc1 = 1; yinc2 = 1;
        }

        if(x1 > x2) {
            xinc1 = -xinc1;
            xinc2 = -xinc2;
        }

        if(y1 > y2) {
            yinc1 = -yinc1;
            yinc2 = -yinc2;
        }

        x = x1;
        y = y1;
        sx = x;

        for(uint32_t i = 0; i < numpixels; i++) {
            px = x; py = y;
            if(d < 0) {
                d += dinc1;
                x += xinc1; y += yinc1;
            }else {
                d += dinc2;
                x += xinc2; y += yinc2;
            }

            if(y != py) {
                if (xinc2 < 0) 
                    draw_pixel_ex(px, py, sx - px + 1);
                else 
                    draw_pixel_ex(sx, py, px - sx + 1);
                sx = x;
            }
        }

        if(x != sx) {
            if (xinc2 < 0) 
                draw_pixel_ex(x + 1, y, sx - x);
            else 
                draw_pixel_ex(sx, y, x - sx);
        }
    }
}

