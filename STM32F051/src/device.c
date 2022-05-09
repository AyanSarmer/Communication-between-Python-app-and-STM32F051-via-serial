#include "device.h"

void deviceInit() 
{
  DS18B20_Init();
  ledsInit();
  serialBegin();
}

void deviceControl()
{		
  float currentTemperature = DS18B20_ReadTemperature();
  unsigned char temperatureBuff[4];
  if(temperatureSign == PLUS)
		{
			temperatureBuff[0] = 0;
		}
		else if(temperatureSign == MINUS)
		{
			temperatureBuff[0] = 1;
		}
		
		temperatureBuff[1] = (unsigned char)(currentTemperature / 10);
		temperatureBuff[2] = (unsigned char)(currentTemperature - temperatureBuff[1] * 10);
		temperatureBuff[3] = (unsigned char)(currentTemperature * 10 - temperatureBuff[1] * 100 - temperatureBuff[2] * 10);
		for(int byteNum = 0; byteNum < 4; byteNum++)
		{
			serialSendByte(temperatureBuff[byteNum] + 48);
		}	
}