#include "tabview.h"

void calcTitlesLength(uint8_t *buffer, int8_t **titles, uint8_t total);

void tabview_make(TabView *tab, int8_t **titles) {

    tab->span = (SCREEN_WIDTH / tab->total);

    draw_rect(tab->x, tab->y, SCREEN_WIDTH, TAB_HEIGHT);
    for(uint8_t i = 0; i < tab->total; i++) {
        draw_line((tab->span * i + tab->x), tab->y, (tab->span * i + tab->x), (tab->y + TAB_HEIGHT - 1));
    }

    uint8_t *sizes = (uint8_t *)malloc(sizeof(uint8_t) * tab->total);
    calcTitlesLength(sizes, titles, tab->total);
       
    uint8_t offset = 0;
    for(uint8_t i = 0; i < tab->total; i++) {
        draw_text(*(titles + i), (tab->span * i + i + ((tab->span - (*(sizes + i) * (FONT_WIDTH + 1))) >> 1)), 
            (tab->y + 1));
        offset += (*(sizes + i) + 1);
    }

    free(sizes);

    offset = tab->select; 
    tab->select = tab->total;
    tabview_select(tab, offset);
}


void tabview_select(TabView *tab, uint8_t position) {
    if(tab->select == position) {
        return;
    }
    
    uint8_t pos[2];
    pos[1] = position;
    pos[0] = (tab->select < tab->total) ? tab->select : tab->total;  

    position = (pos[0] == tab->total) ? 1 : 0;

    for(uint8_t i = position; i < 2; i++) {
        if(pos[i] < (tab->total - 1)) {
            reverse_area((pos[i] * tab->span + 1), (tab->y + 1), tab->span - 1, FONT_HEIGHT);
        }else {
            reverse_area((pos[i] * tab->span + 1), (tab->y + 1), (SCREEN_WIDTH - tab->span * (tab->total - 1) - 2), FONT_HEIGHT);
        }
    }

    tab->select = pos[1];
}


void calcTitlesLength(uint8_t *buffer, int8_t **titles, uint8_t total) {
    uint8_t length = 0;
    int8_t *ptr = NULL;
    for(uint8_t i = 0; i < total; i++) {
        length = 0;
        ptr = *(titles + i); 
        while(*ptr) {
            length++;
            ptr++;
        }
        *(buffer + i) = length;
    }
}

