#pragma once
#include "stm32f4xx.h"

typedef enum {
    GPIO_RESET,
    GPIO_SET
} GPIO_state_t;
typedef enum {
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
    PIN8,
    PIN9,
    PIN10,
    PIN11,
    PIN12,
    PIN13,
    PIN14,
    PIN15
} GPIO_PinNumber_t;
typedef enum {
    INPUT,
    OUTPUT,
    AF_FUNC,
    ANALOG
} GPIO_Mode_t;
typedef enum {
    NO_PULL,
    PULL_UP,
    PULL_DOWN
} GPIO_Pull_t;
typedef enum {
    LOW,
    MEDIUM,
    HIGH,
    VERY_HIGH
} GPIO_Speed_t;
typedef enum {
    PUSH_PULL,
    OPEN_DRAIN
} GPIO_OutputType_t;
typedef enum {
    AF0,
    AF1,
    AF2,
    AF3,
    AF4,
    AF5,
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15
}GPIO_AltFunction_t;
typedef struct {
    GPIO_TypeDef *GPIOx;
    GPIO_PinNumber_t PinNumber;
    GPIO_Mode_t Mode;
    GPIO_Pull_t Pull;
    GPIO_Speed_t Speed;
    GPIO_OutputType_t OutputType;
    uint8_t AltFunction;
} GPIO_Config_t;

void GPIO_init(const GPIO_Config_t *config);
void GPIO_writePin(GPIO_TypeDef *GPIOx, uint16_t pinNumber, GPIO_state_t pinState);
void GPIO_togglePin(GPIO_TypeDef *GPIOx, uint16_t pinNumber);
uint8_t GPIO_readPin(GPIO_TypeDef *GPIOx, uint16_t pinNumber);