#include "leds.h"

void ledsInit(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0;
}

void greenLedOn(void)
{
    GPIOC->ODR |= GPIO_ODR_9;
}

void greenLedOff(void)
{
    GPIOC->ODR &= ~GPIO_ODR_9;
}

void blueLedOn(void)
{
    GPIOC->ODR |= GPIO_ODR_8;
}

void blueLedOff(void)
{
    GPIOC->ODR &= ~GPIO_ODR_8;
}