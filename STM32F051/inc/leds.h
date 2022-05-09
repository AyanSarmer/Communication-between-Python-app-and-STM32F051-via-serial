#ifndef LEDS_H_
#define LEDS_H_

#include "stm32f0xx.h"

#define GREEN_LED           '1'
#define BLUE_LED            '2'
#define LED_ON              '0'
#define LED_OFF             '1'

void ledsInit(void);
void greenLedOn(void);
void greenLedOff(void);
void blueLedOn(void);
void blueLedOff(void);

#endif /* LEDS_H_ */