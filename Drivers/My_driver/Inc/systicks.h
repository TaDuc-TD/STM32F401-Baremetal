#pragma once
#include "stm32f4xx.h"

void sysTicks_init(void);
uint32_t get_ticks_ms(void);
void delay_ms(uint32_t ms);