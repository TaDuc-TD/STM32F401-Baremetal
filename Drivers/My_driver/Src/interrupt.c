#include "interrupt.h"

static inline uint8_t decode_port (GPIO_TypeDef *GPIOx) {
    if (GPIOx == GPIOA) {
        return 0;
    }
    else if (GPIOx == GPIOB) {
        return 1;
    }
    else if (GPIOx == GPIOC) {
        return 2;
    }
    else if (GPIOx == GPIOD) {
        return 3;
    }
    else if (GPIOx == GPIOE) {
        return 4;
    }
    return 0xFF;
}
static inline void EXTI_Config_IRQ(GPIO_PinNumber_t PinNumber, EXTI_Priority_t Priority) {
    if (PinNumber == 0) {
        NVIC_SetPriority(EXTI0_IRQn, Priority);
        NVIC_EnableIRQ(EXTI0_IRQn);
    }
    else if (PinNumber == 1) {
        NVIC_SetPriority(EXTI1_IRQn, Priority);
        NVIC_EnableIRQ(EXTI1_IRQn);
    }
    else if (PinNumber == 2) {
        NVIC_SetPriority(EXTI2_IRQn, Priority);
        NVIC_EnableIRQ(EXTI2_IRQn);
    }
    else if (PinNumber == 3) {
        NVIC_SetPriority(EXTI3_IRQn, Priority);
        NVIC_EnableIRQ(EXTI3_IRQn);
    }
    else if (PinNumber == 4) {
        NVIC_SetPriority(EXTI4_IRQn, Priority);
        NVIC_EnableIRQ(EXTI4_IRQn);
    }
    else if (PinNumber >=5 && PinNumber <= 9) {
        NVIC_SetPriority(EXTI9_5_IRQn, Priority);
        NVIC_EnableIRQ(EXTI9_5_IRQn);
    }
    else if (PinNumber >= 10 && PinNumber <= 15) {
        NVIC_SetPriority(EXTI15_10_IRQn, Priority);
        NVIC_EnableIRQ(EXTI15_10_IRQn);
    }
}
void EXTI_init(const EXTI_GPIO_Config *config) {
    uint8_t syscfg_exit = ((uint8_t)(config->PinNumber) / 4);
    uint32_t port = decode_port(config->GPIOx);
    SYSCFG->EXTICR[syscfg_exit] &= ~(15UL << (((uint8_t)(config->PinNumber) % 4) * 4));
    SYSCFG->EXTICR[syscfg_exit] |= (port << (((uint8_t)(config->PinNumber) % 4) * 4));
    if (config->Trigger == TRIGGER_RISING) {
        EXTI->FTSR &= ~(1UL << (uint8_t)(config->PinNumber));
        EXTI->RTSR &= ~(1UL << (uint8_t)(config->PinNumber));
        EXTI->RTSR |= (1UL << (uint8_t)(config->PinNumber));
    }
    else if (config->Trigger == TRIGGER_FALLING) {
        EXTI->RTSR &= ~(1UL << (uint8_t)(config->PinNumber));
        EXTI->FTSR &= ~(1UL << (uint8_t)(config->PinNumber));
        EXTI->FTSR |= (1UL << (uint8_t)(config->PinNumber));
    }
    else {
        EXTI->RTSR &= ~(1UL << (uint8_t)(config->PinNumber));
        EXTI->RTSR |= (1UL << (uint8_t)(config->PinNumber));
        EXTI->FTSR &= ~(1UL << (uint8_t)(config->PinNumber));
        EXTI->FTSR |= (1UL << (uint8_t)(config->PinNumber));
    }
    EXTI->IMR &= ~(1UL << (uint8_t)(config->PinNumber));
    EXTI->IMR |= (1UL << (uint8_t)(config->PinNumber));
    EXTI_Config_IRQ(config->PinNumber,config->Priority);
}


// ------------------ EXTI ISR ----------------------//

__attribute__((weak)) void EXTI_Line0_Callback(void) {}
__attribute__((weak)) void EXTI_Line1_Callback(void) {}
__attribute__((weak)) void EXTI_Line2_Callback(void) {}
__attribute__((weak)) void EXTI_Line3_Callback(void) {}
__attribute__((weak)) void EXTI_Line4_Callback(void) {}
__attribute__((weak)) void EXTI_Line5_Callback(void) {}
__attribute__((weak)) void EXTI_Line6_Callback(void) {}
__attribute__((weak)) void EXTI_Line7_Callback(void) {}
__attribute__((weak)) void EXTI_Line8_Callback(void) {}
__attribute__((weak)) void EXTI_Line9_Callback(void) {}
__attribute__((weak)) void EXTI_Line10_Callback(void) {}
__attribute__((weak)) void EXTI_Line11_Callback(void) {}
__attribute__((weak)) void EXTI_Line12_Callback(void) {}
__attribute__((weak)) void EXTI_Line13_Callback(void) {}
__attribute__((weak)) void EXTI_Line14_Callback(void) {}
__attribute__((weak)) void EXTI_Line15_Callback(void) {}

void EXTI0_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR0) {
        EXTI->PR = EXTI_PR_PR0;
        EXTI_Line0_Callback();
    }
}
void EXTI1_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR1) {
        EXTI->PR = EXTI_PR_PR1;
        EXTI_Line1_Callback();
    }
}
void EXTI2_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR2) {
        EXTI->PR = EXTI_PR_PR2;
        EXTI_Line2_Callback();
    }
}
void EXTI3_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR3) {
        EXTI->PR = EXTI_PR_PR3;
        EXTI_Line3_Callback();
    }
}
void EXTI4_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR4) {
        EXTI->PR = EXTI_PR_PR4;
        EXTI_Line4_Callback();
    }
}
void EXTI9_5_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR5) {
        EXTI->PR = EXTI_PR_PR5;
        EXTI_Line5_Callback();
    }
    if (EXTI->PR & EXTI_PR_PR6) {
        EXTI->PR = EXTI_PR_PR6;
        EXTI_Line6_Callback();
    }
    if (EXTI->PR & EXTI_PR_PR7) {
        EXTI->PR = EXTI_PR_PR7;
        EXTI_Line7_Callback();
    }
    if (EXTI->PR & EXTI_PR_PR8) {
        EXTI->PR = EXTI_PR_PR8;
        EXTI_Line8_Callback();
    }
    if (EXTI->PR & EXTI_PR_PR9) {
        EXTI->PR = EXTI_PR_PR9;
        EXTI_Line9_Callback();
    }
}
void EXTI15_10_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR10) {
        EXTI->PR = EXTI_PR_PR10;
        EXTI_Line10_Callback();
    }
    if (EXTI->PR & EXTI_PR_PR11) {
        EXTI->PR = EXTI_PR_PR11;
        EXTI_Line11_Callback();
    }
    if (EXTI->PR & EXTI_PR_PR12) {
        EXTI->PR = EXTI_PR_PR12;
        EXTI_Line12_Callback();
    }
    if (EXTI->PR & EXTI_PR_PR13) {
        EXTI->PR = EXTI_PR_PR13;
        EXTI_Line13_Callback();
    }
    if (EXTI->PR & EXTI_PR_PR14) {
        EXTI->PR = EXTI_PR_PR14;
        EXTI_Line14_Callback();
    }
    if (EXTI->PR & EXTI_PR_PR15) {
        EXTI->PR = EXTI_PR_PR15;
        EXTI_Line15_Callback();
    }
}


// ----------------------- TIM ISR ------------------- //

__attribute__((weak)) void TIM1_ISR_Callback(void) {}
__attribute__((weak)) void TIM1_ISR_BRK_Callback(void) {}
__attribute__((weak)) void TIM1_ISR_TRG_Callback(void) {}
__attribute__((weak)) void TIM1_ISR_COM_Callback(void) {}
__attribute__((weak)) void TIM1_ISR_CC1_Callback(void) {}
__attribute__((weak)) void TIM1_ISR_CC2_Callback(void) {}
__attribute__((weak)) void TIM1_ISR_CC3_Callback(void) {}
__attribute__((weak)) void TIM1_ISR_CC4_Callback(void) {}
__attribute__((weak)) void TIM2_ISR_Callback(void) {}
__attribute__((weak)) void TIM3_ISR_Callback(void) {}
__attribute__((weak)) void TIM4_ISR_Callback(void) {}
__attribute__((weak)) void TIM5_ISR_Callback(void) {}
__attribute__((weak)) void TIM9_ISR_Callback(void) {}
__attribute__((weak)) void TIM10_ISR_Callback(void) {}
__attribute__((weak)) void TIM11_ISR_Callback(void) {}

void TIM1_UP_TIM10_IRQHandler(void) {
    if ((TIM1->SR & TIM_SR_UIF) && (TIM1->DIER & TIM_DIER_UIE)) {
        TIM1->SR &= ~TIM_SR_UIF;
        TIM1_ISR_Callback();
    }
    if ((TIM10->SR & TIM_SR_UIF) && (TIM10->DIER & TIM_DIER_UIE)) {
        TIM10->SR &= ~TIM_SR_UIF;
        TIM10_ISR_Callback();
    }
}
void TIM2_IRQHandler(void) {
    if ((TIM2->SR & TIM_SR_UIF) && (TIM2->DIER & TIM_DIER_UIE)) {
        TIM2->SR &= ~TIM_SR_UIF;
        TIM2_ISR_Callback();
    }
}
void TIM3_IRQHandler(void) {
    if ((TIM3->SR & TIM_SR_UIF) && (TIM3->DIER & TIM_DIER_UIE)) {
        TIM3->SR &= ~TIM_SR_UIF;
        TIM3_ISR_Callback();
    }
}
void TIM4_IRQHandler(void) {
    if ((TIM4->SR & TIM_SR_UIF) && (TIM4->DIER & TIM_DIER_UIE)) {
        TIM4->SR &= ~TIM_SR_UIF;
        TIM4_ISR_Callback();
    }
}
void TIM5_IRQHandler(void) {
    if ((TIM5->SR & TIM_SR_UIF) && (TIM5->DIER & TIM_DIER_UIE)) {
        TIM5->SR &= ~TIM_SR_UIF;
        TIM5_ISR_Callback();
    }
}
void TIM1_BRK_TIM9_IRQHandler(void) {
    if ((TIM1->SR & TIM_SR_BIF) && (TIM1->DIER & TIM_DIER_BIE)) {
        TIM1->SR &= ~TIM_SR_BIF;
        TIM1_ISR_BRK_Callback();
    }
    if ((TIM9->SR & TIM_SR_UIF) && (TIM9->DIER & TIM_DIER_UIE)) {
        TIM9->SR &= ~TIM_SR_UIF;
        TIM9_ISR_Callback();
    }
}
void TIM1_TRG_COM_TIM11_IRQHandler(void) {
    if ((TIM1->SR & TIM_SR_TIF) && (TIM1->DIER & TIM_DIER_TIE)) {
        TIM1->SR &= ~TIM_SR_TIF;
        TIM1_ISR_TRG_Callback();
    }
    if ((TIM11->SR & TIM_SR_UIF) && (TIM11->DIER & TIM_DIER_UIE)) {
        TIM11->SR &= ~TIM_SR_UIF;
        TIM11_ISR_Callback();
    }
    if ((TIM1->SR & TIM_SR_COMIF) && (TIM1->DIER & TIM_DIER_COMIE)) {
        TIM1->SR &= ~TIM_SR_COMIF;
        TIM1_ISR_COM_Callback();
    }
}
void TIM1_CC_IRQHandler(void) {
    if ((TIM1->SR & TIM_SR_CC1IF) && (TIM1->DIER & TIM_DIER_CC1IE)) {
        TIM1->SR &= ~TIM_SR_CC1IF;
        TIM1_ISR_CC1_Callback();
    }
    if ((TIM1->SR & TIM_SR_CC2IF) && (TIM1->DIER & TIM_DIER_CC2IE)) {
        TIM1->SR &= ~TIM_SR_CC2IF;
        TIM1_ISR_CC2_Callback();
    }
    if ((TIM1->SR & TIM_SR_CC3IF) && (TIM1->DIER & TIM_DIER_CC3IE)) {
        TIM1->SR &= ~TIM_SR_CC3IF;
        TIM1_ISR_CC3_Callback();
    }
    if ((TIM1->SR & TIM_SR_CC4IF) && (TIM1->DIER & TIM_DIER_CC4IE)) {
        TIM1->SR &= ~TIM_SR_CC4IF;
        TIM1_ISR_CC4_Callback();
    }
}
