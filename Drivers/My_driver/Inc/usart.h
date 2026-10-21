#pragma once
#include "stm32f4xx.h"

typedef enum {
    OVER_SAMPLING_8,
    OVER_SAMPLING_16,
} Over_Sampling_t;
typedef enum {
    LENGTH_8BIT,
    LENGTH_9BIT,
} Word_Length_t;
typedef enum {
    NONE,
    ODD,
    EVEN,
} Parity_t;
typedef enum {
    STOP_BIT_0P5,
    STOP_BITS_1,
    STOP_BITS_1P5,
    STOP_BITS_2,
} Stop_bits_t;
typedef enum {
    TX,
    RX,
    TX_RX,
} Mode_t;
typedef struct {
    DMA_TypeDef *DMAx;
    DMA_Stream_TypeDef *DMA_Stream;
    uint8_t Channel;
} USART_DMA_Map_t;
typedef struct {
    USART_TypeDef *USARTx;
    Mode_t Mode;
    Over_Sampling_t OverSampling;
    uint32_t BaudRate;
    Word_Length_t WordLength;
    Parity_t Parity;
    Stop_bits_t StopBits;
    USART_DMA_Map_t DMA_Map_TX;
    USART_DMA_Map_t DMA_Map_RX;
} USART_Config_t;

void USART_init(const USART_Config_t *config);
void USART_DMA_init(const USART_Config_t *config);
void USART_transmit_char(USART_TypeDef *UARTx, const char c);
void USART_transmit_string(USART_TypeDef *UARTx, const char *str);
void USART_transmit_printf(USART_TypeDef *UARTx, const char *data, ...);
void USART_DMA_transmit(USART_TypeDef *USARTx,USART_DMA_Map_t DMA_Map, const char *tx_buffer, uint16_t length);