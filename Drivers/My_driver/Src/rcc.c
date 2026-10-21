#include "rcc.h"

#define CLK_CRYSTAL_HSI     16UL//MHz
#define CLK_CRYSTAL_HSE     25UL//MHz

static uint8_t sysclk_feq = 0;
static uint8_t hclk_freq = 0;
static uint8_t pclk1_freq = 0;
static uint8_t pclk2_freq = 0;
static inline uint8_t decode_value_PLLP(RCC_PLL_PLLP_Div_t value) {
    return ((value + 1) * 2);
}
static inline uint16_t decode_value_AHB_Prescaler(RCC_AHB_Prescaler_t value) {
    if (value == AHB_PRESCALER_1) {
        return 1;
    }
    else if (value == AHB_PRESCALER_2) {
        return 2;
    }
    else if (value == AHB_PRESCALER_4) {
        return 4;
    }
    else if (value == AHB_PRESCALER_8) {
        return 8;
    }
    else if (value == AHB_PRESCALER_16) {
        return 16;
    }
    else if (value == AHB_PRESCALER_64) {
        return 64;
    }
    else if (value == AHB_PRESCALER_128) {
        return 128;
    }
    else if (value == AHB_PRESCALER_256) {
        return 256;
    }
}
static inline uint8_t decode_value_APB1_Prescaler(RCC_APB1_Prescaler_t value) {
    if (value == APB1_PRESCALER_1) {
        return 1;
    }
    else if (value == APB1_PRESCALER_2) {
        return 2;
    }
    else if (value == APB1_PRESCALER_4) {
        return 4;
    }
    else if (value == APB1_PRESCALER_8) {
        return 8;
    }
    else if (value == APB1_PRESCALER_16) {
        return 16;
    }
}
static inline uint8_t decode_value_APB2_Prescaler(RCC_APB2_Prescaler_t value) {
    if (value == APB2_PRESCALER_1) {
        return 1;
    }
    else if (value == APB2_PRESCALER_2) {
        return 2;
    }
    else if (value == APB2_PRESCALER_4) {
        return 4;
    }
    else if (value == APB2_PRESCALER_8) {
        return 8;
    }
    else if (value == APB2_PRESCALER_16) {
        return 16;
    }
}

void RCC_init(const RCC_Config_t *RCC_Config) {
    if (RCC_Config->RCC_SysClock_Source == SYSCLK_HSI) {
        sysclk_feq = CLK_CRYSTAL_HSI;
        // On HSI
        RCC->CR |= RCC_CR_HSION;
        while (!(RCC->CR & RCC_CR_HSIRDY)) {};
        // Set number of wait states CPU
        FLASH->ACR |= FLASH_ACR_LATENCY_0WS;
        // Set division AHB,APBx
        RCC->CFGR |= RCC_Config->AHB_Prescaler;
        RCC->CFGR |= RCC_Config->APB1_Prescaler;
        RCC->CFGR |= RCC_Config->APB2_Prescaler;
        hclk_freq = sysclk_feq / decode_value_AHB_Prescaler(RCC_Config->AHB_Prescaler);
        pclk1_freq = hclk_freq / decode_value_APB1_Prescaler(RCC_Config->APB1_Prescaler);
        pclk2_freq = hclk_freq / decode_value_APB2_Prescaler(RCC_Config->APB2_Prescaler);
        // Choose Sysclk = HSI
        RCC->CFGR |= RCC_CFGR_SW_HSI;
        while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) {};
    }
    else if (RCC_Config->RCC_SysClock_Source == SYSCLK_HSE) {
        sysclk_feq = CLK_CRYSTAL_HSE;
        // On HSE
        RCC->CR |= RCC_CR_HSEON;
        while (!(RCC->CR & RCC_CR_HSERDY)) {};
        // Set number of wait states CPU
        FLASH->ACR |= FLASH_ACR_LATENCY_0WS;
        // Set division AHB,APBx
        RCC->CFGR |= RCC_Config->AHB_Prescaler;
        RCC->CFGR |= RCC_Config->APB1_Prescaler;
        RCC->CFGR |= RCC_Config->APB2_Prescaler;
        hclk_freq = sysclk_feq / decode_value_AHB_Prescaler(RCC_Config->AHB_Prescaler);
        pclk1_freq = hclk_freq / decode_value_APB1_Prescaler(RCC_Config->APB1_Prescaler);
        pclk2_freq = hclk_freq / decode_value_APB2_Prescaler(RCC_Config->APB2_Prescaler);
        // Choose Sysclk = HSE
        RCC->CFGR |= RCC_CFGR_SW_HSE;
        while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE) {}
    }
    else if (RCC_Config->RCC_SysClock_Source == SYSCLK_PLL) {
        if (RCC_Config->PLL_Config.PLL_Source == PLL_SOURCE_HSI) {
            // Choose PLL Source
            RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;
            // On HSI
            RCC->CR |= RCC_CR_HSION;
            while (!(RCC->CR & RCC_CR_HSIRDY)) {};
        }
        else if (RCC_Config->PLL_Config.PLL_Source == PLL_SOURCE_HSE) {
            // Choose PLL Source
            RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
            // On HSE
            RCC->CR |= RCC_CR_HSEON;
            while (!(RCC->CR & RCC_CR_HSERDY)) {};
        }
        // Set PLLM,PLLN,PLLP,PLLQ
        RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLQ);
        RCC->PLLCFGR |= ((uint32_t)(RCC_Config->PLL_Config.PLLM) << RCC_PLLCFGR_PLLM_Pos)
                        |((uint32_t)(RCC_Config->PLL_Config.PLLN) << RCC_PLLCFGR_PLLN_Pos)
                        |((uint32_t)(RCC_Config->PLL_Config.PLLP) << RCC_PLLCFGR_PLLP_Pos)
                        |((uint32_t)(RCC_Config->PLL_Config.PLLQ) << RCC_PLLCFGR_PLLQ_Pos);
        // Set number of wait states CPU
        if (RCC_Config->PLL_Config.PLL_Source == PLL_SOURCE_HSI) {
            sysclk_feq = (CLK_CRYSTAL_HSI * (RCC_Config->PLL_Config.PLLN))
                        / (RCC_Config->PLL_Config.PLLM) / (decode_value_PLLP(RCC_Config->PLL_Config.PLLP));
        }
        else if (RCC_Config->PLL_Config.PLL_Source == PLL_SOURCE_HSE) {
            sysclk_feq = (CLK_CRYSTAL_HSE * (RCC_Config->PLL_Config.PLLN))
                        / (RCC_Config->PLL_Config.PLLM) / (decode_value_PLLP(RCC_Config->PLL_Config.PLLP));
        }
        if (sysclk_feq > 30 && sysclk_feq <= 60) {
            FLASH->ACR |= FLASH_ACR_LATENCY_1WS;
        }
        else if (sysclk_feq > 60 && sysclk_feq <= 84) {
            FLASH->ACR |= FLASH_ACR_LATENCY_2WS;
        }
        // Set division AHB,APBx
        RCC->CFGR |= RCC_Config->AHB_Prescaler;
        RCC->CFGR |= RCC_Config->APB1_Prescaler;
        RCC->CFGR |= RCC_Config->APB2_Prescaler;
        hclk_freq = sysclk_feq / decode_value_AHB_Prescaler(RCC_Config->AHB_Prescaler);
        pclk1_freq = hclk_freq / decode_value_APB1_Prescaler(RCC_Config->APB1_Prescaler);
        pclk2_freq = hclk_freq / decode_value_APB2_Prescaler(RCC_Config->APB2_Prescaler);
        // On PLL
        RCC->CR |= RCC_CR_PLLON;
        while (!(RCC->CR & RCC_CR_PLLRDY)) {};
        // Choose Sysclk = PLL
        RCC->CFGR |= RCC_CFGR_SW_PLL;
        while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL){}
    }
}
uint8_t Get_sysclk_frequency() {
    return sysclk_feq;
}
uint8_t Get_hclk_freq () {
    return hclk_freq;
}
uint8_t Get_pclk1_freq () {
    return pclk1_freq;
}
uint8_t Get_pclk2_freq () {
    return pclk2_freq;
}
