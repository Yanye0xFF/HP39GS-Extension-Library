#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>

//20190924
//ONLY FOR PORT H & B

/*
 MMU
 0x56000000	->	0x07A00000 ~ 0x07AFFFFF
*/

/*
H7 H6 H3 and H2
*/
#define rGPHCON    (*(volatile unsigned *)0x07A00070) //Port H control
#define rGPHDAT    (*(volatile unsigned *)0x07A00074) //Port H data
#define rGPHUP     (*(volatile unsigned *)0x07A00078) //Pull-up control H

/*
B2   
*/
#define rGPBCON    (*(volatile unsigned *) 0x07A00010) //Port B control
#define rGPBDAT    (*(volatile unsigned *) 0x07A00014) //Port B control
#define rGPBUP     (*(volatile unsigned *) 0x07A00018) //Port B control

#define FUNC_INPUT 0x00
#define FUNC_OUTPUT 0x01
#define FUNC_RESERVED 0x11

#define GPH7 7
#define GPH6 6
#define GPH3 3
#define GPH2 2

#define GPB2 2

void PIN_FUNC_SELECT(uint8_t pin, uint8_t func);
void PIN_PULLUP_EN(uint8_t pin);
void PIN_PULLUP_DIS(uint8_t pin);
void GPIO_DIS_OUTPUT(uint8_t pin);

void GPIO_OUTPUT_SET(uint8_t pin, uint8_t data);
uint8_t GPIO_INPUT_GET(uint8_t pin);

#endif
