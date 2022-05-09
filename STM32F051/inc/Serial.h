#ifndef SERIAL_H_
#define SERIAL_H_

#include "stm32f0xx.h"
#include "leds.h"

#define USART2_BRR_VALUE        0x341   
#define USART2_AFR_VALUE		0x1100

void USART2_IRQHandler(void);
void serialBegin(void);
void serialSendByte(char data);
void serialPrintln(char* buff);

extern volatile unsigned char receivedByte[2], byteNum;

#endif /* SERIAL_H_ */
