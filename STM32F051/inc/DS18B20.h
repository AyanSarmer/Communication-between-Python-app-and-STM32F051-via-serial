#ifndef DS18B20_H_
#define DS18B20_H_

#include "OneWire.h"

#define SKIP_ROM            0xCC
#define READ_SCRATCH_PAD    0xBE
#define CONVERT_T           0x44

#define CONVERT_DELAY       for(unsigned long i = 0; i < 780000; i++) {__asm("nop");}

#define MINUS               1
#define PLUS                0

void DS18B20_Init();
float DS18B20_ReadTemperature();
unsigned char data[2];
extern unsigned char temperatureSign;

#endif /* DS18B20_H_ */