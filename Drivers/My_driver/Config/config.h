#pragma once
#include "gpio.h"
#include "usart.h"
/* ================== RCC =================*/
// Begin
static const RCC_Config_t RCC_Config = {
     .RCC_SysClock_Source = SYSCLK_PLL,
     .PLL_Config = {
         .PLL_Source = PLL_SOURCE_HSE,
         .PLLM = 25,
         .PLLN = 336,
         .PLLP = PLLP_DIV4,
     },
     .AHB_Prescaler = AHB_PRESCALER_1,
     .APB1_Prescaler = APB1_PRESCALER_2,
     .APB2_Prescaler = APB2_PRESCALER_1,
};
// End
/* =================== GPIO =======================*/
// Begin
static const GPIO_Config_t LED = {
    .GPIOx = GPIOC,
    .PinNumber = PIN13,
    .Mode = OUTPUT,
    .Pull = NO_PULL,
    .Speed = HIGH,
    .OutputType = PUSH_PULL
};

static const GPIO_Config_t TX1 = {
    .GPIOx = GPIOA,
    .PinNumber = PIN9,
    .Mode = AF_FUNC,
    .Pull = NO_PULL,
    .Speed = HIGH,
    .OutputType = PUSH_PULL,
    .AltFunction = AF7,
};
// End
/* =================== TIM ========================*/
// Begin
// End
/* ================== EXTI ========================*/
// Begin
// End
/* ================= USART ========================*/
// Begin
static const USART_Config_t USART1_Config = {
    .USARTx = USART1,
    .Mode = TX,
    .OverSampling = OVER_SAMPLING_8,
    .BaudRate = 115200,

};
// End
/* =================== SPI ========================*/
// Begin
// End
/* =================== I2C ========================*/
// Begin
// End






