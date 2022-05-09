#include "DS18B20.h"

unsigned char temperatureSign;

void DS18B20_Init()
{
  owiInit();
}

float DS18B20_ReadTemperature()
{
  owiReset();
  owiSendByte(SKIP_ROM);
  owiSendByte(CONVERT_T);
  CONVERT_DELAY;

  owiReset();
  owiSendByte(SKIP_ROM);
  owiSendByte(READ_SCRATCH_PAD);
  for(int i = 0; i < 2; i++)
  {
    data[i] = owiReceiveByte();
  }
  owiReset();

  float temperature = (data[1] << 8 | data[0])/16.0;
  if(temperature >= 0)
  {
	  temperatureSign = PLUS;
  }
  else if(temperature < 0)
  {
	  temperatureSign = MINUS; 
  }

  return temperature;
}
