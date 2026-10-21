#include "tim.h"

static inline void Enable_peripheral_clock(TIM_TypeDef *TIMx) {
    if (TIMx == TIM1) {
        RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    }
    else if (TIMx == TIM2) {
        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    }
    else if (TIMx == TIM3) {
        RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    }
    else if (TIMx == TIM4) {
        RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    }
    else if (TIMx == TIM5) {
        RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
    }
    else if (TIMx == TIM9) {
        RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
    }
    else if (TIMx == TIM10) {
        RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
    }
    else if (TIMx == TIM11) {
        RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
    }
}
void TIM_init(const TIMx_Config_t *config) {
    Enable_peripheral_clock(config->TIMx);
    config->TIMx->PSC = config->PSC;
    config->TIMx->ARR = config->ARR;
    config->TIMx->EGR = TIM_EGR_UG;
    config->TIMx->CR1 &= ~(3UL << TIM_CR1_CMS_Pos); config->TIMx->CR1 |= ((config->Mode) << TIM_CR1_CMS_Pos);
}
void TIM_start(TIM_TypeDef *TIMx) {
    TIMx->CNT = 0;
    TIMx->CR1 |= TIM_CR1_CEN;
}
void TIM_stop(TIM_TypeDef *TIMx) {
    TIMx->CR1 &= ~TIM_CR1_CEN;
}
void TIM_enable_update_IT(TIM_TypeDef *TIMx) {
    TIMx->SR &= ~TIM_SR_UIF;
    TIMx->DIER |= TIM_DIER_UIE;
    if (TIMx == TIM1) {
        NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
    }
    else if (TIMx == TIM2) {
        NVIC_EnableIRQ(TIM2_IRQn);
    }
    else if (TIMx == TIM3) {
        NVIC_EnableIRQ(TIM3_IRQn);
    }
    else if (TIMx == TIM4) {
        NVIC_EnableIRQ(TIM4_IRQn);
    }
    else if (TIMx == TIM5) {
        NVIC_EnableIRQ(TIM5_IRQn);
    }
    else if (TIMx == TIM9) {
        NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
    }
    else if (TIMx == TIM10) {
        NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
    }
    else if (TIMx == TIM11) {
        NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
    }
}
void TIM_disable_update_IT(TIM_TypeDef *TIMx) {
    TIMx->DIER &= ~TIM_DIER_UIE;
    TIMx->SR &= ~TIM_SR_UIF;
    // Dang nghi cach fix tiep
}
uint32_t TIM_getCounter(TIM_TypeDef *TIMx) {
    return (uint32_t)(TIMx->CNT);
}