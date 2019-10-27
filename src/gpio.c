#include "gpio.h"

void PIN_FUNC_SELECT(uint8_t pin, uint8_t func) {
    rGPHCON &= (~(((func) ? 0x2 : 0x3) << (pin << 1)));
}

void GPIO_DIS_OUTPUT(uint8_t pin) {
    rGPHCON |= (0x3 << (pin << 1));
}

void PIN_PULLUP_EN(uint8_t pin) {
    rGPHUP &= (~(0x1 << pin));
}

void PIN_PULLUP_DIS(uint8_t pin) {
    rGPHUP |= (0x1 << pin); 
}

void GPIO_OUTPUT_SET(uint8_t pin, uint8_t data) {
    rGPHDAT = (data) ? (rGPHDAT | (0x1 << pin)) : (rGPHDAT & (~(0x1 << pin))); 
}

uint8_t GPIO_INPUT_GET(uint8_t pin) {
    return (rGPHDAT >> pin) & 0x1;
}
 
