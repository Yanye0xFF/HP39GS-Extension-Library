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
            d = (dy << 1) - dx;
            dinc1 = dy << 1;
            dinc2 = (dy - dx) << 1;
            //**
            // *
            xinc1 = 1; xinc2 = 1;
            yinc1 = 0; yinc2 = 1;
        }else {
            numpixels = dy + 1;
            d = (dx << 1) - dy;
            dinc1 = dx << 1;
            dinc2 = (dx - dy) << 1;
            //*
            //**
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

void draw_rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    if(width == 0 && height == 0) {
        draw_pixel(x, y);
        return;
    } 
    height -= 1;
    draw_pixel_ex(x, y, width);
    draw_pixel_ex(x, y + height, width);
    
    for(uint32_t i = y + 1; i < height; i++) {
        draw_pixel(x, y + i);
    }

    x = x + width - 1; 
    for(uint32_t i = 1; i < height; i++) {
        draw_pixel(x, y + i);
    }
}

void draw_circle(uint32_t cx, uint32_t cy, uint32_t r) {
    uint32_t x = 0, y = r;
    int32_t d = 3 - (2 * r);

    while (x <= y) {
        draw_pixel(cx + x, cy + y);
        draw_pixel(cx + x, cy - y);

        if (x != 0) {
            draw_pixel(cx - x, cy + y);
            draw_pixel(cx - x, cy - y);
        }

        if (x != y) {
            draw_pixel(cx + y, cy + x);
            draw_pixel(cx - y, cy + x);

            if (x != 0) {
                draw_pixel(cx + y, cy - x);
                draw_pixel(cx - y, cy - x);
            }
        }

        if (d < 0) {
            d += 4 * x + 6;
        }else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

const uint8_t height = 7, width = 5;
//flash offset 0x4000
const uint32_t base_address = 0x0FEF00;
void draw_font(uint32_t addr, uint32_t x, uint32_t y) {
    uint8_t *ptr;
    uint32_t line, idx, pos;

    for(uint32_t j = 0; j < height; j++) {
        ptr = (uint8_t *)(addr + j);
        line = ((y + j) << 4) + ((y + j) << 2);

        for(uint32_t i = 0; i < width; i++) {
            idx = ((x + i) >> 3); 
            pos = ((x + i) % 8);

            if(((*ptr) >> (7 - i)) & 0x1) {
                *(__display_buf + line + idx) |= (0x1 << pos);
            }else {
                *(__display_buf + line + idx) &= ~(0x1 << pos);
            }
        }
    }
}

void draw_text(char *str, uint32_t x, uint32_t y) {
    /*
    ascii font bitmap range: [0faf00 0fb200)
    BaseAdd = 0x0faf00
    if (ASCIICode >= 0x20 && ASCIICode <= 0x7E)  
        Address = (ASCIICode – 0x20 ) * 8 + BaseAdd; 
    */
    uint32_t address;
    uint32_t start_x = x;

    while(*str) {

        if(*str == 0x0A) {
            str++;
            x = start_x;
            y += height + 1;
            continue;
        }
        
        if((*str >= 0x20) && (*str <= 0x7E)) {
            address = ((*str - 0x20) << 3) + base_address;
            draw_font(address, x, y);
            x += (width + 1);
        }
        str++;
    }
}


void reverse_area(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    uint32_t line, idx, pos;
    for(uint32_t j = 0; j < height; j++) {
        line = ((y + j) << 4) + ((y + j) << 2);
        for(uint32_t i = 0; i < width; i++) {
            idx = ((x + i) >> 3); pos = ((x + i) % 8);
            if((*(__display_buf + line + idx) >> pos) & 0x1) {
                *(__display_buf + line + idx) &= ~(0x1 << pos);
            }else {
                *(__display_buf + line + idx) |= (0x1 << pos);
            }
        }
    }
}

