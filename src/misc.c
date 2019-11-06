#include "misc.h"

//like puts without '\n'
void putstr(const char *str) {
    while(*str) {
        putchar(*str++);
    }
}

const char *hex = "0123456789ABCDEF";
//converts a nibble to its hex form
char nibToHex(uint8_t nib) { 
	return hex[nib & 0xF];
}

//num in range 0 ~ 15
char numToHex(uint8_t num) { 
	return hex[num];
}

/*
以16进制打印uint32_t
@param hex 输出的数值 
@param full_paint TRUE:完整打印4字节,高位以0补齐;FALSE:自动缩放,按实际长度输出
*/
void printHex(uint32_t hex, uint8_t full_paint) {
    uint8_t paint = full_paint, ch = 0x00;
    if(hex == 0x00) {
        putchar('0');
        return;
    }
    for(int32_t offset = 28; offset > -1; offset -= 4) {
        ch = nibToHex(hex >> offset); 
        if(!paint) paint = (ch != 0x30);
        if(paint) putchar(ch);
    }
}

void hex_printf(const char *str, uint32_t val, uint8_t next_line) {
    putstr(str);
    printHex(val, FALSE);
    if(next_line) putchar('\n');
}
