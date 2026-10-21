#pragma once
#include "stm32f4xx.h"
#include "gpio.h"

typedef  enum {
    TRIGGER_RISING,
    TRIGGER_FALLING,
    TRIGGER_FALL_AND_RISING
} EXTI_Trigger_t;
typedef enum {
    PRI1,
    PRI2,
    PRI3,
    PRI4,
    PRI5,
    PRI6,
    PRI7,
    PRI8,
    PRI9,
    PRI10
} EXTI_Priority_t;
typedef struct {
    GPIO_TypeDef *GPIOx;
    GPIO_PinNumber_t PinNumber;
    EXTI_Trigger_t Trigger;
    EXTI_Priority_t Priority;
} EXTI_GPIO_Config;

void EXTI_init(const EXTI_GPIO_Config *config);