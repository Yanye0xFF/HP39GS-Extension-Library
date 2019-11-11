#ifndef __LISTVIEW_H__
#define __LISTVIEW_H__

#include <stdint.h>

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

//real 8bytes
typedef struct list_item {
    int8_t *title_ptr;
    uint8_t id;
    struct list_item *prev;
} ListItem;

//4bytes
typedef struct list_view {
    uint8_t x;
    uint8_t y;
    uint8_t total;
    uint8_t current;
} ListView;


void listview_make(ListView *listview, ListItem *dataset);
void listview_select(ListView *listview, uint8_t position, ListItem *dataset);


#endif
