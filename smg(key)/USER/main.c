#include "sys.h"
#include "delay.h"
#include "SMG.h"
#include "key.h"


int main(void)
{ 
	//u16 key;
	u8 key_state;
	u32 counter=0;
  HAL_Init();                    														//��ʼ��HAL��    
  Stm32_Clock_Init(336,8,2,7);  														//����ʱ��,168Mhz
	delay_init(168);																					//��ʼ����ʱ����
	SMG_Init();																								//��ʼ������ܺ���
	KEY_Init();
	
	while(1)
	{
		DIV_number(counter);
		SMG_Disp(Disp_Code);
		switch(key_state)
		{
			case key_state_0:
				if(!KEY0)      //�������£�����״̬1
				{
					key_state=key_state_1;
				}
			break;
			case key_state_1:     
				if(!KEY0)     //���û�е������״̬2
				{             //�����������Ϊ�����������ص�״̬0���¼��
					key_state=key_state_2;
				}
				else
				{
					key_state=key_state_0;
				}
			break;
			case key_state_2:    //���������������Ϊ����һ�Σ�������Ӧ�����ݴ�����֮�������κδ���
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
//		key=KEY_Scan(0);            //����ɨ��
//		switch(key)
//		{
//			case KEY0_PRES:	
//				counter--;
//		}
		
}

