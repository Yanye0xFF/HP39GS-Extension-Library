#ifndef __FONT_H__
#define __FONT_H__

#include <stdint.h>

typedef struct font_info {
    uint16_t count;
    uint8_t height;
    uint8_t width;
}FONT_INFO;


extern FONT_INFO font_args;
extern char font_data[];

#endif

