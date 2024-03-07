#include "S_bus_Reci.h"
//P9.2+P8.2
 int S_bus_flag = 0;
 int En[2] = {1,1};
 uint8_t Data = 0x00;
void S_bus_init()
{
	GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P9,GPIO_PIN2);
	GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P8,GPIO_PIN2);
}

uint8_t S_Reci()
{
	int ii;
	En[0] = GPIO_getInputPinValue(GPIO_PORT_P8,GPIO_PIN2);//Enable_new_state
	
	if(En[0]-En[1] == 1)
	{
		S_bus_flag = 1;
		Delay_us(1);
	}
	
	En[1] = En[0];//Enable_old_state
	
	if(S_bus_flag)
	{
		for(ii=0;ii<8;ii++)
		{
			if( GPIO_getInputPinValue(GPIO_PORT_P9,GPIO_PIN2) )
					Data |= 0x01;
			else
				;
			Data<<=1;
			Delay_us(2);
		}
		S_bus_flag = 0;
  }
//	if(En[0]-En[1]==-1)
//		S_bus_flag = 0;
}



