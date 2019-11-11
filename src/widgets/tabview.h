#ifndef __TABVIEW_H__
#define __TABVIEW_H__

#include <stdint.h>
#include <hpstdlib.h>

#include "graphics.h"
#include <hpconio.h>

extern uint8_t *__display_buf;

#ifndef NULL
    #define NULL 0
#endif

#ifndef __SCREEN_PIXEL__
    #define __SCREEN_PIXEL__ 
    #define SCREEN_WIDTH 131
    #define SCREEN_HEIGHT 64
#endif

#ifndef __FONT_INFO__
    #define __FONT_INFO__ 
    #define FONT_HEIGHT 7
    #define FONT_WIDTH 5
#endif

#define TAB_HEIGHT 9

//real 8bytes
typedef struct tabview {
    uint8_t x;
    uint8_t y;
    uint8_t total;
    uint8_t select;
    uint8_t span;
} TabView;

void tabview_make(TabView *tab, int8_t **titles);
void tabview_select(TabView *tab, uint8_t position);


#endif
