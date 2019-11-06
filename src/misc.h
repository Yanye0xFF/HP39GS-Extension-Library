#ifndef __MISC_H__
#define __MISC_H__

#include <hpconio.h>
#include <stdint.h>

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

void putstr(const int8_t *str);

char nibToHex(uint8_t nib);
char numToHex(uint8_t num);

void printHex(uint32_t hex, uint8_t full_paint);
void hex_printf(const char *str, uint32_t val, uint8_t next_line);

#endif
