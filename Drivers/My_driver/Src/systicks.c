#include "systicks.h"
#include "rcc.h"

static uint32_t ticks_ms = 0;

void sysTicks_init(void) {
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
    SysTick->LOAD = 1000 * Get_sysclk_frequency();
    SysTick->VAL = 0UL;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void) {
    ticks_ms++;
}

uint32_t get_ticks_ms(void) {
    return ticks_ms;
}

void delay_ms(uint32_t ms) {
    uint32_t start_time  = get_ticks_ms();
    while (get_ticks_ms() - start_time < ms);
}