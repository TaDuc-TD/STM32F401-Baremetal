#pragma once
#include "stm32f4xx.h"

typedef enum {
    Edge_aligned,
    Center_aligned1,
    Center_aligned2,
    Center_aligned3
}TIM_CounterMode_t;

typedef struct {
    TIM_TypeDef *TIMx;
    uint16_t PSC;
    uint32_t ARR;
    TIM_CounterMode_t Mode;
}TIMx_Config_t;

void TIM_init(const TIMx_Config_t *config);
void TIM_start(TIM_TypeDef *TIMx);
void TIM_stop(TIM_TypeDef *TIMx);
void TIM_enable_update_IT(TIM_TypeDef *TIMx);
void TIM_disable_update_IT(TIM_TypeDef *TIMx);
uint32_t TIM_getCounter(TIM_TypeDef *TIMx);