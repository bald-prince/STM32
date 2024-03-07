#include "sys.h"
#include "delay.h"
#include "SMG.h"
#include "key.h"


int main(void)
{ 
	//u16 key;
	u8 key_state;
	u32 counter=0;
  HAL_Init();                    														//初始化HAL库    
  Stm32_Clock_Init(336,8,2,7);  														//设置时钟,168Mhz
	delay_init(168);																					//初始化延时函数
	SMG_Init();																								//初始化数码管函数
	KEY_Init();
	
	while(1)
	{
		DIV_number(counter);
		SMG_Disp(Disp_Code);
		switch(key_state)
		{
			case key_state_0:
				if(!KEY0)      //按键按下，进入状态1
				{
					key_state=key_state_1;
				}
			break;
			case key_state_1:     
				if(!KEY0)     //如果没有弹起进入状态2
				{             //如果弹起则是为按键抖动，回到状态0重新检测
					key_state=key_state_2;
				}
				else
				{
					key_state=key_state_0;
				}
			break;
			case key_state_2:    //如果按键弹起，则视为按了一次，进行相应的数据处理，反之不进行任何处理
				if(KEY0)
				{
					key_state=key_state_0;
					counter++;
				}
			break;
				
		}
	
	}
		
		//DIV_number(counter);
		//SMG_Disp(Disp_Code);
//		key=KEY_Scan(0);            //按键扫描
//		switch(key)
//		{
//			case KEY0_PRES:	
//				counter--;
//		}
		
}

