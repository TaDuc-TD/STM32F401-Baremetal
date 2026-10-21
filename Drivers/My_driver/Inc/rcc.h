#pragma once
#include "stm32f4xx.h"

typedef enum {
    SYSCLK_HSE,
    SYSCLK_HSI,
    SYSCLK_PLL,
} RCC_SysClock_Source_t;
typedef enum {
    PLL_SOURCE_HSE,
    PLL_SOURCE_HSI,
} RCC_PLL_Source_t;
typedef enum {
    PLLP_DIV2 = 0UL,
    PLLP_DIV4 = 1UL,
    PLLP_DIV6 = 2UL,
    PLLP_DIV8 = 3UL,
} RCC_PLL_PLLP_Div_t;
typedef enum {
    AHB_PRESCALER_1 = RCC_CFGR_HPRE_DIV1,
    AHB_PRESCALER_2 = RCC_CFGR_HPRE_DIV2,
    AHB_PRESCALER_4 = RCC_CFGR_HPRE_DIV4,
    AHB_PRESCALER_8 = RCC_CFGR_HPRE_DIV8,
    AHB_PRESCALER_16 = RCC_CFGR_HPRE_DIV16,
    AHB_PRESCALER_64 = RCC_CFGR_HPRE_DIV64,
    AHB_PRESCALER_128 = RCC_CFGR_HPRE_DIV128,
    AHB_PRESCALER_256 = RCC_CFGR_HPRE_DIV256,
} RCC_AHB_Prescaler_t;
typedef enum {
    APB1_PRESCALER_1 = RCC_CFGR_PPRE1_DIV1,
    APB1_PRESCALER_2 = RCC_CFGR_PPRE1_DIV2,
    APB1_PRESCALER_4 = RCC_CFGR_PPRE1_DIV4,
    APB1_PRESCALER_8 = RCC_CFGR_PPRE1_DIV8,
    APB1_PRESCALER_16 = RCC_CFGR_PPRE1_DIV16,
}RCC_APB1_Prescaler_t;
typedef enum {
    APB2_PRESCALER_1 = RCC_CFGR_PPRE2_DIV1,
    APB2_PRESCALER_2 = RCC_CFGR_PPRE2_DIV2,
    APB2_PRESCALER_4 = RCC_CFGR_PPRE2_DIV4,
    APB2_PRESCALER_8 = RCC_CFGR_PPRE2_DIV8,
    APB2_PRESCALER_16 = RCC_CFGR_PPRE2_DIV16,
} RCC_APB2_Prescaler_t;
typedef struct {
    RCC_PLL_Source_t PLL_Source;
    uint16_t PLLN;
    uint8_t PLLQ;
    uint8_t PLLM;
    RCC_PLL_PLLP_Div_t PLLP;
} RCC_PLL_Config_t;
typedef struct {
    RCC_SysClock_Source_t RCC_SysClock_Source;
    RCC_PLL_Config_t PLL_Config;
    RCC_AHB_Prescaler_t AHB_Prescaler;
    RCC_APB1_Prescaler_t APB1_Prescaler;
    RCC_APB2_Prescaler_t APB2_Prescaler;
} RCC_Config_t;

void RCC_init(const RCC_Config_t *RCC_Config);
uint8_t Get_sysclk_frequency();
uint8_t Get_hclk_freq ();
uint8_t Get_pclk1_freq();
uint8_t Get_pclk2_freq();