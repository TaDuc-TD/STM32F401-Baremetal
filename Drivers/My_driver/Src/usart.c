#include "usart.h"
#include "rcc.h"
#include <stdarg.h>
#include <stdio.h>

static inline void Enable_peripheral_clock (USART_TypeDef *USARTx) {
    if (USARTx == USART1) {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    }
    else if (USARTx == USART6) {
        RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
    }
    else if (USARTx == USART2) {
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    }
}
static inline void Set_BaudRate(USART_TypeDef * USARTx, uint32_t BaudRate, Over_Sampling_t OverSampling) {
    uint32_t k;
    uint32_t clk_usart = 0;
    uint16_t Mantissa = 0;
    uint8_t Fraction = 0;
    if (USARTx == USART1 || USARTx == USART6) {
        clk_usart = Get_pclk2_freq();
    }
    else if (USARTx == USART2) {
        clk_usart = Get_pclk1_freq();
    }
    if (OverSampling == OVER_SAMPLING_8) {
        k = BaudRate * 8;
        Fraction = (((1000000UL * clk_usart) % k) * 8UL + k/2UL) / k;
        Mantissa = 1000000UL * clk_usart / BaudRate / 8UL;
        if (Fraction >= 8) {
            Fraction = 0UL;
            Mantissa++;
        }
    }
    else if (OverSampling == OVER_SAMPLING_16) {
        k = BaudRate * 16;
        Fraction = (((1000000UL * clk_usart) % k) * 16UL + k/2UL) / k;
        Mantissa = 1000000UL * clk_usart / BaudRate / 16UL;
        if (Fraction >= 16) {
            Fraction = 0UL;
            Mantissa++;
        }
    }
    USARTx->BRR = (Mantissa << USART_BRR_DIV_Mantissa_Pos) | (Fraction << USART_BRR_DIV_Fraction_Pos);
}

void USART_init(const USART_Config_t *config) {
    Enable_peripheral_clock(config->USARTx);
    // Choose Over sampling
    if (config->OverSampling == OVER_SAMPLING_8) {
        config->USARTx->CR1 |= USART_CR1_OVER8;
    }
    else if (config->OverSampling == OVER_SAMPLING_16) {
        config->USARTx->CR1 &= ~USART_CR1_OVER8;
    }
    // Set baudRate
    Set_BaudRate(config->USARTx, config->BaudRate, config->OverSampling);
    // Choose mode
    if (config->Mode == TX) {
        config->USARTx->CR1 |= USART_CR1_TE;
    }
    else if (config->Mode == RX) {
        config->USARTx->CR1 |= USART_CR1_RE;
    }
    else if (config->Mode == TX_RX) {
        config->USARTx->CR1 |= (USART_CR1_TE | USART_CR1_RE);
    }
    else {
        config->USARTx->CR1 |= (USART_CR1_TE | USART_CR1_RE);
    }
    // Enable USART
    config->USARTx->CR1 |= USART_CR1_UE;
}
void USART_DMA_init (const USART_Config_t *config) {
    if (config->DMA_Map_TX.DMAx == DMA2 || config->DMA_Map_RX.DMAx == DMA2) {
        RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
    }
    else if (config->DMA_Map_TX.DMAx == DMA1 || config->DMA_Map_RX.DMAx == DMA1 ) {
        RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
    }
    if (config->Mode == TX) {
        config->DMA_Map_TX.DMA_Stream->CR &= ~ DMA_SxCR_EN;
        while (config->DMA_Map_TX.DMA_Stream->CR & DMA_SxCR_EN);
        config->DMA_Map_TX.DMA_Stream->PAR = (uint32_t)&(config->USARTx->DR);
        config->DMA_Map_TX.DMA_Stream->CR = ((uint32_t)(config->DMA_Map_TX.Channel) << DMA_SxCR_CHSEL_Pos) | (1UL << DMA_SxCR_DIR_Pos) | DMA_SxCR_MINC;
        config->USARTx->CR3 |= USART_CR3_DMAT;
    }
    else if (config->Mode == RX) {
        config->DMA_Map_RX.DMA_Stream->CR &= ~ DMA_SxCR_EN;
        while (config->DMA_Map_RX.DMA_Stream->CR & DMA_SxCR_EN);
        config->DMA_Map_RX.DMA_Stream->PAR = (uint32_t)&(config->USARTx->DR);
        config->DMA_Map_RX.DMA_Stream->CR = ((uint32_t)(config->DMA_Map_RX.Channel) << DMA_SxCR_CHSEL_Pos) | (0UL << DMA_SxCR_DIR_Pos) | DMA_SxCR_MINC;
        config->USARTx->CR3 |= USART_CR3_DMAR;
    }
    else if (config->Mode == TX_RX) {
        config->DMA_Map_TX.DMA_Stream->CR &= ~ DMA_SxCR_EN;
        config->DMA_Map_RX.DMA_Stream->CR &= ~ DMA_SxCR_EN;
        while (config->DMA_Map_TX.DMA_Stream->CR & DMA_SxCR_EN);
        while (config->DMA_Map_RX.DMA_Stream->CR & DMA_SxCR_EN);
        config->DMA_Map_TX.DMA_Stream->PAR = (uint32_t)&(config->USARTx->DR);
        config->DMA_Map_RX.DMA_Stream->PAR = (uint32_t)&(config->USARTx->DR);
        config->DMA_Map_TX.DMA_Stream->CR = ((uint32_t)(config->DMA_Map_TX.Channel) << DMA_SxCR_CHSEL_Pos)
                                            | (1UL << DMA_SxCR_DIR_Pos) | DMA_SxCR_MINC;
        config->DMA_Map_RX.DMA_Stream->CR = ((uint32_t)(config->DMA_Map_RX.Channel) << DMA_SxCR_CHSEL_Pos)
                                            | (0UL << DMA_SxCR_DIR_Pos) | DMA_SxCR_MINC;
        config->USARTx->CR3 |= USART_CR3_DMAT;
        config->USARTx->CR3 |= USART_CR3_DMAR;
    }
}
void USART_transmit_char(USART_TypeDef *UARTx, const char c)
{
    while (!(UARTx->SR & USART_SR_TXE)) {}
    UARTx->DR = c;
}
void USART_transmit_string(USART_TypeDef *UARTx, const char *str) {
    while (*str) {
        USART_transmit_char(UARTx, *str++);
    }
}
void USART_transmit_printf(USART_TypeDef *UARTx, const char *data, ...) {
    char buffer[128];
    va_list values;
    va_start(values, data);
    vsnprintf(buffer, sizeof(buffer), data, values);
    va_end(values);
    for (uint8_t i = 0; buffer[i] != '\0'; i++) {
        USART_transmit_char(UARTx,buffer[i]);
    }
}
void USART_DMA_transmit(USART_TypeDef *USARTx,USART_DMA_Map_t DMA_Map, const char *tx_buffer, uint16_t length) {
    while (DMA_Map.DMA_Stream->CR & DMA_SxCR_EN);
    DMA_Map.DMA_Stream->CR &= ~DMA_SxCR_EN;
    DMA_Map.DMAx->HIFCR = 
    DMA_Map.DMA_Stream->M0AR = (uint32_t)tx_buffer;
    DMA_Map.DMA_Stream->NDTR = length;
    DMA_Map.DMA_Stream->CR |= DMA_SxCR_EN;
}
