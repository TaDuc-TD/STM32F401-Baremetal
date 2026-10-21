#include <string.h>
#include "rcc.h"
#include "systicks.h"
#include "gpio.h"
#include "interrupt.h"
#include "config.h"
#include "tim.h"

uint16_t counter = 0;
char buffer[] = "1234567890 ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz\r\n"
                "1234567890 ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz\r\n"
                "1234567890 ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz\r\n"
                "1234567890 ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz\r\n\r\n\r\n";

int main(void) {
    RCC_init(&RCC_Config);
    sysTicks_init();
    GPIO_init(&LED);
    GPIO_init(&TX1);
    USART_init(&USART1_Config);
    USART_DMA_init(&USART1_Config);
    while (1) {
        GPIO_writePin(LED.GPIOx, LED.PinNumber, GPIO_RESET);
        USART_transmit_string(USART1, buffer);
        GPIO_writePin(LED.GPIOx, LED.PinNumber, GPIO_SET);
        delay_ms(2000);
        GPIO_writePin(LED.GPIOx, LED.PinNumber, GPIO_RESET);
        USART_DMA_transmit(USART1, buffer, sizeof(buffer) - 1);
        GPIO_writePin(LED.GPIOx, LED.PinNumber, GPIO_SET);
        delay_ms(2000);
    }
}