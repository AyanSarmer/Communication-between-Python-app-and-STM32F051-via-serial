#include "Serial.h"

volatile uint8_t receivedByte[2], byteNum = 0;

void USART2_IRQHandler(void)
{
	receivedByte[byteNum] = USART2->RDR;
	byteNum++;
	if(byteNum > 1)
	{
		byteNum = 0;
        if(receivedByte[0] == GREEN_LED)
        {
            if(receivedByte[1] == LED_ON)
            {
                greenLedOn();
            }
            else if(receivedByte[1] == LED_OFF)
            {
                greenLedOff();
            }
        }
        else if(receivedByte[0] == BLUE_LED)
        {
            if(receivedByte[1] == LED_ON)
            {
                blueLedOn();
            }
            else if(receivedByte[1] == LED_OFF)
            {
                blueLedOff();
            }        
        }
	}    
}

void serialBegin()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1;
    GPIOA->AFR[0] |= USART2_AFR_VALUE;

    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->CFGR3 |= RCC_CFGR3_USART1SW;
    USART2->BRR |= USART2_BRR_VALUE;
    USART2->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
    while (!(USART2->ISR &= USART_ISR_TXE));
    NVIC_EnableIRQ(USART2_IRQn);
    
}

void serialSendByte(char data)
{       
    while (!(USART2->ISR & USART_ISR_TC));
    USART2->TDR = data;     
}

void serialPrintln(char* buff)
{
    while(*buff != '\0')
	{
		serialSendByte(*buff);
		buff++;
	}
	serialSendByte('\n');
}

