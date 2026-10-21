#include "gpio.h"

static inline void Enable_peripheral_clock(GPIO_TypeDef *GPIOx) {
    if (GPIOx == GPIOA) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    }
    else if (GPIOx == GPIOB) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    }
    else if (GPIOx == GPIOC) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    }
    else if (GPIOx == GPIOD) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    }
    else if (GPIOx == GPIOE) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    }
};
void GPIO_init(const GPIO_Config_t *config ) {
    Enable_peripheral_clock(config->GPIOx);
    config->GPIOx->MODER &= ~ (3UL << (config->PinNumber * 2));
    config->GPIOx->MODER |= ((uint32_t)(config->Mode) << (config->PinNumber * 2));
    if (config->Mode == OUTPUT || config->Mode == AF_FUNC) {
        config->GPIOx->OTYPER &= ~ (1UL << (config->PinNumber));
        config->GPIOx->OTYPER |= ((uint32_t)(config->OutputType) << (config->PinNumber));
        config->GPIOx->OSPEEDR &= ~ (3UL << (config->PinNumber * 2));
        config->GPIOx->OSPEEDR |= ((uint32_t)(config->Speed) << (config->PinNumber * 2));
    }
    config->GPIOx->PUPDR &= ~ (3UL << (config->PinNumber * 2));
    config->GPIOx->PUPDR |= ((uint32_t)(config->Pull) << (config->PinNumber * 2));
    if (config->Mode == AF_FUNC) {
        if (config->PinNumber <= 7) {
            config->GPIOx->AFR[0] &= ~(15UL << (config->PinNumber * 4));
            config->GPIOx->AFR[0] |= ((uint32_t)(config->AltFunction) << (config->PinNumber * 4));
        }
        else {
            config->GPIOx->AFR[1] &= ~(15UL << ((config->PinNumber-8) * 4));
            config->GPIOx->AFR[1] |= ((uint32_t)(config->AltFunction) << ((config->PinNumber-8) * 4));
        }
    }
}
void GPIO_writePin(GPIO_TypeDef *GPIOx, uint16_t pinNumber, GPIO_state_t pinState) {
    if (pinState == GPIO_SET) {
        GPIOx->BSRR = 1UL << pinNumber;
    }
    else if (pinState == GPIO_RESET) {
        GPIOx->BSRR = 1UL << (pinNumber + 16);
    }
}
void GPIO_togglePin(GPIO_TypeDef *GPIOx, uint16_t pinNumber) {
    GPIOx->ODR ^= 1UL << pinNumber;
}
uint8_t GPIO_readPin(GPIO_TypeDef *GPIOx, uint16_t pinNumber) {
    return (GPIOx->IDR & (1UL << pinNumber)) != 0;
}