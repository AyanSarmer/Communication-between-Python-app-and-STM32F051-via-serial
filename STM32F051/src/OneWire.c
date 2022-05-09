#include "OneWire.h"

void owiInit()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    OWI_RELEASE_BUS;
    DELAY_H;
}

void owiReset()
{
    OWI_PULL_BUS_LOW;
    DELAY_H;  
    OWI_RELEASE_BUS;
    DELAY_I;  
    DELAY_J;
}

void owiWriteBit0()
{
    OWI_PULL_BUS_LOW;
    DELAY_C;
    OWI_RELEASE_BUS;
    DELAY_D;  
}

void owiWriteBit1()
{
    OWI_PULL_BUS_LOW;
    DELAY_A;
    OWI_RELEASE_BUS;
    DELAY_B;    
}

unsigned char owiReadBit()
{
    unsigned char bitsRead = 0;

    OWI_PULL_BUS_LOW;
    DELAY_A;  
    OWI_RELEASE_BUS;
    DELAY_E;  
    if(OWI_IDR & (1 << OWI_PIN)) 
        bitsRead = 1;  
    DELAY_F;  

    return bitsRead;
}

void owiSendByte(unsigned char data)
{
    for (unsigned char currentBit = 0; currentBit < 8; currentBit++)
    {
        if(data & LSBit)
        {
            owiWriteBit1();
        }
        else 
        {
            owiWriteBit0();
        }
        data >>= 1;
    }
}

unsigned char owiReceiveByte()
{
    unsigned char data = 0;

    for (unsigned char currentBit = 0; currentBit < 8; currentBit++)
    {
        data >>= 1;
        if (owiReadBit()) 
        {
            data |= MSBit;
        }
    }

    return data;
}