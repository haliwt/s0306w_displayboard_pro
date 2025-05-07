#ifndef __BSP_DELAY_H_
#define __BSP_DELAY_H_
#include "main.h"

void delay_init(uint8_t SYSCLK);

void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);

#endif
