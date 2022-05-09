#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include "stm32f0xx.h"

#define OWI_IDR                 GPIOB->IDR
#define OWI_PIN                 12
#define MSBit                   0x80
#define LSBit                   0x01

#define DELAY_A                 for(int i = 0; i < 6; i++) {__asm("nop");}
#define DELAY_B                 for(int i = 0; i < 83; i++) {__asm("nop");}
#define DELAY_C                 for(int i = 0; i < 80; i++) {__asm("nop");}
#define DELAY_D                 for(int i = 0; i < 11; i++) {__asm("nop");}
#define DELAY_E                 for(int i = 0; i < 9; i++) {__asm("nop");}
#define DELAY_F                 for(int i = 0; i < 73; i++) {__asm("nop");}
#define DELAY_G 
#define DELAY_H                 for(int i = 0; i < 482; i++) {__asm("nop");}                
#define DELAY_I                 for(int i = 0; i < 91; i++) {__asm("nop");}
#define DELAY_J                 for(int i = 0; i < 412; i++) {__asm("nop");}                

#define OWI_RELEASE_BUS         GPIOB->MODER &= ~GPIO_MODER_MODER12_0
#define OWI_PULL_BUS_LOW        GPIOB->MODER |= GPIO_MODER_MODER12_0

void owiInit();
void owiReset();
void owiWriteBit0();
void owiWriteBit1();
unsigned char owiReadBit();
void owiSendByte(unsigned char data);
unsigned char owiReceiveByte();

#endif /* ONEWIRE_H_ */